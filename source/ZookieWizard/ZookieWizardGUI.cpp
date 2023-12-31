#include <ZookieWizard/ZookieWizard.h>
#include <ZookieWizard/WindowsManager.h>

#include <ElephantBase/Archive.h>
#include <ElephantEngine/eNode.h>

namespace ZookieWizard
{
    namespace GUI
    {
        ////////////////////////////////////////////////////////////////
        // Initialize variables
        ////////////////////////////////////////////////////////////////

        HBITMAP myWindowLogo = NULL;
        HFONT myWindowFont = NULL;

        bool updatingEditboxesNotByUser = false;

        static const int32_t nodesList_ButtonsCount = 25;
        static const int32_t nodesList_ActionsCount = 7;
        int32_t nodesList_CurrentAction;
        static HWND nodesList_Windows[1 + nodesList_ButtonsCount];
        static int32_t nodesList_ActionIds[nodesList_ActionsCount][2];

        static const char* nodesList_ActionNames[nodesList_ActionsCount] =
        {
            "Browsing the Archive", "Moving Nodes", "Deleting Nodes", "Cloning Nodes",
            "Managing Materials", "Modifying 3D meshes", "Other"
        };


        ////////////////////////////////////////////////////////////////
        // List of static functions
        ////////////////////////////////////////////////////////////////

        #define MENUFUNC_DENISCONVERT_OPENLVL  0
        #define MENUFUNC_DENISCONVERT_CONVERT  1

        void menuFunc_DenisConvert(WPARAM wParam, LPARAM lParam, void* custom_param)
        {
            switch ((int32_t)custom_param)
            {
                case MENUFUNC_DENISCONVERT_OPENLVL:
                    DenisMenuOptions_OpenDenisLevel();
                    return;
                case MENUFUNC_DENISCONVERT_CONVERT:
                    DenisMenuOptions_ConvertDenisLevel();
                    return;
            }
        }

        #define MENUFUNC_ARMENUBAR_OPEN          0
        #define MENUFUNC_ARMENUBAR_SAVE          1
        #define MENUFUNC_ARMENUBAR_CLOSE         2
        #define MENUFUNC_ARMENUBAR_GENERATE      3
        #define MENUFUNC_ARMENUBAR_PARSER        4
        #define MENUFUNC_ARMENUBAR_SAVESCRIPTS   5
        #define MENUFUNC_ARMENUBAR_SAVEXREF      6
        #define MENUFUNC_ARMENUBAR_LOADXREF      7
        #define MENUFUNC_ARMENUBAR_BULKCONVERT   8
        #define MENUFUNC_ARMENUBAR_SAVESTRUCT    9
        #define MENUFUNC_ARMENUBAR_SAVECOLLADA  10

        void menuFunc_ArMenuBar(WPARAM wParam, LPARAM lParam, void* custom_param)
        {
            switch ((int32_t)custom_param)
            {
                case MENUFUNC_ARMENUBAR_OPEN:
                    ArMenuOptions_OpenOrSaveAr(nullptr, AR_MODE_READ);
                    return;
                case MENUFUNC_ARMENUBAR_SAVE:
                    ArMenuOptions_OpenOrSaveAr(nullptr, AR_MODE_WRITE);
                    return;
                case MENUFUNC_ARMENUBAR_CLOSE:
                    ArMenuOptions_CloseAr(false);
                    return;
                case MENUFUNC_ARMENUBAR_GENERATE:
                    ArMenuOptions_GenerateEmptyScene(false);
                    return;
                case MENUFUNC_ARMENUBAR_PARSER:
                    ArMenuOptions_ChangeNodesWithTxt();
                    return;
                case MENUFUNC_ARMENUBAR_SAVESCRIPTS:
                    ArMenuOptions_ExportScripts();
                    return;
                case MENUFUNC_ARMENUBAR_SAVEXREF:
                    ArMenuOptions_ExportProxies();
                    return;
                case MENUFUNC_ARMENUBAR_LOADXREF:
                    ArMenuOptions_ReloadProxies();
                    return;
                case MENUFUNC_ARMENUBAR_BULKCONVERT:
                    ArMenuOptions_BulkArchiveConverter();
                    return;
                case MENUFUNC_ARMENUBAR_SAVESTRUCT:
                    ArMenuOptions_WriteTreeToJsonFile();
                    return;
                case MENUFUNC_ARMENUBAR_SAVECOLLADA:
                    ArMenuOptions_ExportArToCollada();
                    return;
            }
        }

        void buttonFunc_EditBoxTyping(WPARAM wParam, LPARAM lParam, void* custom_param)
        {
            if ((!updatingEditboxesNotByUser) && (EN_CHANGE == HIWORD(wParam)))
            {
                GetWindowText((HWND)lParam, (LPSTR)custom_param, LARGE_BUFFER_SIZE);
            }
        }

        void buttonFunc_ArchivesList(WPARAM wParam, LPARAM lParam, void* custom_param)
        {
            eString dummy_str;
            char bufor[64];

            switch (HIWORD(wParam))
            {
                case LBN_SELCHANGE:
                {
                    currentArId = SendMessage((HWND)lParam, LB_GETCURSEL, 0, 0);

                    if (currentArId < 0)
                    {
                        currentArId = 0;
                    }
                    else if (currentArId >= MAX_OPEN_ARCHIVES)
                    {
                        currentArId = (MAX_OPEN_ARCHIVES - 1);
                    }

                    /****************/

                    myARs[currentArId].changeGlobalScene();
                    myARs[currentArId].changeSelectedObject(NODES_LISTBOX_UPDATE_CURRENT, nullptr);

                    /****************/

                    if (myARs[currentArId].isNotEmpty())
                    {
                        dummy_str = myARs[currentArId].getBaseFileName();

                        if (checkArFilenameExtensions(dummy_str.getText(), dummy_str.getLength()))
                        {
                            dummy_str = dummy_str.getSubstring(0, (-4));
                        }
                    }

                    GUI::updateArSettingsText(2, dummy_str.getText());

                    /****************/

                    setMaxArchiveVersion(myARs[currentArId].getVersion());

                    sprintf_s(bufor, 64, "%i", currentArchiveVersion);

                    GUI::updateArSettingsText(7, bufor);

                    /****************/

                    break;
                }
            }
        }

        void buttonFunc_ArchiveVersionsEdit(WPARAM wParam, LPARAM lParam, void* custom_param)
        {
            int32_t new_version;
            bool invalid_version = false;
            bool lost_focus = (EN_KILLFOCUS == HIWORD(wParam));
            char bufor[16];

            if (!updatingEditboxesNotByUser && ((EN_CHANGE == HIWORD(wParam)) || lost_focus))
            {
                GetWindowText((HWND)lParam, bufor, 16);

                new_version = std::atoi(bufor);

                if (new_version < ARCHIVE_VERSION_MIN)
                {
                    new_version = ARCHIVE_VERSION_MIN;
                    invalid_version = true;
                }
                else if (new_version > ARCHIVE_VERSION_MAX)
                {
                    new_version = ARCHIVE_VERSION_MAX;
                    invalid_version = true;
                }

                if (lost_focus && invalid_version)
                {
                    updatingEditboxesNotByUser = true;

                    sprintf_s(bufor, 16, "%i", new_version);
                    SetWindowText((HWND)lParam, bufor);

                    updatingEditboxesNotByUser = false;
                }

                currentArchiveVersion = new_version;
            }
        }

        void buttonFunc_ArchiveVersionsList(WPARAM wParam, LPARAM lParam, void* custom_param)
        {
            int32_t a;
            char bufor[16];

            const int ELEPHANT_ENGINES = 7;

            const int AR_VERSIONS[ELEPHANT_ENGINES] =
            {
                0x87, 0x89, 0x90, 0x93, 0x9A, 0xA0, 0xB1
            };

            switch (HIWORD(wParam))
            {
                case LBN_SELCHANGE:
                {
                    a = SendMessage((HWND)lParam, LB_GETCURSEL, 0, 0);

                    if (a < 0)
                    {
                        a = 0;
                    }
                    else if (a >= ELEPHANT_ENGINES)
                    {
                        a = (ELEPHANT_ENGINES - 1);
                    }

                    /****************/

                    setMaxArchiveVersion(AR_VERSIONS[a]);

                    sprintf_s(bufor, 16, "%i", currentArchiveVersion);

                    GUI::updateArSettingsText(7, bufor);

                    /****************/

                    break;
                }
            }
        }

        void buttonFunc_Anim(WPARAM wParam, LPARAM lParam, void* custom_param)
        {
            int32_t i;
            char bufor[32];

            if ((!updatingEditboxesNotByUser) && (EN_CHANGE == HIWORD(wParam)))
            {
                GetWindowText((HWND)lParam, bufor, 32);

                i = std::atoi(bufor);

                if (0 == (int32_t)custom_param)
                {
                    if (i < 0) i = 0;

                    if (animationID != i)
                    {
                        animationID = i;
                        timerReset();
                    }
                }
                else if (1 == (int32_t)custom_param)
                {
                    if (i < 1) i = 1;

                    animationFPS = i;
                }
            }
        }

