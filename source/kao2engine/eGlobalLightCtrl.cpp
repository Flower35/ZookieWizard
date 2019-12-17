#include <kao2engine/eGlobalLightCtrl.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eGlobalLightCtrl interface
    // <kao_tw.0052FAB1> (constructor)
    // <kao_tw.0052FB20> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_GLOBALLIGHTCTRL_TYPEINFO
    (
        E_GLOBALLIGHTCTRL_ID,
        "eGlobalLightCtrl",
        &E_GROUP_TYPEINFO,
        []() -> eObject*
        {
            return new eGlobalLightCtrl;
        }
    );

    TypeInfo* eGlobalLightCtrl::getType()
    {
        /* (--dsp--) Simple hack for versions older than "kao_tw" */
        /* But this replaces object ID even when saving "kao_tw" archives... */

        return &E_GROUP_TYPEINFO;
    }

    eGlobalLightCtrl::eGlobalLightCtrl()
    : eGroup()
    {}

    eGlobalLightCtrl::~eGlobalLightCtrl() {}


    ////////////////////////////////////////////////////////////////
    // eGlobalLightCtrl serialization
    ////////////////////////////////////////////////////////////////
    void eGlobalLightCtrl::serialize(Archive &ar)
    {
        /* See above: TypeInfo hack ("eGroup" ID is being written) */

        if (false)
        {
            if (ar.getVersion() < 0x90)
            {
                throw ErrorMessage
                (
                    "eGlobalLightCtrl::serialize():\n" \
                    "ar.version() 144 required!"
                );
            }
        }

        eGroup::serialize(ar);
    }

}
