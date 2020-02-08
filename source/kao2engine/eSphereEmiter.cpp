#include <kao2engine/eSphereEmiter.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSphereEmiter interface
    // <kao2.00553120> (constructor)
    // <kao2.00553260> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SPHEREEMITER_TYPEINFO
    (
        E_SPHEREEMITER_ID,
        "eSphereEmiter",
        &E_PARTICLEEMITER_TYPEINFO,
        []() -> eObject*
        {
            return new eSphereEmiter;
        }
    );

    TypeInfo* eSphereEmiter::getType() const
    {
        return &E_SPHEREEMITER_TYPEINFO;
    }

    eSphereEmiter::eSphereEmiter()
    : eParticleEmiter()
    {
        /*[0x021C]*/ unknown_021C = 256.0f;
        /*[0x0220]*/ unknown_0220 = 0x01;
    }

    eSphereEmiter::~eSphereEmiter() {}


    ////////////////////////////////////////////////////////////////
    // eSphereEmiter serialization
    // <kao2.00553480>
    ////////////////////////////////////////////////////////////////
    void eSphereEmiter::serialize(Archive &ar)
    {
        eParticleEmiter::serialize(ar);

        /* [0x021C] unknown */
        ar.readOrWrite(&unknown_021C, 0x04);

        /* [0x0220] unknown */
        ar.readOrWrite(&unknown_0220, 0x01);
    }

}