        void buttonFunc_NodesListChild(WPARAM wParam, LPARAM lParam, void* custom_param)
        {
            int32_t a = 0, b;

            switch (HIWORD(wParam))
            {
                case LBN_DBLCLK:
                {
                    a = 1;
                    break;
                }

                case LBN_SELCHANGE:
                case LBN_SELCANCEL:
                {
                    a = 2;
                    break;
                }
            }

            if (0 != a)
            {
                b = SendMessage((HWND)lParam, LB_GETCURSEL, 0, 0);

                switch (a)
                {
                    case 1:
                    {
                        a = (b == LB_ERR) ? NODES_LISTBOX_UPDATE_CURRENT : b;
                        b = 0;
                        break;
                    }

                    case 2:
                    {
                        a = NODES_LISTBOX_SET_MARKED_CHILD;
                        b = (b == LB_ERR) ? (-1) : b;
                        break;
                    }
                }

                myARs[currentArId].changeSelectedObject(a, (void*)b);
            }
        }

        void func_NodesListSwitchPage(int32_t direction)
        {
            char bufor[32];

            if (direction < 0)
            {
                nodesList_CurrentAction--;
            }
            else if (direction > 0)
            {
                nodesList_CurrentAction++;
            }

            if (nodesList_CurrentAction < 0)
            {
                nodesList_CurrentAction = 0;
            }
            else if (nodesList_CurrentAction >= nodesList_ActionsCount)
            {
                nodesList_CurrentAction = nodesList_ActionsCount - 1;
            }

            for (int32_t i = 0; i < nodesList_ButtonsCount; i++)
            {
                bool show_button = ((i >= nodesList_ActionIds[nodesList_CurrentAction][0])
                    && (i <= nodesList_ActionIds[nodesList_CurrentAction][1]));

                ShowWindow(nodesList_Windows[1 + i], show_button ? SW_SHOW : SW_HIDE);
            }

            sprintf_s(bufor, 32, "Actions: %s", nodesList_ActionNames[nodesList_CurrentAction]);

            SetWindowText(nodesList_Windows[0], bufor);
        }

        void menuFunc_NodesListEnter()
        {
            func_NodesListSwitchPage(0);
        }

        void buttonFunc_NodesListSwitchPage(WPARAM wParam, LPARAM lParam, void* custom_param)
        {
            if (BN_CLICKED == HIWORD(wParam))
            {
                func_NodesListSwitchPage((int32_t)custom_param);
            }
        }

        void buttonFunc_NodesListMisc(WPARAM wParam, LPARAM lParam, void* custom_param)
        {
            if (BN_CLICKED == HIWORD(wParam))
            {
                myARs[currentArId].changeSelectedObject((int32_t)custom_param, nullptr);
            }
        }

        void buttonFunc_NodesListObj(WPARAM wParam, LPARAM lParam, void* custom_param)
        {
            if (BN_CLICKED == HIWORD(wParam))
            {
                if (0 == (int32_t)custom_param)
                {
                    ArMenuOptions_ExportTrimeshToObj();
                }
                else if (1 == (int32_t)custom_param)
                {
                    ArMenuOptions_ImportTrimeshFromObj();
                }
            }
        }

        void buttonFunc_ResetTimer(WPARAM wParam, LPARAM lParam, void* custom_param)
        {
            if (BN_CLICKED == HIWORD(wParam))
            {
                timerReset();
            }
        }

        void buttonFunc_CameraReset(WPARAM wParam, LPARAM lParam, void* custom_param)
        {
            if (BN_CLICKED == HIWORD(wParam))
            {
                testCamera.reset(0, 0, 0);
            }
        }

        void buttonFunc_CameraSpeed(WPARAM wParam, LPARAM lParam, void* custom_param)
        {
            int32_t id = (int32_t)custom_param;
            double new_speed;
            char bufor[32];

            if ((!updatingEditboxesNotByUser) && (EN_CHANGE == HIWORD(wParam)) && (id >= 0) && (id < 2))
            {
                GetWindowText((HWND)lParam, bufor, 32);

                new_speed = std::atof(bufor);

                testCamera.speed[id] = (new_speed > 0) ? new_speed : TEST_CAMERA_DEFAULT_SPEED;
            }
        }

        void buttonFunc_BackgroundColor(WPARAM wParam, LPARAM lParam, void* custom_param)
        {
            int32_t id = (int32_t)custom_param;
            int32_t new_value;
            bool invalid_value = false;
            char bufor[8];

            if ((!updatingEditboxesNotByUser) && (EN_CHANGE == HIWORD(wParam)) && (id >= 0) && (id < 3))
            {
                GetWindowText((HWND)lParam, bufor, 8);

                new_value = std::atoi(bufor);

                if (new_value < 0)
                {
                    new_value = 0;
                    invalid_value = true;
                }
                else if (new_value > 255)
                {
                    new_value = 255;
                    invalid_value = true;
                }

                if (invalid_value)
                {
                    updatingEditboxesNotByUser = true;

                    sprintf_s(bufor, 8, "%d", new_value);
                    SetWindowText((HWND)lParam, bufor);

                    updatingEditboxesNotByUser = false;
                }

                backgroundColor[id] = new_value / 255.0f;
                updateSceneBackgroundColor();
            }
        }

        void buttonFunc_RenderFlags(WPARAM wParam, LPARAM lParam, void* custom_param)
        {
            if (BN_CLICKED == HIWORD(wParam))
            {
                int32_t index = (int32_t)custom_param;

                if (BST_CHECKED == SendMessage((HWND)lParam, BM_GETCHECK, 0, 0))
                {
                    if (0 == index)
                    {
                        renderingLimitFramerate = true;
                    }
                    else if (1 == index)
                    {
                        glPolygonMode(GL_FRONT, GL_LINE);
                    }
                    else if ((index >= (2 + 0)) && (index < (2 + drawFlags::DRAW_FLAG_COUNT)))
                    {
                        myDrawFlags |= (1 << (index - 2));
                    }
                }
                else
                {
                    if (0 == index)
                    {
                        renderingLimitFramerate = false;
                    }
                    else if (1 == index)
                    {
                        glPolygonMode(GL_FRONT, GL_FILL);
                    }
                    else if ((index >= (2 + 0)) && (index < (2 + drawFlags::DRAW_FLAG_COUNT)))
                    {
                        myDrawFlags &= (~ (1 << (index - 2)));
                    }
                }
            }
        }

        void buttonFunc_NodeType(WPARAM wParam, LPARAM lParam, void* custom_param)
        {
            char bufor[64];
            HWND type_name_window = NULL;

            if (BN_CLICKED == HIWORD(wParam))
            {
                type_name_window = theWindowsManager.getSpecificWindow(2, 1);

                if (NULL != type_name_window)
                {
                    GetWindowText(type_name_window, bufor, 64);

                    if (0x00 == (int32_t)custom_param)
                    {
                        theWindowsManager.displayMessage
                        (
                            WINDOWS_MANAGER_MESSAGE_WARNING,
                            "Changng object type is not supported yet."
                        );
                    }
                    else if (0x01 == (int32_t)custom_param)
                    {
                        myARs[currentArId].changeSelectedObject(NODES_EDITING_INSERT, bufor);
                    }
                }
            }
        }

        void buttonFunc_NodeName(WPARAM wParam, LPARAM lParam, void* custom_param)
        {
            char bufor[LARGE_BUFFER_SIZE];

            if ((!updatingEditboxesNotByUser) && (EN_CHANGE == HIWORD(wParam)))
            {
                GetWindowText((HWND)lParam, bufor, LARGE_BUFFER_SIZE);

                myARs[currentArId].changeSelectedObject(NODES_EDITING_CHANGE_NAME, bufor);
            }
        }

        void buttonFunc_NodeFlags(WPARAM wParam, LPARAM lParam, void* custom_param)
        {
            if (BN_CLICKED == HIWORD(wParam))
            {
                if (BST_CHECKED == SendMessage((HWND)lParam, BM_GETCHECK, 0, 0))
                {
                    myARs[currentArId].changeSelectedObject(NODES_EDITING_SET_FLAG, custom_param);
                }
                else
                {
                    myARs[currentArId].changeSelectedObject(NODES_EDITING_UNSET_FLAG, custom_param);
                }
            }
        }

