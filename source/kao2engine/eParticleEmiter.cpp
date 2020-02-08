#include <kao2engine/eParticleEmiter.h>
#include <kao2ar/Archive.h>

#include <kao2engine/eSndEmiter.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eParticleEmiter interface
    // <kao2.00550B90> (constructor)
    // <kao2.00551250> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_PARTICLEEMITER_TYPEINFO
    (
        E_PARTICLEEMITER_ID,
        "eParticleEmiter",
        &E_GROUP_TYPEINFO,
        []() -> eObject*
        {
            return nullptr;
        }
    );

    TypeInfo* eParticleEmiter::getType() const
    {
        return &E_PARTICLEEMITER_TYPEINFO;
    }

    eParticleEmiter::eParticleEmiter()
    : eGroup()
    {
        /*[0x0214]*/ soundEmiter = nullptr;

        /*[0x0020]*/ sphBound[0] = 0;
        /*[0x0024]*/ sphBound[1] = 0;
        /*[0x0028]*/ sphBound[2] = 0;
        /*[0x002C]*/ sphBound[3] = 128.0f;
        /*[0x001C]*/ flags &= 0xFFFFFF7F;

        /*[0x01F1]*/ unknown_01F1 = 0x00;
        /*[0x01F0]*/ unknown_01F0 = 0x00;
        /*[0x0200]*/ unknown_0200 = 16000.0f;
        /*[0x01FC]*/ unknown_01FC = 32000.0f;
        /*[0x01F8]*/ unknown_01F8 = 0;
        /*[0x01F4]*/ unknown_01F4 = 0;

        /* somee manipulation and multiplication with a global variable */
        /*[0x0204]*/ unknown_0204 = 0;

        /*[0x0048]*/ unknown_0048 = (-1.0f);
        /*[0x0218]*/ unknown_0218 = 0x00;
    }

    eParticleEmiter::~eParticleEmiter()
    {
        if (nullptr != soundEmiter)
        {
            soundEmiter->decRef();
        }
    }


    ////////////////////////////////////////////////////////////////
    // eParticleEmiter serialization
    // <kao2.00551F30>
    ////////////////////////////////////////////////////////////////
    void eParticleEmiter::serialize(Archive &ar)
    {
        eGroup::serialize(ar);

        /* unknown values */

        ar.readOrWrite(&unknown_0048, 0x04);
        ar.readOrWrite(&unknown_004C, 0x04);
        ar.readOrWrite(&unknown_0050, 0x04);
        ar.readOrWrite(&unknown_0054, 0x04);
        ar.readOrWrite(&unknown_0058, 0x04);
        ar.readOrWrite(&unknown_005C, 0x04);
        ar.readOrWrite(&unknown_0060, 0x04);

        /* [0x0070] eGlobalCtrl::serialize() */

        unknown_0070.serialize(ar);

        /* unknown values */

        ar.readOrWrite(&unknown_01DC, 0x04);
        ar.readOrWrite(&unknown_01E0, 0x04);
        ar.readOrWrite(&unknown_01E4, 0x04);
        ar.readOrWrite(&unknown_01E8, 0x04);

        /* unknown values */

        ar.readOrWrite(&unknown_01F1, 0x01);
        ar.readOrWrite(&unknown_01F0, 0x01);

        /* unknown values */

        ar.readOrWrite(&unknown_01F4, 0x04);
        ar.readOrWrite(&unknown_01FC, 0x04);
        ar.readOrWrite(&unknown_0200, 0x04);
        ar.readOrWrite(&unknown_0204, 0x04);

        if (ar.getVersion() >= 0x69)
        {
            /* [0x0218] unknown */

            ar.readOrWrite(&unknown_0218, 0x01);

            /* [0x0210] Sound emiter file name */

            ar.serializeString(soundEmiterFileName);

            /* [0x0214] Sound emiter */

            ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&soundEmiter, &E_SNDEMITER_TYPEINFO);
        }
        else
        {
            if (ar.isInReadMode())
            {
                /* [0x0218] unknown */
                
                unknown_0218 = 0x00;

                /* [0x0210] Sound emiter file name */

                soundEmiterFileName = eString(0);

                /* [0x214] Sound emiter */

                if (nullptr != soundEmiter)
                {
                    soundEmiter->decRef();

                    soundEmiter = nullptr;
                }
            }
        }
    }

}
