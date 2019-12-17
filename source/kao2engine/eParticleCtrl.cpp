#include <kao2engine/eParticleCtrl.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eParticleCtrl interface
    // <kao2.004306A0> (constructor)
    // <kao2.00430740> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_PARTICLECTRL_TYPEINFO
    (
        E_PARTICLECTRL_ID,
        "eParticleCtrl",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eParticleCtrl;
        }
    );

    TypeInfo* eParticleCtrl::getType()
    {
        return &E_PARTICLECTRL_TYPEINFO;
    }

    eParticleCtrl::eParticleCtrl()
    : Gadget()
    {}

    eParticleCtrl::~eParticleCtrl() {}


    ////////////////////////////////////////////////////////////////
    // eParticleCtrl serialization
    // <kao2.00430C40>
    ////////////////////////////////////////////////////////////////
    void eParticleCtrl::serialize(Archive &ar)
    {
        /* (NOTE: GADGET FUNCTION IS NOT CALLED) */

        if (ar.isInReadMode())
        {
            ar.replaceStringDuringSerialization(name, getDefaultGadgetName());
        }
    }


    ////////////////////////////////////////////////////////////////
    // eParticleCtrl: get default name (scripting shenanigans)
    ////////////////////////////////////////////////////////////////
    eString eParticleCtrl::getDefaultGadgetName()
    {
        return "prt";
    }

}
