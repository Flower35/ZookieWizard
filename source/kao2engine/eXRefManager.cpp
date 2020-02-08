#include <kao2engine/eXRefManager.h>
#include <kao2ar/Archive.h>

#include <kao2engine/eXRefTarget.h>

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

    eXRefManager::~eXRefManager() {}


    ////////////////////////////////////////////////////////////////
    // eXRefManager serialization
    // <kao2.004AE730>
    ////////////////////////////////////////////////////////////////
    void eXRefManager::serialize(Archive &ar)
    {
        int32_t i;
        eXRefTarget* test_xref_taget;

        eNode::serialize(ar);

        xrefs.serialize(ar, &E_XREFTARGET_TYPEINFO);

        /********************************/
        /* Saving external models... */

        if (ar.isInExportProxiesMode())
        {
            for (i = 0; i < xrefs.getSize(); i++)
            {
                test_xref_taget = (eXRefTarget*)xrefs.getIthChild(i);

                if (nullptr != test_xref_taget)
                {
                    /* These targets already start with "build/win32" names */

                    test_xref_taget->exportTarget
                    (
                        ar,
                        (AR_MODE_ABSOLUTE_PATH | AR_MODE_XREF_PATH)
                    );
                }
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eXRefManager: render each child eXRefTarget
    ////////////////////////////////////////////////////////////////
    void eXRefManager::renderObject(eAnimate* anim, int32_t draw_flags, eSRP &parent_srp)
    {
        int32_t i;
        eXRefTarget* test_xref_taget;

        if (GUI::drawFlags::DRAW_FLAG_PROXIES & draw_flags)
        {
            for (i = 0; i < xrefs.getSize(); i++)
            {
                test_xref_taget = (eXRefTarget*)xrefs.getIthChild(i);

                if (nullptr != test_xref_taget)
                {
                    test_xref_taget->renderObject(anim, draw_flags, parent_srp);
                }
            }
        }
    }

}