        void buttonFunc_CurrentTransform(WPARAM wParam, LPARAM lParam, void* custom_param)
        {
            int32_t id = (int32_t)custom_param;
            char bufor[32];
            float dummy_float;
            eSRP customizable_xform;
            float dummy_angles[3];

            if ((!updatingEditboxesNotByUser) && (EN_CHANGE == HIWORD(wParam)) && (id >= 1) && (id <= 7))
            {
                GetWindowText((HWND)lParam, bufor, 32);
                dummy_float = (float)std::atof(bufor);

                GUI::getMovedSeletedTransform(&customizable_xform);

                switch (id)
                {
                    case 1: // pos.x
                    {
                        customizable_xform.pos.x = dummy_float;
                        break;
                    }

                    case 2: // pos.y
                    {
                        customizable_xform.pos.y = dummy_float;
                        break;
                    }

                    case 3: // pos.z
                    {
                        customizable_xform.pos.z = dummy_float;
                        break;
                    }

                    case 4: // Euler angle X
                    case 5: // Euler angle Y
                    case 6: // Euler angle Z
                    {
                        customizable_xform.rot.toEulerAngles(true, dummy_angles[0], dummy_angles[1], dummy_angles[2]);
                        dummy_angles[id - 4] = DEG2RAD_F(dummy_float);
                        customizable_xform.rot.fromEulerAngles(true, dummy_angles[0], dummy_angles[1], dummy_angles[2]);
                        break;
                    }

                    case 7: // scale
                    {
                        customizable_xform.scale = dummy_float;
                        break;
                    }
                }

                GUI::setMovedSeletedTransform(&customizable_xform, id);
            }
        }


        ////////////////////////////////////////////////////////////////
        // WindowsManager: overriden ListBox key dispatch
        ////////////////////////////////////////////////////////////////
        LRESULT WindowsManager::overriddenListboxKeyDispatch(HWND listbox_window, uint16_t keycode) const
        {
            int32_t a;

            if (getSpecificWindow(-2, (-1)) == listbox_window)
            {
                switch (keycode)
                {
                    case VK_RETURN:
                    {
                        a = SendMessage(listbox_window, LB_GETCURSEL, 0, 0);

                        a = (LB_ERR == a) ? NODES_LISTBOX_UPDATE_CURRENT : a;

                        myARs[currentArId].changeSelectedObject(a, nullptr);

                        return (-2);
                    }

                    case VK_BACK:
                    {
                        myARs[currentArId].changeSelectedObject(NODES_LISTBOX_PARENT, nullptr);

                        return (-2);
                    }


                    case VK_DELETE:
                    {
                        myARs[currentArId].changeSelectedObject(NODES_LISTBOX_DELETE_SELECTED, nullptr);
                        
                        return (-2);
                    }

                    case VK_F1:
                    {
                        myARs[currentArId].changeSelectedObject(NODES_LISTBOX_MOVE_UP, nullptr);

                        return (-2);
                    }

                    case VK_F2:
                    {
                        myARs[currentArId].changeSelectedObject(NODES_LISTBOX_MOVE_DOWN, nullptr);

                        return (-2);
                    }

                    case VK_F3:
                    {
                        myARs[currentArId].changeSelectedObject(NODES_LISTBOX_MOVE_IN, nullptr);

                        return (-2);
                    }

                    case VK_F4:
                    {
                        myARs[currentArId].changeSelectedObject(NODES_LISTBOX_MOVE_OUT, nullptr);

                        return (-2);
                    }

                    case VK_F5:
                    {
                        myARs[currentArId].changeSelectedObject(NODES_EDITING_CLONE_SELECTED, nullptr);

                        return (-2);
                    }

                    case VK_F6:
                    {
                        myARs[currentArId].changeSelectedObject(NODES_EDITING_CLONE_PASTING, nullptr);

                        return (-2);
                    }

                    case VK_F7:
                    {
                        myARs[currentArId].changeSelectedObject(NODES_EDITING_MATERIAL_CLONE, nullptr);

                        return (-2);
                    }

                    case VK_F8:
                    {
                        myARs[currentArId].changeSelectedObject(NODES_EDITING_MATERIAL_CHANGE, nullptr);

                        return (-2);
                    }

                    case VK_F9:
                    {
                        myARs[currentArId].changeSelectedObject(NODES_LISTBOX_COLLISION_REBUILD, nullptr);

                        return (-2);
                    }

                    case VK_F11:
                    {
                        myARs[currentArId].changeSelectedObject(NODES_LISTBOX_COLLISION_CLEAR, nullptr);

                        return (-2);
                    }
                }
            }

            /* Default action */
            return (-1);
        }


        ////////////////////////////////////////////////////////////////
        // Update ListBox of nodes
        // (-3) set label message
        // (-2) clears listbox
        // (-1) sets listbox selection
        // (0) adds children nodes to the listbox
        // (1) sets current node type
        // (2) sets current node name
        // (3) sets current node flags
        ////////////////////////////////////////////////////////////////
        void updateNodesList(int32_t mode, void* param)
        {
            int32_t a;
            WPARAM b;

            const char* new_text = "";
            HWND label = theWindowsManager.getSpecificWindow(-2, 0);
            HWND listbox = theWindowsManager.getSpecificWindow(-2, (-1));
            HWND test_hwnd;

            if (((-3) == mode) && (NULL != label))
            {
                if (nullptr != param)
                {
                    new_text = (char*)param;
                }

                SetWindowText(label, new_text);
            }
            else if ((mode <= 0) && (NULL != listbox))
            {
                if ((-2) == mode)
                {
                    SendMessage(listbox, LB_RESETCONTENT, 0, 0);
                }
                else if ((-1) == mode)
                {
                    SendMessage(listbox, LB_SETCURSEL, (WPARAM)param, 0);
                }
                else if (0 == mode)
                {
                    if (nullptr != param)
                    {
                        new_text = (char*)param;
                    }

                    SendMessage(listbox, LB_ADDSTRING, 0, (LPARAM)new_text);
                }
            }
            else if ((1 == mode) || (2 == mode))
            {
                updatingEditboxesNotByUser = true;

                if (nullptr != param)
                {
                    new_text = (char*)param;
                }

                test_hwnd = theWindowsManager.getSpecificWindow(2, (1 == mode) ? 1 : 5);

                if (NULL != test_hwnd)
                {
                    SetWindowText(test_hwnd, new_text);
                }

                updatingEditboxesNotByUser = false;
            }
            else if (3 == mode)
            {
                for (a = 0; a < 32; a++)
                {
                    test_hwnd = theWindowsManager.getSpecificWindow(2, (7 + a));

                    if (NULL != test_hwnd)
                    {
                        b = ((0x01 << a) & (int32_t)param) ? BST_CHECKED : BST_UNCHECKED;

                        SendMessage(test_hwnd, BM_SETCHECK, b, 0);
                    }
                }
            }
        }


        ////////////////////////////////////////////////////////////////
        // Update EditBoxes with specific text
        // (0) "MediaDir"
        // (1) "DenisDir"
        // (2) "LevelName"
        // (3) "CameraMovementSpeed"
        // (4) "CameraRotationSpeed"
        // (5) "DrawFlags" (CheckBoxes)
        // (6) "BackgroundColor"
        // (7) "ArchiveVersion"
        ////////////////////////////////////////////////////////////////
        void updateArSettingsText(int32_t id, const char* new_text)
        {
            char bufor[32];

            HWND dummy_window;
            int32_t page_id, window_id;
            char* destination_copy = nullptr;
            int32_t camera_speed_id = (-1);

            eString colors_str[5];
            int32_t colors[3];

            if (nullptr == new_text)
            {
                new_text = "";
            }

            switch (id)
            {
                case 0: // "MediaDir"
                {
                    page_id = 1;
                    window_id = 1;

                    destination_copy = mediaDirectory;
                    break;
                }

                case 1: // "DenisDir"
                {
                    page_id = 1;
                    window_id = 3;

                    destination_copy = denisDirectory;
                    break;
                }

                case 2: // "LevelName"
                {
                    page_id = 1;
                    window_id = 5;

                    destination_copy = denisLevelName;
                    break;
                }

                case 3: // "CameraMovementSpeed"
                {
                    page_id = 0;
                    window_id = 25;

                    camera_speed_id = 0;
                    break;
                }

                case 4: // "CameraRotationSpeed"
                {
                    page_id = 0;
                    window_id = 26;

                    camera_speed_id = 1;
                    break;
                }

                case 5: // "DrawFlags"
                {
                    myDrawFlags = std::atoi(new_text);

                    for (window_id = (2 + 0); window_id < (2 + drawFlags::DRAW_FLAG_COUNT); window_id++)
                    {
                        if (NULL != (dummy_window = theWindowsManager.getSpecificWindow(0, window_id)))
                        {
                            SendMessage(dummy_window, BM_SETCHECK, (0x01 & (myDrawFlags >> (window_id - 2))) ? BST_CHECKED : BST_UNCHECKED, 0);
                        }
                    }

                    return;
                }

                case 6: // "BackgroundColor"
                {
                    colors_str[4] = new_text;

                    if (ArFunctions::splitString(colors_str[4], colors_str, 4) >= 3)
                    {
                        updatingEditboxesNotByUser = true;

                        for (window_id = 0; window_id < 3; window_id++)
                        {
                            colors[window_id] = std::atoi(colors_str[window_id].getText());

                            if (colors[window_id] < 0)
                            {
                                colors[window_id] = 0;
                            }
                            else if (colors[window_id] > 255)
                            {
                                colors[window_id] = 255;
                            }

                            if (NULL != (dummy_window = theWindowsManager.getSpecificWindow(0, (19 + window_id))))
                            {
                                sprintf_s(bufor, 32, "%d", colors[window_id]);
                                SetWindowText(dummy_window, bufor);
                            }

                            backgroundColor[window_id] = colors[window_id] / 255.0f;
                        }

                        updateSceneBackgroundColor();

                        updatingEditboxesNotByUser = false;
                    }

                    return;
                }

                case 7: // "ArchiveVersion"
                {
                    if (NULL != (dummy_window = theWindowsManager.getSpecificWindow(1, 11)))
                    {
                        updatingEditboxesNotByUser = true;

                        SetWindowText(dummy_window, new_text);

                        updatingEditboxesNotByUser = false;
                    }

                    return;
                }

                default:
                {
                    return;
                }
            }

            if (NULL != (dummy_window = theWindowsManager.getSpecificWindow(page_id, window_id)))
            {
                updatingEditboxesNotByUser = true;

                if (nullptr != destination_copy)
                {
                    SetWindowText(dummy_window, new_text);

                    strcpy_s(destination_copy, LARGE_BUFFER_SIZE, new_text);
                }
                else if ((camera_speed_id >= 0) && (camera_speed_id < 2))
                {
                    testCamera.speed[camera_speed_id] = std::atof(new_text);

                    if (testCamera.speed[camera_speed_id] <= 0)
                    {
                        testCamera.speed[camera_speed_id] = TEST_CAMERA_DEFAULT_SPEED;
                    }

                    sprintf_s(bufor, 32, "%f", testCamera.speed[camera_speed_id]);

                    SetWindowText(dummy_window, bufor);
                }

                updatingEditboxesNotByUser = false;
            }
        }


