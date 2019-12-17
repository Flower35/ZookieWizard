#include <kao2engine/ePointEmiter.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePointEmiter interface
    // <kao2.005522D0> (constructor)
    // <kao2.005523A0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_POINTEMITER_TYPEINFO
    (
        E_POINTEMITER_ID,
        "ePointEmiter",
        &E_PARTICLEEMITER_TYPEINFO,
        []() -> eObject*
        {
            return new ePointEmiter;
        }
    );

    TypeInfo* ePointEmiter::getType()
    {
        return &E_POINTEMITER_TYPEINFO;
    }

    ePointEmiter::ePointEmiter()
    : eParticleEmiter()
    {
        /*[0x0054]*/ unknown_0054 = 360.0f;
        /*[0x0050]*/ unknown_0050 = 5.0f;
    }

    ePointEmiter::~ePointEmiter() {}

}
