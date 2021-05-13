#include <ZookieWizard/ZookieWizard.h>
#include <ZookieWizard/WindowsManager.h>

#include <ElephantEngine/eALBox.h>
#include <ElephantEngine/eGroup.h>
#include <ElephantEngine/eXRefTarget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Nodes Manager: Variables and Definitions (Proxies)
    ////////////////////////////////////////////////////////////////

    #define ZOOKIEWIZARD_NODESMGR_MAXPROXIES 128

    class nodesManager_ProxyEntry
    {
        public:

            eString path;
            eXRefTarget* target;

            nodesManager_ProxyEntry()
            {
                target = nullptr;
            }

            ~nodesManager_ProxyEntry()
            {
                target->decRef();
            }
    };

    nodesManager_ProxyEntry* nodesMgr_Proxies;

    int32_t nodesMgr_ProxiesCount;


    ////////////////////////////////////////////////////////////////
    // Nodes Manager: Variables and Definitions (ALBox rebuilding)
    ////////////////////////////////////////////////////////////////

    #define ZOOKIEWIZARD_NODESMGR_MAXALBOXES 256

    eNode** nodesMgr_ALBoxesRefs;

    int32_t nodesMgr_ALBoxesCount;


    ////////////////////////////////////////////////////////////////
    // Nodes Manager: Variables and Definitions (Cloning)
    ////////////////////////////////////////////////////////////////

    eNode* nodesMgr_ClonedNode;


    ////////////////////////////////////////////////////////////////
    // Nodes Manager: Constructor
    ////////////////////////////////////////////////////////////////
    bool prepareNodesManager()
    {
        nodesMgr_ProxiesCount = 0;
        nodesMgr_Proxies = new nodesManager_ProxyEntry [ZOOKIEWIZARD_NODESMGR_MAXPROXIES];

        nodesMgr_ALBoxesCount = 0;
        nodesMgr_ALBoxesRefs = new eNode* [ZOOKIEWIZARD_NODESMGR_MAXALBOXES];

        nodesMgr_ClonedNode = nullptr;

        return true;
    }


    ////////////////////////////////////////////////////////////////
    // Nodes Manager: Destructor
    ////////////////////////////////////////////////////////////////
    void clearNodesManager()
    {
        nodesManager_ClearProxies();

        if (nullptr != nodesMgr_Proxies)
        {
            delete[](nodesMgr_Proxies);
            nodesMgr_Proxies = nullptr;
        }

        /****************/

        nodesManager_ClearALBoxesRefs();

        if (nullptr != nodesMgr_ALBoxesRefs)
        {
            delete[](nodesMgr_ALBoxesRefs);
            nodesMgr_ALBoxesRefs = nullptr;
        }

        /****************/

        if (nullptr != nodesMgr_ClonedNode)
        {
            nodesMgr_ClonedNode->decRef();
            nodesMgr_ClonedNode = nullptr;
        }
    }


    ////////////////////////////////////////////////////////////////
    // Nodes Manager: Getting already loaded PROXY (if exists)
    ////////////////////////////////////////////////////////////////
    void* nodesManager_GetProxyTarget(void* full_path)
    {
        eString dummy_str = *(eString*)full_path;

        for (int32_t a = 0; a < nodesMgr_ProxiesCount; a++)
        {
            if (nodesMgr_Proxies[a].path.comparePath(dummy_str))
            {
                return nodesMgr_Proxies[a].target;
            }
        }

        return nullptr;
    }


    ////////////////////////////////////////////////////////////////
    // Nodes Manager: Saving new PROXY that was just loaded
    ////////////////////////////////////////////////////////////////
    bool nodesManager_InsertProxyTarget(void* full_path, void* new_target)
    {
        if ((nullptr == full_path) || (nullptr == new_target))
        {
            return false;
        }

        for (int32_t a = 0; a < nodesMgr_ProxiesCount; a++)
        {
            if (new_target == nodesMgr_Proxies[a].target)
            {
                return true;
            }
        }

        if ((nodesMgr_ProxiesCount + 1) >= ZOOKIEWIZARD_NODESMGR_MAXPROXIES)
        {
            throw ErrorMessage
            (
                "[Zookie Wizard, Nodes Manager]:\n" \
                "Too many proxies loaded! (maximum is %d)",
                ZOOKIEWIZARD_NODESMGR_MAXPROXIES
            );

            return false;
        }

        nodesMgr_Proxies[nodesMgr_ProxiesCount].path = *(eString*)full_path;
        nodesMgr_Proxies[nodesMgr_ProxiesCount].target = (eXRefTarget*)new_target;

        nodesMgr_Proxies[nodesMgr_ProxiesCount].target->incRef();

        nodesMgr_ProxiesCount++;
        return true;
    }


    ////////////////////////////////////////////////////////////////
    // Nodes Manager: Clear only active proxies
    ////////////////////////////////////////////////////////////////
    void nodesManager_ClearProxies()
    {
        for (int32_t a = 0; a < nodesMgr_ProxiesCount; a++)
        {
            nodesMgr_Proxies[a].target->decRef();
            nodesMgr_Proxies[a].target = nullptr;

            nodesMgr_Proxies[a].path = eString(-1);
        }

        nodesMgr_ProxiesCount = 0;
    }


    ////////////////////////////////////////////////////////////////
    // Nodes Manager: Save a node reference, to rebuild its ALBox later
    ////////////////////////////////////////////////////////////////
    bool nodesManager_InsertNodeWithMissingAxisListBox(void* node)
    {
        if (nullptr == node)
        {
            return false;
        }

        for (int32_t a = 0; a < nodesMgr_ProxiesCount; a++)
        {
            if (node == nodesMgr_ALBoxesRefs[a])
            {
                return true;
            }
        }

        if ((nodesMgr_ALBoxesCount + 1) >= ZOOKIEWIZARD_NODESMGR_MAXALBOXES)
        {
            throw ErrorMessage
            (
                "[Zookie Wizard, Nodes Manager]:\n" \
                "Too many ALBox references! (maximum is %d)",
                ZOOKIEWIZARD_NODESMGR_MAXALBOXES
            );

            return false;
        }

        nodesMgr_ALBoxesRefs[nodesMgr_ALBoxesCount] = (eNode*)node;
        nodesMgr_ALBoxesRefs[nodesMgr_ALBoxesCount]->incRef();

        nodesMgr_ALBoxesCount++;
        return true;
    }


    ////////////////////////////////////////////////////////////////
    // Nodes Manager: Rebuild missing ALBoxes for a chosen set of nodes
    ////////////////////////////////////////////////////////////////
    int32_t nodesManager_RebuildAxisListBoxes()
    {
        int32_t a, result = 0;
        char bufor[LARGE_BUFFER_SIZE];

        for (a = 0; a < nodesMgr_ALBoxesCount; a++)
        {
            if (nullptr != nodesMgr_ALBoxesRefs[a])
            {
                if (nodesMgr_ALBoxesRefs[a]->createCollisionEntry())
                {
                    result++;
                }

                nodesMgr_ALBoxesRefs[a]->decRef();
                nodesMgr_ALBoxesRefs[a] = nullptr;
            }
        }

        /****************/

        sprintf_s
        (
            bufor, LARGE_BUFFER_SIZE,
                "[Zookie Wizard, Nodes Manager]\n" \
                "Rebuilded %d/%d \"Axis List Boxes\" for cloned nodes.",
            result, nodesMgr_ALBoxesCount
        );

        GUI::theWindowsManager.displayMessage(WINDOWS_MANAGER_MESSAGE_INFO, bufor);

        /****************/

        nodesMgr_ALBoxesCount = 0;

        return result;
    }


    ////////////////////////////////////////////////////////////////
    // Nodes Manager: Clear only active ALBox references
    ////////////////////////////////////////////////////////////////
    void nodesManager_ClearALBoxesRefs()
    {
        for (int32_t a = 0; a < nodesMgr_ALBoxesCount; a++)
        {
            if (nullptr != nodesMgr_ALBoxesRefs[a])
            {
                nodesMgr_ALBoxesRefs[a]->decRef();
                nodesMgr_ALBoxesRefs[a] = nullptr;
            }
        }

        nodesMgr_ALBoxesCount = 0;
    }


    ////////////////////////////////////////////////////////////////
    // Nodes Manager: Clone the child of selected group
    ////////////////////////////////////////////////////////////////
    bool nodesManager_CloneChild(void* parent_node, int32_t child_id)
    {
        eGroup* test_group = (eGroup*)parent_node;
        eNode* test_node;

        if (child_id < 0)
        {
            if (nullptr == (test_node = test_group))
            {
                return false;
            }
        }
        else
        {
            if ((nullptr == test_group) || (!test_group->getType()->checkHierarchy(&E_GROUP_TYPEINFO)))
            {
                return false;
            }

            if (nullptr == (test_node = test_group->getIthChild(child_id)))
            {
                return false;
            }
        }

        if (nullptr != nodesMgr_ClonedNode)
        {
            nodesMgr_ClonedNode->decRef();
        }

        nodesMgr_ClonedNode = test_node;
        nodesMgr_ClonedNode->incRef();

        return true;
    }


    ////////////////////////////////////////////////////////////////
    // Nodes Manager: Paste the last clonded node into selected group
    ////////////////////////////////////////////////////////////////
    bool nodesManager_PasteLastClone(void* parent_node)
    {
        eGroup* test_group = (eGroup*)parent_node;
        eNode* new_node;

        if (nullptr == nodesMgr_ClonedNode)
        {
            GUI::theWindowsManager.displayMessage
            (
                WINDOWS_MANAGER_MESSAGE_WARNING,
                    "[Zookie Wizard, Nodes Manager]\n" \
                    "Node cloning failed: No node was cloned yet!"
            );

            return false;
        }
        else if ((nullptr == test_group) || (!test_group->getType()->checkHierarchy(&E_GROUP_TYPEINFO)))
        {
            GUI::theWindowsManager.displayMessage
            (
                WINDOWS_MANAGER_MESSAGE_WARNING,
                    "[Zookie Wizard, Nodes Manager]\n" \
                    "Node cloning failed: Destination is not an \"eGroup\" or similar object!"
            );

            return false;
        }

        try
        {
            new_node = (eNode*)nodesMgr_ClonedNode->cloneFromMe();

            test_group->appendChild(new_node);

            new_node->assertNodeLinksSameArchive();

            new_node->reloadXRef(getEditorString(1, false), currentArchiveVersion);
        }
        catch (ErrorMessage &err)
        {
            err.display();
        }

        if (nodesMgr_ALBoxesCount > 0)
        {
            nodesManager_RebuildAxisListBoxes();
        }

        return true;
    }


    ////////////////////////////////////////////////////////////////
    // Nodes Manager: Child removing template
    // (returns the active node, if deleted child was any of the active node's parents)
    ////////////////////////////////////////////////////////////////
    void* nodesManager_RemoveChild(void* parent_node, int32_t child_id, void* active_node)
    {
        eGroup* test_group[2];
        eNode* test_node;

        if ((nullptr != (test_group[0] = (eGroup*)parent_node)) && test_group[0]->getType()->checkHierarchy(&E_GROUP_TYPEINFO))
        {
            if ((child_id >= 0) && (child_id < test_group[0]->getNodesCount()))
            {
                test_node = test_group[0]->getIthChild(child_id);

                if (nullptr != test_node)
                {
                    test_group[1] = (eGroup*)active_node;

                    while (nullptr != test_group[1])
                    {
                        if (test_group[1] == test_node)
                        {
                            active_node = test_group[1]->getParentNode();
                            test_group[1] = nullptr;
                        }
                        else
                        {
                            test_group[1] = test_group[1]->getParentNode();
                        }
                    }

                    /****************/

                    if (test_node->getReferenceCount() >= 2)
                    {
                        if (nullptr != (test_group[1] = test_group[0]->getRootNode()))
                        {
                            test_group[1]->findAndDereference(test_node);
                        }
                    }
                }

                test_group[0]->deleteIthChild(child_id);
            }
        }

        return active_node;
    }

}