        ////////////////////////////////////////////////////////////////
        // Create windows
        ////////////////////////////////////////////////////////////////

        bool createWindow_linePause()
        {
            int32_t y;
            const int WINDOW_PADDING_SMALL = 8;

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | SS_ETCHEDHORZ);
            theWindowsManager.getCurrentPosition(nullptr, &y);
            theWindowsManager.setCurrentPosition(0, (y + WINDOW_PADDING_SMALL - 2));

            if (0 == theWindowsManager.addWindow("", RECT_LOGO_X2, 2, nullptr, 0, 0x01))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(0, WINDOW_PADDING_SMALL);

            return true;
        }

        bool createWindows(HINSTANCE hInstance)
        {
            int32_t a, b, x, y;
            char bufor[64];
            HMENU menu_bar, test_menu;
            HWND main_window, scroll_window, dummy_window;

            const int WINDOW_HEIGHT = 24;
            const int WINDOW_PADDING = 16;
            const int WINDOW_PADDING_SMALL = 8;
            const int TOP_OFFSET = 8;
            const int NODES_BUTTON_HEIGHT = (int)(2.25 * WINDOW_HEIGHT);
            const int LARGE_BUTTON_WIDTH = ((RECT_TABS_X2 - (2 - 1) * WINDOW_PADDING_SMALL) / 2);
            const int SMALL_EDITBOX_WIDTH = ((RECT_TABS_X2 - (3 - 1) * WINDOW_PADDING_SMALL) / 3);

            const char* WELCOME_MESSAGE = \
                "Camera movement:\n" \
                " - LMB for rotation\n" \
                " - RMB or [W][A][S][D] for strafing\n" \
                "\n" \
                "This project is in alpha stage.";

            /********************************/
            /* Prepare manager (1/2) */

            updatingEditboxesNotByUser = true;

            theWindowsManager.reset();
            theWindowsManager.setCurrentModuleInstance(hInstance);

            /********************************/
            /* Load fonts and resources */

            myWindowLogo = LoadBitmap(hInstance, MAKEINTRESOURCE(IDM_BITMAP));

            if (NULL == myWindowLogo)
            {
                return false;
            }

            myWindowFont = CreateFont
            (
                16, 0, 0, 0,
                FW_NORMAL,
                FALSE, FALSE, FALSE,
                DEFAULT_CHARSET,
                OUT_DEFAULT_PRECIS,
                CLIP_DEFAULT_PRECIS,
                DEFAULT_QUALITY,
                (DEFAULT_PITCH | FF_SWISS),
                "Verdana"
            );

            if (NULL == myWindowFont)
            {
                return false;
            }

            /********************************/
            /* Prepare manager (2/2) */

            if (false == theWindowsManager.createMainWindows())
            {
                return false;
            }

            main_window = theWindowsManager.getMainWindow();
            scroll_window = theWindowsManager.getScrollWindow();

            theWindowsManager.setCurrentParent(scroll_window);
            theWindowsManager.setCurrentPadding(0, 0);

            /********************************/
            /* [MENU BAR] */

            menu_bar = CreateMenu();

            test_menu = CreateMenu();
            AppendMenu(test_menu, MF_STRING, (UINT_PTR)theWindowsManager.addStaticFunction(menuFunc_DenisConvert, (void*)MENUFUNC_DENISCONVERT_OPENLVL), "&Open level");
            AppendMenu(test_menu, MF_STRING, (UINT_PTR)theWindowsManager.addStaticFunction(menuFunc_DenisConvert, (void*)MENUFUNC_DENISCONVERT_CONVERT), "&Convert level");
            AppendMenu(menu_bar, MF_POPUP, (UINT_PTR)test_menu, "Denis the Kangaroo");

            test_menu = CreateMenu();
            AppendMenu(test_menu, MF_STRING, (UINT_PTR)theWindowsManager.addStaticFunction(menuFunc_ArMenuBar, (void*)MENUFUNC_ARMENUBAR_OPEN),        "Open Archive");
            AppendMenu(test_menu, MF_STRING, (UINT_PTR)theWindowsManager.addStaticFunction(menuFunc_ArMenuBar, (void*)MENUFUNC_ARMENUBAR_SAVE),        "Save Archive");
            AppendMenu(test_menu, MF_STRING, (UINT_PTR)theWindowsManager.addStaticFunction(menuFunc_ArMenuBar, (void*)MENUFUNC_ARMENUBAR_CLOSE),       "Close Archive");
            AppendMenu(test_menu, MF_STRING, (UINT_PTR)theWindowsManager.addStaticFunction(menuFunc_ArMenuBar, (void*)MENUFUNC_ARMENUBAR_GENERATE),    "Generate empty scene");
            AppendMenu(test_menu, MF_STRING, (UINT_PTR)theWindowsManager.addStaticFunction(menuFunc_ArMenuBar, (void*)MENUFUNC_ARMENUBAR_PARSER),      "Parse instructions");
            AppendMenu(test_menu, MF_STRING, (UINT_PTR)theWindowsManager.addStaticFunction(menuFunc_ArMenuBar, (void*)MENUFUNC_ARMENUBAR_SAVESCRIPTS), "Export Scripts");
            AppendMenu(test_menu, MF_STRING, (UINT_PTR)theWindowsManager.addStaticFunction(menuFunc_ArMenuBar, (void*)MENUFUNC_ARMENUBAR_SAVEXREF),    "Export Proxies");
            AppendMenu(test_menu, MF_STRING, (UINT_PTR)theWindowsManager.addStaticFunction(menuFunc_ArMenuBar, (void*)MENUFUNC_ARMENUBAR_LOADXREF),    "Reload Proxies");
            AppendMenu(test_menu, MF_STRING, (UINT_PTR)theWindowsManager.addStaticFunction(menuFunc_ArMenuBar, (void*)MENUFUNC_ARMENUBAR_BULKCONVERT), "Bulk Archive Converter");
            AppendMenu(test_menu, MF_STRING, (UINT_PTR)theWindowsManager.addStaticFunction(menuFunc_ArMenuBar, (void*)MENUFUNC_ARMENUBAR_SAVESTRUCT),  "Export JSON document");
            AppendMenu(test_menu, MF_STRING, (UINT_PTR)theWindowsManager.addStaticFunction(menuFunc_ArMenuBar, (void*)MENUFUNC_ARMENUBAR_SAVECOLLADA), "Export COLLADA dae");
            AppendMenu(menu_bar, MF_POPUP, (UINT_PTR)test_menu, "Kao the Kangaroo: Round 2");

            SetMenu(main_window, menu_bar);

			/********************************/
			/* Main scroll window */

			theWindowsManager.setCurrentParent(theWindowsManager.getScrollWindow());

            /********************************/
            /* [PAGE 0] */

            theWindowsManager.addPage("Render settings", nullptr, nullptr);

            theWindowsManager.setCurrentPosition(RECT_TABS_X1, TOP_OFFSET);
            theWindowsManager.updateReturningPosition();

            /********************************/
            /* [PAGE 0] (0 – 16) Create checkboxes */

            theWindowsManager.setCurrentClassName("BUTTON");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | BS_AUTOCHECKBOX);

            const int RENDER_FLAGS_COUNT = 2 + drawFlags::DRAW_FLAG_COUNT;

