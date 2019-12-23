#include <kao2engine/eProxy.h>
#include <kao2ar/Archive.h>

#include <kao2engine/eXRefProxy.h>
#include <kao2engine/eXRefTarget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eProxy interface
    // <kao2.004844A0> (constructor)
    // <kao2.00484590> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_PROXY_TYPEINFO
    (
        E_PROXY_ID,
        "eProxy",
        &E_TRANSFORM_TYPEINFO,
        []() -> eObject*
        {
            return new eProxy;
        }
    );

    TypeInfo* eProxy::getType()
    {
        return &E_PROXY_TYPEINFO;
    }

    eProxy::eProxy()
    : eTransform()
    {
        category = 0;
    }

    eProxy::~eProxy() {}


    ////////////////////////////////////////////////////////////////
    // eProxy serialization
    // <kao2.004846C0>
    ////////////////////////////////////////////////////////////////
    void eProxy::serialize(Archive &ar)
    {
        int32_t ar_flags;
        eXRefTarget* test_xref_taget;
        eXRefProxy* test_xref_proxy;

        if (ar.checkGameEngine(GAME_VERSION_KAO_TW_PC, GAME_VERSION_KAO_TW_PC) && ar.isInDebugMode() && ar.isInWriteMode())
        {
            /* Serialize "eNode" and "eTransform" (zero elements in "eGroup!") */

            eNode::serialize(ar);

            ar_flags = 0;
            ar.readOrWrite(&ar_flags, 0x04);
            
            form01.serialize(ar);
            form02.serialize(ar);

            ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&ctrl, &E_CTRL_ESRP_TYPEINFO);
        }
        else
        {
            eTransform::serialize(ar);
        }

        ar.serializeString(targetFile);

        ar.readOrWrite(&category, 0x04);

        /********************************/
        /* Loading external models... */
        /* CURRENTLY NEEDED ONLY WITH "kao_tw" ENGINE */

        if (ar.checkGameEngine(GAME_VERSION_KAO_TW_PC, GAME_VERSION_KAO_TW_PC) && ar.isInDebugMode() && ar.isInReadMode())
        {
            if (nodes.getSize() <= 0)
            {
                if (canBeLoadedOrExported(ar_flags))
                {
                    test_xref_taget = new eXRefTarget;

                    test_xref_taget->loadTarget(ar, ar_flags, targetFile);

                    test_xref_proxy = new eXRefProxy(test_xref_taget);

                    nodes.appendChild(test_xref_proxy);
                }
            }
        }

        /********************************/
        /* Saving external models... */

        if (ar.isInExportProxiesMode())
        {
            if (canBeLoadedOrExported(ar_flags))
            {
                test_xref_proxy = (eXRefProxy*)nodes.getIthChild(0);

                if (nullptr != test_xref_proxy)
                {
                    /* Child node could be "eTriMesh" */

                    if (test_xref_proxy->getType()->checkHierarchy(&E_XREFPROXY_TYPEINFO))
                    {
                        test_xref_taget = test_xref_proxy->getXRefTarget();

                        if (nullptr != test_xref_taget)
                        {
                            test_xref_taget->exportTarget(ar, ar_flags);
                        }
                    }
                }
            }
        }
    }

    
    ////////////////////////////////////////////////////////////////
    // eProxy: set archive flags and file extension
    ////////////////////////////////////////////////////////////////
    bool eProxy::canBeLoadedOrExported(int32_t &ar_flags)
    {
        if (false == targetFile.hasExtension("ar"))
        {
            return false;
        }

        switch (category)
        {
            case 0: // (particle)
            {
                ar_flags = (AR_MODE_XREF_PATH);

                return true;
            }

            case 3: // (enemy)
            case 4: // (fluff)
            case 5: // (geoproxy)
            case 6: // (object)
            {
                ar_flags = 0;

                return true;
            }
        }

        return false;
    }


    ////////////////////////////////////////////////////////////////
    // eProxy: set target name
    ////////////////////////////////////////////////////////////////
    void eProxy::setTargetName(eString new_target)
    {
        targetFile = new_target;
    }


    ////////////////////////////////////////////////////////////////
    // eProxy: set category
    ////////////////////////////////////////////////////////////////
    void eProxy::setCategory(int32_t new_category)
    {
        category = new_category;
    }


    ////////////////////////////////////////////////////////////////
    // eProxy: export readable structure
    ////////////////////////////////////////////////////////////////
    void eProxy::writeStructureToTextFile(FileOperator &file, int32_t indentation)
    {
        char bufor[128];

        eNode::writeStructureToTextFile(file, indentation);

        sprintf_s
        (
            bufor,
            128,
            " - proxy target: [%d] \"%s\"",
            category,
            targetFile.getText()
        );

        ArFunctions::writeIndentation(file, indentation);
        file << bufor;
        ArFunctions::writeNewLine(file, 0);
    }


    ////////////////////////////////////////////////////////////////
    // eProxy: render
    ////////////////////////////////////////////////////////////////
    void eProxy::renderObject(float time, int32_t draw_flags)
    {
        if (GUI::drawFlags::DRAW_FLAG_PROXIES & draw_flags)
        {
            eTransform::renderObject(time, draw_flags);

            /* (--dsp--) use `glCallList()` here !!! */

            const float CUBE_WIDTH = (64.0f / 2);
            const float CUBE_WIDTH_FRONT = 0.75f * CUBE_WIDTH;

            glBindTexture(GL_TEXTURE_2D, 0);

            glColor3f(0, 0, 1.0f);

            glLineWidth(2.0f);

            glBegin(GL_LINES);

            /* Cube Front */

            glVertex3f(form01.pos.x - CUBE_WIDTH, form01.pos.y - CUBE_WIDTH_FRONT, form01.pos.z - CUBE_WIDTH);
            glVertex3f(form01.pos.x + CUBE_WIDTH, form01.pos.y - CUBE_WIDTH_FRONT, form01.pos.z - CUBE_WIDTH);
            
            glVertex3f(form01.pos.x + CUBE_WIDTH, form01.pos.y - CUBE_WIDTH_FRONT, form01.pos.z - CUBE_WIDTH);
            glVertex3f(form01.pos.x + CUBE_WIDTH, form01.pos.y - CUBE_WIDTH_FRONT, form01.pos.z + CUBE_WIDTH);

            glVertex3f(form01.pos.x + CUBE_WIDTH, form01.pos.y - CUBE_WIDTH_FRONT, form01.pos.z + CUBE_WIDTH);
            glVertex3f(form01.pos.x - CUBE_WIDTH, form01.pos.y - CUBE_WIDTH_FRONT, form01.pos.z + CUBE_WIDTH);

            glVertex3f(form01.pos.x - CUBE_WIDTH, form01.pos.y - CUBE_WIDTH_FRONT, form01.pos.z + CUBE_WIDTH);
            glVertex3f(form01.pos.x - CUBE_WIDTH, form01.pos.y - CUBE_WIDTH_FRONT, form01.pos.z - CUBE_WIDTH);

            /* Cube Back */

            glVertex3f(form01.pos.x - CUBE_WIDTH, form01.pos.y + CUBE_WIDTH, form01.pos.z - CUBE_WIDTH);
            glVertex3f(form01.pos.x + CUBE_WIDTH, form01.pos.y + CUBE_WIDTH, form01.pos.z - CUBE_WIDTH);

            glVertex3f(form01.pos.x + CUBE_WIDTH, form01.pos.y + CUBE_WIDTH, form01.pos.z - CUBE_WIDTH);
            glVertex3f(form01.pos.x + CUBE_WIDTH, form01.pos.y + CUBE_WIDTH, form01.pos.z + CUBE_WIDTH);

            glVertex3f(form01.pos.x + CUBE_WIDTH, form01.pos.y + CUBE_WIDTH, form01.pos.z + CUBE_WIDTH);
            glVertex3f(form01.pos.x - CUBE_WIDTH, form01.pos.y + CUBE_WIDTH, form01.pos.z + CUBE_WIDTH);

            glVertex3f(form01.pos.x - CUBE_WIDTH, form01.pos.y + CUBE_WIDTH, form01.pos.z + CUBE_WIDTH);
            glVertex3f(form01.pos.x - CUBE_WIDTH, form01.pos.y + CUBE_WIDTH, form01.pos.z - CUBE_WIDTH);

            /* Cube Left */

            glVertex3f(form01.pos.x - CUBE_WIDTH, form01.pos.y + CUBE_WIDTH, form01.pos.z + CUBE_WIDTH);
            glVertex3f(form01.pos.x - CUBE_WIDTH, form01.pos.y - CUBE_WIDTH_FRONT, form01.pos.z + CUBE_WIDTH);

            glVertex3f(form01.pos.x - CUBE_WIDTH, form01.pos.y + CUBE_WIDTH, form01.pos.z - CUBE_WIDTH);
            glVertex3f(form01.pos.x - CUBE_WIDTH, form01.pos.y - CUBE_WIDTH_FRONT, form01.pos.z - CUBE_WIDTH);

            /* Cube Right */

            glVertex3f(form01.pos.x + CUBE_WIDTH, form01.pos.y + CUBE_WIDTH, form01.pos.z + CUBE_WIDTH);
            glVertex3f(form01.pos.x + CUBE_WIDTH, form01.pos.y - CUBE_WIDTH_FRONT, form01.pos.z + CUBE_WIDTH);

            glVertex3f(form01.pos.x + CUBE_WIDTH, form01.pos.y + CUBE_WIDTH, form01.pos.z - CUBE_WIDTH);
            glVertex3f(form01.pos.x + CUBE_WIDTH, form01.pos.y - CUBE_WIDTH_FRONT, form01.pos.z - CUBE_WIDTH);

            /* Stop drawing lines */

            glEnd();

            glColor3f(1.0f, 1.0f, 1.0f);

            glLineWidth(1.0f);
        }
    }

}
