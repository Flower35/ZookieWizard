#include <ElephantEngine/eXRefManager.h>
#include <ElephantBase/Archive.h>
#include <ElephantBase/eDrawContext.h>

#include <ElephantEngine/eXRefTarget.h>
#include <ElephantEngine/eScene.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eXRefManager interface
    // <kao2.004AD7D0> (constructor)
    // <kao2.004AD900> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_XREFMANAGER_TYPEINFO
    (
        E_XREFMANAGER_ID,
        "eXRefManager",
        &E_NODE_TYPEINFO,
        []() -> eObject*
        {
            return new eXRefManager;
        }
    );

    TypeInfo* eXRefManager::getType() const
    {
        return &E_XREFMANAGER_TYPEINFO;
    }

    eXRefManager::eXRefManager()
    : eNode()
    {
        /*[0x1C]*/ flags |= 0x70000000;
        /*[0x14]*/ name = "$XRefManager";
    }

    eXRefManager::~eXRefManager()
    {}


    ////////////////////////////////////////////////////////////////
    // eXRefManager: cloning the object
    ////////////////////////////////////////////////////////////////

    void eXRefManager::createFromOtherObject(const eXRefManager &other)
    {
        throw ErrorMessage
        (
            "CRITICAL ERROR while cloning the \"eXRefManager\" object:\n" \
            "cloning << XRef managers >> without context is not supported!!!"
        );
    }

    eXRefManager::eXRefManager(const eXRefManager &other)
    : eNode(other)
    {
        createFromOtherObject(other);
    }

    eXRefManager& eXRefManager::operator = (const eXRefManager &other)
    {
        if ((&other) != this)
        {
            eNode::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eXRefManager::cloneFromMe() const
    {
        return new eXRefManager(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eXRefManager: serialization
    // <kao2.004AE730>
    ////////////////////////////////////////////////////////////////
    void eXRefManager::serialize(Archive &ar)
    {
        eNode::serialize(ar);

        xrefs.serialize(ar, &E_XREFTARGET_TYPEINFO);
    }


    ////////////////////////////////////////////////////////////////
    // eXRefManager: destroy before dereferencing
    ////////////////////////////////////////////////////////////////
    void eXRefManager::destroyNode()
    {
        int32_t i;
        eXRefTarget* test_xref_taget;
        eNode* nested_scene;

        for (i = 0; i < xrefs.getSize(); i++)
        {
            test_xref_taget = (eXRefTarget*)xrefs.getIthChild(i);

            if (nullptr != test_xref_taget)
            {
                nested_scene = test_xref_taget->getLocalScene();

                if (nullptr != nested_scene)
                {
                    nested_scene->destroyNode();
                }
            }
        }

        eNode::destroyNode();
    }


    ////////////////////////////////////////////////////////////////
    // eXRefManager: render each child eXRefTarget
    ////////////////////////////////////////////////////////////////
    void eXRefManager::renderNode(eDrawContext &draw_context) const
    {
        eXRefTarget* test_xref_taget;

        if (GUI::drawFlags::DRAW_FLAG_PROXIES & draw_context.getDrawFlags())
        {
            for (int32_t i = 0; i < xrefs.getSize(); i++)
            {
                if (nullptr != (test_xref_taget = (eXRefTarget*)xrefs.getIthChild(i)))
                {
                    test_xref_taget->renderXRefScene(draw_context);
                }
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eXRefManager: exporting Proxies
    ////////////////////////////////////////////////////////////////
    void eXRefManager::exportXRef(const eString &media_dir, int32_t engine_version) const
    {
        eXRefTarget* test_xref_taget;

        for (int32_t a = 0; a < xrefs.getSize(); a++)
        {
            if (nullptr != (test_xref_taget = (eXRefTarget*)xrefs.getIthChild(a)))
            {
                /* These targets already start with "build/win32" names */

                test_xref_taget->exportTarget
                (
                    media_dir,
                    engine_version,
                    AR_MODE_XREF_PATH
                );
            }
        }
    }

}