            const char* render_flags_names[RENDER_FLAGS_COUNT] =
            {
                "Limit rendering framerate (30 fps)",
                "WIREFRAME MODE",

                "Outline SELECTED NODES",
                "Render INVISIBLE MESHES",
                "DrawPass #1",
                "DrawPass #2",
                "DrawPass #3",
                "Render with TEXTURES",
                "Render with MATERIAL BLENDING",
                "Render with FRUSTUM TESTING",
                "Render with VERTEX COLORS",
                "Render with DYNAMIC LIGHTS",
                "Update ANIMATIONS",
                "Objects: BOX ZONES",
                "Objects: PROXIES",
                "Objects: COLLISION",
                "Objects: SPECIAL HELPERS"
            };

            for (a = 0; a < RENDER_FLAGS_COUNT; a++)
            {
                if (0 == (dummy_window = theWindowsManager.addWindow(render_flags_names[a], RECT_TABS_X2, WINDOW_HEIGHT, buttonFunc_RenderFlags, (void*)a, 0x01)))
                {
                    return false;
                }

                switch (a)
                {
                    case (2 + 2): // "DrawPass #1"
                    case (2 + 3): // "DrawPass #2"
                    case (2 + 5): // "Render with TEXTURES"
                    case (2 + 7): // "Render with FRUSTUM TESTING"
                    {
                        SendMessage(dummy_window, BM_SETCHECK, BST_CHECKED, 0);
                        myDrawFlags |= (1 << (a - 2));

                        break;
                    }
                }
            }

            theWindowsManager.offsetCurrentPosition(0, WINDOW_PADDING);

            /********************************/
            /* [PAGE 0] (17) Create line decoration */

            if (!createWindow_linePause())
            {
                return false;
            }

            /********************************/
            /* [PAGE 0] (18) Create dummy label */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == theWindowsManager.addWindow("Background color (Red, Green, Blue):", RECT_TABS_X2, WINDOW_HEIGHT, nullptr, nullptr, 0x01))
            {
                return false;
            }

            /********************************/
            /* [PAGE 0] (19-21) Create editboxes */

            theWindowsManager.setCurrentClassName("EDIT");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | ES_AUTOHSCROLL);

            for (a = 0; a < 3; a++)
            {
                sprintf_s(bufor, 64, "%d", (int)(255 * backgroundColor[a]));

                theWindowsManager.addEdgesToNextWindow();
                if (0 == theWindowsManager.addWindow(bufor, SMALL_EDITBOX_WIDTH, WINDOW_HEIGHT, buttonFunc_BackgroundColor, (void*)a, (a < 2) ? 0x00 : 0x01))
                {
                    return false;
                }

                if (a < 2)
                {
                    theWindowsManager.offsetCurrentPosition(WINDOW_PADDING_SMALL, 0);
                }
                else
                {
                    theWindowsManager.offsetCurrentPosition(0, WINDOW_PADDING_SMALL);
                }
            }

            /********************************/
            /* [PAGE 0] (22) Create line decoration */

            if (!createWindow_linePause())
            {
                return false;
            }

            /********************************/
            /* [PAGE 0] (23) Create button */

            theWindowsManager.setCurrentClassName("BUTTON");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | BS_DEFPUSHBUTTON);

            if (0 == theWindowsManager.addWindow("Reset Camera", RECT_TABS_X2, WINDOW_HEIGHT, buttonFunc_CameraReset, nullptr, 0x01))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(0, WINDOW_PADDING);

            /********************************/
            /* [PAGE 0] (24) Create dummy label */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == theWindowsManager.addWindow("Camera movement and rotation speed:", RECT_TABS_X2, WINDOW_HEIGHT, nullptr, nullptr, 0x01))
            {
                return false;
            }

            /********************************/
            /* [PAGE 0] (25-26) Create editboxes */

            theWindowsManager.setCurrentClassName("EDIT");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | ES_AUTOHSCROLL);

            theWindowsManager.addEdgesToNextWindow();
            if (0 == theWindowsManager.addWindow(TEST_CAMERA_DEFAULT_SPEED_TEXT, LARGE_BUTTON_WIDTH, WINDOW_HEIGHT, buttonFunc_CameraSpeed, (void*)0, 0))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(WINDOW_PADDING_SMALL, 0);

            theWindowsManager.addEdgesToNextWindow();
            if (0 == theWindowsManager.addWindow(TEST_CAMERA_DEFAULT_SPEED_TEXT, LARGE_BUTTON_WIDTH, WINDOW_HEIGHT, buttonFunc_CameraSpeed, (void*)1, 0x01))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(0, WINDOW_PADDING);

            /********************************/
            /* [PAGE 0] (27) Create line decoration */

            if (!createWindow_linePause())
            {
                return false;
            }

            /********************************/
            /* [PAGE 0] (28) Create dummy label */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == theWindowsManager.addWindow("Animation ID", RECT_TABS_X2, WINDOW_HEIGHT, nullptr, nullptr, 0x01))
            {
                return false;
            }

            /********************************/
            /* [PAGE 0] (29) Create editbox */

            theWindowsManager.setCurrentClassName("EDIT");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | ES_AUTOHSCROLL);

            theWindowsManager.addEdgesToNextWindow();
            if (0 == theWindowsManager.addWindow("0", RECT_TABS_X2, WINDOW_HEIGHT, buttonFunc_Anim, (void*)0, 0x01))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(0, WINDOW_PADDING);

            /********************************/
            /* [PAGE 0] (30) Create button */

            theWindowsManager.setCurrentClassName("BUTTON");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | BS_DEFPUSHBUTTON);

            if (0 == theWindowsManager.addWindow("Reset Timer", RECT_TABS_X2, WINDOW_HEIGHT, buttonFunc_ResetTimer, nullptr, 0x01))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(0, WINDOW_PADDING);

            /********************************/
            /* [PAGE 0] (31) Create dummy label */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == theWindowsManager.addWindow("Frames per second", RECT_TABS_X2, WINDOW_HEIGHT, nullptr, nullptr, 0x01))
            {
                return false;
            }

            /********************************/
            /* [PAGE 0] (32) Create editbox */

            theWindowsManager.setCurrentClassName("EDIT");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | ES_AUTOHSCROLL);

            theWindowsManager.addEdgesToNextWindow();
            if (0 == theWindowsManager.addWindow(ANIMATION_FRAMERATE_DEFAULT_TEXT, RECT_TABS_X2, WINDOW_HEIGHT, buttonFunc_Anim, (void*)1, 0x01))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(0, WINDOW_PADDING);

            /********************************/
            /* [PAGE 0] (33) Create line decoration */

            if (!createWindow_linePause())
            {
                return false;
            }

            /********************************/
            /* [PAGE 0] (34) Create dummy label */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == theWindowsManager.addWindow(WELCOME_MESSAGE, RECT_TABS_X2, (5 * WINDOW_HEIGHT), nullptr, nullptr, 0))
            {
                return false;
            }

            /********************************/
            /* [PAGE 1] */

            theWindowsManager.addPage("theAR + Denis", nullptr, nullptr);

            theWindowsManager.setCurrentPosition(RECT_TABS_X1, TOP_OFFSET);

            /********************************/
            /* [PAGE 1] (0) Create dummy label */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == theWindowsManager.addWindow("Working directory (\"/media/\"):", RECT_TABS_X2, WINDOW_HEIGHT, nullptr, nullptr, 0x01))
            {
                return false;
            }

            /********************************/
            /* [PAGE 1] (1) Create editbox */

            theWindowsManager.setCurrentClassName("EDIT");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | ES_AUTOHSCROLL);

            theWindowsManager.addEdgesToNextWindow();
            if (0 == theWindowsManager.addWindow("", RECT_TABS_X2, WINDOW_HEIGHT, buttonFunc_EditBoxTyping, (void*)mediaDirectory, 0x01))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(0, WINDOW_PADDING);

            /********************************/
            /* [PAGE 1] (2) Create dummy label */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == theWindowsManager.addWindow("Denis game directory:", RECT_TABS_X2, WINDOW_HEIGHT, nullptr, nullptr, 0x01))
            {
                return false;
            }

            /********************************/
            /* [PAGE 1] (3) Create editbox */

            theWindowsManager.setCurrentClassName("EDIT");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | ES_AUTOHSCROLL);

            theWindowsManager.addEdgesToNextWindow();
            if (0 == theWindowsManager.addWindow("", RECT_TABS_X2, WINDOW_HEIGHT, buttonFunc_EditBoxTyping, (void*)denisDirectory, 0x01))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(0, WINDOW_PADDING);

            /********************************/
            /* [PAGE 1] (4) Create dummy label */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == theWindowsManager.addWindow("Denis Level Name / New Scene Name\n / Last Ar Name:", RECT_TABS_X2, (2 * WINDOW_HEIGHT), nullptr, nullptr, 0x01))
            {
                return false;
            }

            /********************************/
            /* [PAGE 1] (5) Create editbox */

            theWindowsManager.setCurrentClassName("EDIT");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | ES_AUTOHSCROLL);

            theWindowsManager.addEdgesToNextWindow();
            if (0 == theWindowsManager.addWindow("", RECT_TABS_X2, WINDOW_HEIGHT, buttonFunc_EditBoxTyping, (void*)denisLevelName, 0x01))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(0, WINDOW_PADDING);

            /********************************/
            /* [PAGE 1] (6) Create line decoration */

            if (!createWindow_linePause())
            {
                return false;
            }

            /********************************/
            /* [PAGE 1] (7) Create dummy label */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == theWindowsManager.addWindow("Choose an Archive:", RECT_TABS_X2, WINDOW_HEIGHT, nullptr, nullptr, 0x01))
            {
                return false;
            }

            /********************************/
            /* [PAGE 1] (8) Create listbox */

            theWindowsManager.setCurrentClassName("LISTBOX");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | WS_HSCROLL | WS_VSCROLL | LBS_DISABLENOSCROLL | LBS_HASSTRINGS | LBS_NOTIFY);

            theWindowsManager.addEdgesToNextWindow();
            if (0 == (dummy_window = theWindowsManager.addWindow("", RECT_TABS_X2, 128, buttonFunc_ArchivesList, nullptr, 0x01)))
            {
                return false;
            }

            SendMessage(dummy_window, LB_SETHORIZONTALEXTENT, (WPARAM)512, 0);

            for (a = 0; a < MAX_OPEN_ARCHIVES; a++)
            {
                SendMessage(dummy_window, LB_ADDSTRING, 0, (LPARAM)"<< EMPTY >>");
            }

            SendMessage(dummy_window, LB_SETCURSEL, (WPARAM)0, 0);

            /********************************/
            /* [PAGE 1] (9) Create line decoration */

            if (!createWindow_linePause())
            {
                return false;
            }

            /********************************/
            /* [PAGE 1] (10) Create dummy label */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == theWindowsManager.addWindow("Current Archive (engine) version:", RECT_TABS_X2, WINDOW_HEIGHT, nullptr, nullptr, 0x01))
            {
                return false;
            }

            /********************************/
            /* [PAGE 1] (11) Create editbox */

            theWindowsManager.setCurrentClassName("EDIT");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | ES_AUTOHSCROLL);

            sprintf_s(bufor, 64, "%d", ARCHIVE_VERSION_MAX);

            theWindowsManager.addEdgesToNextWindow();
            if (0 == theWindowsManager.addWindow(bufor, SMALL_EDITBOX_WIDTH, WINDOW_HEIGHT, buttonFunc_ArchiveVersionsEdit, nullptr, 0x01))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(0, WINDOW_PADDING_SMALL);

            /********************************/
            /* [PAGE 1] (12) Create listbox */

            theWindowsManager.setCurrentClassName("LISTBOX");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | WS_HSCROLL | WS_VSCROLL | LBS_DISABLENOSCROLL | LBS_HASSTRINGS | LBS_NOTIFY);

            theWindowsManager.addEdgesToNextWindow();
            if (0 == (dummy_window = theWindowsManager.addWindow("", RECT_TABS_X2, 128, buttonFunc_ArchiveVersionsList, nullptr, 0x01)))
            {
                return false;
            }

            SendMessage(dummy_window, LB_SETHORIZONTALEXTENT, (WPARAM)384, 0);

            SendMessage(dummy_window, LB_ADDSTRING, 0, (LPARAM)"\"Kangurek Kao: Runda 2\" (2003, PC);");
            SendMessage(dummy_window, LB_ADDSTRING, 0, (LPARAM)"\"Kao the Kangaroo: Round 2\"  (2003, PC);");
            SendMessage(dummy_window, LB_ADDSTRING, 0, (LPARAM)"\"Kao: Tajemnica Wulkanu\"  (2006, PC);");
            SendMessage(dummy_window, LB_ADDSTRING, 0, (LPARAM)"\"Asterix & Obelix XXL 2: Mission WiFix\"  (2006, PSP);)");
            SendMessage(dummy_window, LB_ADDSTRING, 0, (LPARAM)"\"Lanfeust of Troy\"  (2008, PSP);");
            SendMessage(dummy_window, LB_ADDSTRING, 0, (LPARAM)"\"My Horse and Me 2\"  (2008, PC);");
            SendMessage(dummy_window, LB_ADDSTRING, 0, (LPARAM)"\"The Saddle Club\"  (2010, PC);");

            /********************************/
            /* [PAGE 2] */

            theWindowsManager.addPage("Node editing", nullptr, nullptr);

            theWindowsManager.setCurrentPosition(RECT_TABS_X1, TOP_OFFSET);

            /********************************/
            /* [PAGE 2] (0) Create dummy label */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == theWindowsManager.addWindow("\"eNode\" type:", RECT_TABS_X2, WINDOW_HEIGHT, nullptr, nullptr, 0x01))
            {
                return false;
            }

            /********************************/
            /* [PAGE 2] (1) Create editbox */

            theWindowsManager.setCurrentClassName("EDIT");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | ES_AUTOHSCROLL);

            theWindowsManager.addEdgesToNextWindow();
            if (0 == theWindowsManager.addWindow("", RECT_TABS_X2, WINDOW_HEIGHT, nullptr, nullptr, 0x01))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(0, WINDOW_PADDING);

            /********************************/
            /* [PAGE 2] (2 – 3) Create buttons */

            theWindowsManager.setCurrentClassName("BUTTON");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | BS_DEFPUSHBUTTON);

            theWindowsManager.setCurrentPadding(WINDOW_PADDING_SMALL, WINDOW_PADDING_SMALL);

            if (0 == theWindowsManager.addWindow("Change Type", LARGE_BUTTON_WIDTH, WINDOW_HEIGHT, buttonFunc_NodeType, (void*)0x00, 0))
            {
                return false;
            }

            if (0 == theWindowsManager.addWindow("Add New Node", LARGE_BUTTON_WIDTH, WINDOW_HEIGHT, buttonFunc_NodeType, (void*)0x01, 0x01))
            {
                return false;
            }

            theWindowsManager.setCurrentPadding(0, 0);
            theWindowsManager.offsetCurrentPosition(0, WINDOW_PADDING_SMALL);

            /********************************/
            /* [PAGE 2] (4) Create dummy label */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == theWindowsManager.addWindow("\"eNode\" name:", RECT_TABS_X2, WINDOW_HEIGHT, nullptr, nullptr, 0x01))
            {
                return false;
            }

            /********************************/
            /* [PAGE 2] (5) Create editbox */

            theWindowsManager.setCurrentClassName("EDIT");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | ES_AUTOHSCROLL);

            theWindowsManager.addEdgesToNextWindow();
            if (0 == theWindowsManager.addWindow("", RECT_TABS_X2, WINDOW_HEIGHT, buttonFunc_NodeName, nullptr, 0x01))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(0, WINDOW_PADDING);

            /********************************/
            /* [PAGE 2] (6) Create dummy label */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == theWindowsManager.addWindow("\"eNode\" flags:", RECT_TABS_X2, WINDOW_HEIGHT, nullptr, nullptr, 0x01))
            {
                return false;
            }

            /********************************/
            /* [PAGE 2] (7 – 38) Create checkboxes */

            theWindowsManager.setCurrentClassName("BUTTON");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | BS_AUTOCHECKBOX);

            for (a = 0; a < 32; a++)
            {
                b = (0x01 << a);
                sprintf_s(bufor, 64, "(0x%08X) %s", b, theNodeFlagNames[a]);

                if (0 == theWindowsManager.addWindow(bufor, RECT_TABS_X2, WINDOW_HEIGHT, buttonFunc_NodeFlags, (void*)b, 0x01))
                {
                    return false;
                }
            }

            /********************************/
            /* [PAGE 3] */

            if (false == materialsManager_AddWindows())
            {
                return false;
            }

            /********************************/
            /* [PAGE 4] */

            theWindowsManager.addPage("Object movement", nullptr, nullptr);

            theWindowsManager.setCurrentPosition(RECT_TABS_X1, TOP_OFFSET);

            if (false == theWindowsManager.createObjectMovementWindows())
            {
                return false;
            }

            /********************************/
            /* [PAGE 4] Create line decoration */

            if (!createWindow_linePause())
            {
                return false;
            }

            /********************************/
            /* [PAGE 4] (18) Create dummy labels */

            theWindowsManager.setCurrentClassName("STATIC");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD);

            if (0 == theWindowsManager.addWindow("EDITING THE TRANSFORMATION\n  OF THE CURRENTLY MOVED OBJECT", RECT_TABS_X2, (2 * WINDOW_HEIGHT), nullptr, nullptr, 0x03))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(0, WINDOW_PADDING_SMALL);

            if (0 == theWindowsManager.addWindow("Position [X Y Z]", LARGE_BUTTON_WIDTH, WINDOW_HEIGHT, nullptr, nullptr, 0))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(WINDOW_PADDING, 0);

            if (0 == theWindowsManager.addWindow("Rotation [X Y Z]", LARGE_BUTTON_WIDTH, WINDOW_HEIGHT, nullptr, nullptr, 0x01))
            {
                return false;
            }

            theWindowsManager.getCurrentPosition(&x, &y);

            theWindowsManager.offsetCurrentPosition(0, 3 * (WINDOW_HEIGHT + WINDOW_PADDING_SMALL));

            if (0 == theWindowsManager.addWindow("Scale", LARGE_BUTTON_WIDTH, WINDOW_HEIGHT, nullptr, nullptr, 0x02))
            {
                return false;
            }

            /********************************/
            /* [PAGE 4] (19-20) Create editboxes */

            theWindowsManager.setCurrentClassName("EDIT");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | ES_AUTOHSCROLL);

            theWindowsManager.setCurrentPadding(WINDOW_PADDING, WINDOW_PADDING_SMALL);

            theWindowsManager.setCurrentPosition(x, y);

            for (b = 0; b < 3; b++)
            {
                theWindowsManager.addEdgesToNextWindow();
                if (0 == theWindowsManager.addWindow("", LARGE_BUTTON_WIDTH, WINDOW_HEIGHT, buttonFunc_CurrentTransform, (void*)(b + 1), 0))
                {
                    return false;
                }

                theWindowsManager.addEdgesToNextWindow();
                if (0 == theWindowsManager.addWindow("", LARGE_BUTTON_WIDTH, WINDOW_HEIGHT, buttonFunc_CurrentTransform, (void*)(b + 4), 0x01))
                {
                    return false;
                }
            }

            theWindowsManager.offsetCurrentPosition(0, WINDOW_HEIGHT);

            theWindowsManager.addEdgesToNextWindow();
            if (0 == theWindowsManager.addWindow("", LARGE_BUTTON_WIDTH, WINDOW_HEIGHT, buttonFunc_CurrentTransform, (void*)(7), 0x03))
            {
                return false;
            }

            theWindowsManager.offsetCurrentPosition(0, WINDOW_PADDING);

            theWindowsManager.setCurrentPadding(0, 0);

            /********************************/
            /* [PAGE 0] (21) Create line decoration */

            if (!createWindow_linePause())
            {
                return false;
            }

            /********************************/
            /* [PAGE 4] Create buttons */

            theWindowsManager.setCurrentClassName("BUTTON");
            theWindowsManager.setCurrentStyleFlags(WS_CHILD | BS_DEFPUSHBUTTON);

            theWindowsManager.setCurrentPadding(WINDOW_PADDING, WINDOW_PADDING_SMALL);

            if (0 == theWindowsManager.addWindow("Reset", LARGE_BUTTON_WIDTH, WINDOW_HEIGHT, buttonFunc_NodesListMisc, (void*)NODES_EDITING_RESET_TRANSFORM, 0))
            {
                return false;
            }

            if (0 == theWindowsManager.addWindow("Apply", LARGE_BUTTON_WIDTH, WINDOW_HEIGHT, buttonFunc_NodesListMisc, (void*)NODES_EDITING_APPLY_TRANSFORM, 0x01))
            {
                return false;
            }

            theWindowsManager.setCurrentPadding(0, 0);
            theWindowsManager.offsetCurrentPosition(0, WINDOW_PADDING_SMALL);

			/********************************/
			/* Node tree scroll window */

			theWindowsManager.setCurrentParent(theWindowsManager.getNodeTreeWindow());
			theWindowsManager.setCurrentPosition(RECT_TABS_X1, TOP_OFFSET);
			theWindowsManager.setCurrentPageNumber(-2);

			/********************************/
			/* [Node tree] (0) Create dummy label */

			theWindowsManager.setCurrentClassName("STATIC");
			theWindowsManager.setCurrentStyleFlags(WS_CHILD | WS_VISIBLE);

			if (0 == theWindowsManager.addWindow("( no archive loaded yet\n or the parent item is not a node )", RECT_TABS_X2, (4 * WINDOW_HEIGHT), nullptr, nullptr, 0x01))
			{
				return false;
			}

			/********************************/
			/* [Node tree] (1) Create line decoration */

			if (!createWindow_linePause())
			{
				return false;
			}

			/********************************/
			/* [Node tree] (2 – 4) Create action switching buttons */

			nodesList_CurrentAction = 0;

			theWindowsManager.setCurrentClassName("BUTTON");
			theWindowsManager.setCurrentStyleFlags(WS_CHILD | BS_DEFPUSHBUTTON | WS_VISIBLE);

			theWindowsManager.setCurrentPadding(WINDOW_PADDING_SMALL, WINDOW_PADDING_SMALL);

			if (0 == theWindowsManager.addWindow("<<", 24, 20, buttonFunc_NodesListSwitchPage, (void*)(-1), 0))
			{
				return false;
			}

			if (0 == theWindowsManager.addWindow(">>", 24, 20, buttonFunc_NodesListSwitchPage, (void*)(1), 0))
			{
				return false;
			}

			theWindowsManager.setCurrentClassName("STATIC");
			theWindowsManager.setCurrentStyleFlags(WS_CHILD | WS_VISIBLE);

			if (0 == (nodesList_Windows[0] = theWindowsManager.addWindow("", (RECT_TABS_X2 - 2 * (24 + WINDOW_PADDING_SMALL)), WINDOW_HEIGHT, nullptr, nullptr, 0x01)))
			{
				return false;
			}

			theWindowsManager.getCurrentPosition(&x, &y);

			/********************************/
			/* [Node tree] (5 – 23) Create buttons */

			theWindowsManager.setCurrentClassName("BUTTON");
			theWindowsManager.setCurrentStyleFlags(WS_CHILD | BS_DEFPUSHBUTTON | BS_MULTILINE);

			theWindowsManager.setCurrentPosition(x, y);
			nodesList_ActionIds[0][0] = 0;
			nodesList_ActionIds[0][1] = 2;

			if (0 == (nodesList_Windows[1 + 0] = theWindowsManager.addWindow("^ Back to the\nArchive Root", LARGE_BUTTON_WIDTH, NODES_BUTTON_HEIGHT, buttonFunc_NodesListMisc, (void*)NODES_LISTBOX_ROOT, 0)))
			{
				return false;
			}

			if (0 == (nodesList_Windows[1 + 1] = theWindowsManager.addWindow("^ Back to the\nParent Node", LARGE_BUTTON_WIDTH, NODES_BUTTON_HEIGHT, buttonFunc_NodesListMisc, (void*)NODES_LISTBOX_PARENT, 0x01)))
			{
				return false;
			}

			if (0 == (nodesList_Windows[1 + 2] = theWindowsManager.addWindow("Center the Camera on the Current Node", LARGE_BUTTON_WIDTH, NODES_BUTTON_HEIGHT, buttonFunc_NodesListMisc, (void*)NODES_LISTBOX_CENTER_CAMERA, 0)))
			{
				return false;
			}

			theWindowsManager.setCurrentPosition(x, y);
			nodesList_ActionIds[1][0] = 3;
			nodesList_ActionIds[1][1] = 6;

			if (0 == (nodesList_Windows[1 + 3] = theWindowsManager.addWindow("(F1)\nMove Higlighted Node UP", LARGE_BUTTON_WIDTH, NODES_BUTTON_HEIGHT, buttonFunc_NodesListMisc, (void*)NODES_LISTBOX_MOVE_UP, 0)))
			{
				return false;
			}

			if (0 == (nodesList_Windows[1 + 4] = theWindowsManager.addWindow("(F2)\nMove Higlighted Node DOWN", LARGE_BUTTON_WIDTH, NODES_BUTTON_HEIGHT, buttonFunc_NodesListMisc, (void*)NODES_LISTBOX_MOVE_DOWN, 0x01)))
			{
				return false;
			}

			if (0 == (nodesList_Windows[1 + 5] = theWindowsManager.addWindow("(F4)\nMove Highlighted\nNode OUTSIDE", LARGE_BUTTON_WIDTH, NODES_BUTTON_HEIGHT, buttonFunc_NodesListMisc, (void*)NODES_LISTBOX_MOVE_OUT, 0)))
			{
				return false;
			}

			if (0 == (nodesList_Windows[1 + 6] = theWindowsManager.addWindow("(F3)\nMove INTO the\nGroup entry ontop", LARGE_BUTTON_WIDTH, NODES_BUTTON_HEIGHT, buttonFunc_NodesListMisc, (void*)NODES_LISTBOX_MOVE_IN, 0x01)))
			{
				return false;
			}

			theWindowsManager.setCurrentPosition(x, y);
			nodesList_ActionIds[2][0] = 7;
			nodesList_ActionIds[2][1] = 9;

			if (0 == (nodesList_Windows[1 + 7] = theWindowsManager.addWindow("Delete Current Node", LARGE_BUTTON_WIDTH, NODES_BUTTON_HEIGHT, buttonFunc_NodesListMisc, (void*)NODES_LISTBOX_DELETE_CURRENT, 0x01)))
			{
				return false;
			}

			if (0 == (nodesList_Windows[1 + 8] = theWindowsManager.addWindow("Delete All Children from the Current Group", LARGE_BUTTON_WIDTH, NODES_BUTTON_HEIGHT, buttonFunc_NodesListMisc, (void*)NODES_LISTBOX_DELETE_CHILDREN, 0)))
			{
				return false;
			}

			if (0 == (nodesList_Windows[1 + 9] = theWindowsManager.addWindow("(DEL)\nDelete\nHighlighted Node", LARGE_BUTTON_WIDTH, NODES_BUTTON_HEIGHT, buttonFunc_NodesListMisc, (void*)NODES_LISTBOX_DELETE_SELECTED, 0x01)))
			{
				return false;
			}

			theWindowsManager.setCurrentPosition(x, y);
			nodesList_ActionIds[3][0] = 10;
			nodesList_ActionIds[3][1] = 12;

			if (0 == (nodesList_Windows[1 + 10] = theWindowsManager.addWindow("Clone Current Node", LARGE_BUTTON_WIDTH, NODES_BUTTON_HEIGHT, buttonFunc_NodesListMisc, (void*)NODES_EDITING_CLONE_CURRENT, 0)))
			{
				return false;
			}

			if (0 == (nodesList_Windows[1 + 11] = theWindowsManager.addWindow("(F5)\nClone\nHighlighted Node", LARGE_BUTTON_WIDTH, NODES_BUTTON_HEIGHT, buttonFunc_NodesListMisc, (void*)NODES_EDITING_CLONE_SELECTED, 0x01)))
			{
				return false;
			}

			if (0 == (nodesList_Windows[1 + 12] = theWindowsManager.addWindow("(F6)\nPaste Cloned\nNode here", LARGE_BUTTON_WIDTH, NODES_BUTTON_HEIGHT, buttonFunc_NodesListMisc, (void*)NODES_EDITING_CLONE_PASTING, 0x01)))
			{
				return false;
			}

			theWindowsManager.setCurrentPosition(x, y);
			nodesList_ActionIds[4][0] = 13;
			nodesList_ActionIds[4][1] = 16;

			if (0 == (nodesList_Windows[1 + 13] = theWindowsManager.addWindow("(F7)\nClone or Create\na new Material", LARGE_BUTTON_WIDTH, NODES_BUTTON_HEIGHT, buttonFunc_NodesListMisc, (void*)NODES_EDITING_MATERIAL_CLONE, 0)))
			{
				return false;
			}

			if (0 == (nodesList_Windows[1 + 14] = theWindowsManager.addWindow("Remove Material from Current Node", LARGE_BUTTON_WIDTH, NODES_BUTTON_HEIGHT, buttonFunc_NodesListMisc, (void*)NODES_EDITING_MATERIAL_DELETE, 0x01)))
			{
				return false;
			}

			if (0 == (nodesList_Windows[1 + 15] = theWindowsManager.addWindow("(F8)\nApply Material from Manager", LARGE_BUTTON_WIDTH, NODES_BUTTON_HEIGHT, buttonFunc_NodesListMisc, (void*)NODES_EDITING_MATERIAL_CHANGE, 0)))
			{
				return false;
			}

			if (0 == (nodesList_Windows[1 + 16] = theWindowsManager.addWindow("Optimize Similar Materials from Current Node", LARGE_BUTTON_WIDTH, NODES_BUTTON_HEIGHT, buttonFunc_NodesListMisc, (void*)NODES_EDITING_MATERIAL_OPTIMIZE, 0x01)))
			{
				return false;
			}

			theWindowsManager.setCurrentPosition(x, y);
			nodesList_ActionIds[5][0] = 17;
			nodesList_ActionIds[5][1] = 20;

			if (0 == (nodesList_Windows[1 + 17] = theWindowsManager.addWindow("Export 3D Meshes to Wavefront OBJ", LARGE_BUTTON_WIDTH, NODES_BUTTON_HEIGHT, buttonFunc_NodesListObj, (void*)0, 0)))
			{
				return false;
			}

			if (0 == (nodesList_Windows[1 + 18] = theWindowsManager.addWindow("Import 3D Meshes from Wavefront OBJ", LARGE_BUTTON_WIDTH, NODES_BUTTON_HEIGHT, buttonFunc_NodesListObj, (void*)1, 0x01)))
			{
				return false;
			}

			if (0 == (nodesList_Windows[1 + 19] = theWindowsManager.addWindow("(F9)\nRebuild Collision of\nHighlighted Node", LARGE_BUTTON_WIDTH, NODES_BUTTON_HEIGHT, buttonFunc_NodesListMisc, (void*)NODES_LISTBOX_COLLISION_REBUILD, 0)))
			{
				return false;
			}

			if (0 == (nodesList_Windows[1 + 20] = theWindowsManager.addWindow("(F11)\nClear Collision of\nHighlighted Node", LARGE_BUTTON_WIDTH, NODES_BUTTON_HEIGHT, buttonFunc_NodesListMisc, (void*)NODES_LISTBOX_COLLISION_CLEAR, 0x01)))
			{
				return false;
			}

			theWindowsManager.setCurrentPosition(x, y);
			nodesList_ActionIds[6][0] = 21;
			nodesList_ActionIds[6][1] = 24;

			if (0 == (nodesList_Windows[1 + 21] = theWindowsManager.addWindow("Update \"DrawPass\" flags", LARGE_BUTTON_WIDTH, NODES_BUTTON_HEIGHT, buttonFunc_NodesListMisc, (void*)NODES_EDITING_GROUPS_DPFLAGS, 0)))
			{
				return false;
			}

			if (0 == (nodesList_Windows[1 + 22] = theWindowsManager.addWindow("Remove empty and unreferenced Groups", LARGE_BUTTON_WIDTH, NODES_BUTTON_HEIGHT, buttonFunc_NodesListMisc, (void*)NODES_EDITING_GROUPS_UNREF, 0x01)))
			{
				return false;
			}

            if (0 == (nodesList_Windows[1 + 23] = theWindowsManager.addWindow("Reconstruct eTriMesh\nvertices", LARGE_BUTTON_WIDTH, NODES_BUTTON_HEIGHT, buttonFunc_NodesListMisc, (void*)NODES_EDITING_GROUPS_UPDATEMESH, 0)))
            {
                return false;
            }

            if (0 == (nodesList_Windows[1 + 24] = theWindowsManager.addWindow("Apply env map", LARGE_BUTTON_WIDTH, NODES_BUTTON_HEIGHT, buttonFunc_NodesListMisc, (void*)NODES_EDITING_GROUPS_ADD_ENVMAP, 0x01)))
            {
                return false;
            }

			theWindowsManager.setCurrentPosition(x, (y + 2 * (NODES_BUTTON_HEIGHT + WINDOW_PADDING_SMALL)));
			theWindowsManager.setCurrentPadding(0, 0);
			theWindowsManager.offsetCurrentPosition(0, WINDOW_PADDING_SMALL);

			/********************************/
			/* [Node tree] (21) Create listbox */

			theWindowsManager.setCurrentClassName("LISTBOX");
			theWindowsManager.setCurrentStyleFlags(WS_CHILD | WS_HSCROLL | WS_VSCROLL | LBS_DISABLENOSCROLL | LBS_HASSTRINGS | LBS_NOTIFY | LBS_WANTKEYBOARDINPUT | WS_VISIBLE);

			theWindowsManager.addEdgesToNextWindow();
			if (0 == (dummy_window = theWindowsManager.addWindow("", RECT_TABS_X2, 384, buttonFunc_NodesListChild, nullptr, 0x01)))
			{
				return false;
			}

			SendMessage(dummy_window, LB_SETHORIZONTALEXTENT, (WPARAM)512, 0);
			menuFunc_NodesListEnter();

            /********************************/
            /* WinApi creation completed. :) */

            theWindowsManager.switchPage(0);

            ShowWindow(main_window, SW_SHOW);

            updatingEditboxesNotByUser = false;

            return true;
        }


        ////////////////////////////////////////////////////////////////
        // Close windows and unload OpenGL
        ////////////////////////////////////////////////////////////////
        void closeWindows()
        {
            /* Disable OpenGL */

            wglMakeCurrent(NULL, NULL);

            if (NULL != openGL_DeviceContext)
            {
                wglDeleteContext(openGL_RenderingContext);

                ReleaseDC(theWindowsManager.getMainWindow(), openGL_DeviceContext);
            }

            /* Close/Unload others */

            if (NULL != myWindowLogo)
            {
                FreeResource(myWindowLogo);
            }

            if (NULL != myWindowFont)
            {
                DeleteObject(myWindowFont);
            }
        }


        ////////////////////////////////////////////////////////////////
        // Window loop: Is main window still open?
        ////////////////////////////////////////////////////////////////
        bool isAppRunning()
        {
            bool stillActive = true;
            MSG message = {0};

            while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
            {
                if (WM_QUIT == message.message)
                {
                    stillActive = false;
                }

                TranslateMessage(&message);
                DispatchMessage(&message);
            }

            return stillActive;
        }

    }
}
