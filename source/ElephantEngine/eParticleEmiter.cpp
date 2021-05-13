#include <ElephantEngine/eParticleEmiter.h>
#include <ElephantBase/Archive.h>

#include <ElephantEngine/eSndEmiter.h>

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

        /*[0x002C]*/ sphBound.w = 128.0f;
        /*[0x001C]*/ flags &= 0xFFFFFF7F;

        /*[0x01F1]*/ unknown_01F1 = 0x00;
        /*[0x01F0]*/ unknown_01F0 = 0x00;
        /*[0x0200]*/ unknown_0200 = 16000.0f;
        /*[0x01FC]*/ unknown_01FC = 32000.0f;
        /*[0x01F8]*/ unknown_01F8 = 0;
        /*[0x01F4]*/ unknown_01F4 = 0;

        /* some manipulation and multiplication with a global variable */
        /*[0x0204]*/ unknown_0204 = 0;

        /*[0x0048]*/ unknown_0048 = (-1.0f);
        /*[0x0218]*/ unknown_0218 = 0x00;
    }

    eParticleEmiter::~eParticleEmiter()
    {
        soundEmiter->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // eParticleEmiter: cloning the object
    ////////////////////////////////////////////////////////////////

    void eParticleEmiter::createFromOtherObject(const eParticleEmiter &other)
    {
        unknown_0048 = other.unknown_0048;
        unknown_004C = other.unknown_004C;
        unknown_0050 = other.unknown_0050;
        unknown_0054 = other.unknown_0054;
        unknown_0058 = other.unknown_0058;
        unknown_005C = other.unknown_005C;
        unknown_0060 = other.unknown_0060;

        unknown_0070 = other.unknown_0070;

        unknown_01DC = other.unknown_01DC;
        unknown_01E0 = other.unknown_01E0;
        unknown_01E4 = other.unknown_01E4;
        unknown_01E8 = other.unknown_01E8;

        unknown_01F1 = other.unknown_01F1;
        unknown_01F0 = other.unknown_01F0;

        unknown_01F4 = other.unknown_01F4;
        unknown_01FC = other.unknown_01FC;
        unknown_0200 = other.unknown_0200;
        unknown_0204 = other.unknown_0204;

        unknown_0218 = other.unknown_0218;

        soundEmiterFileName = other.soundEmiterFileName;

        soundEmiter = other.soundEmiter;
        if (nullptr != soundEmiter)
        {
            soundEmiter->incRef();
        }
    }

    eParticleEmiter::eParticleEmiter(const eParticleEmiter &other)
    : eGroup(other)
    {
        createFromOtherObject(other);
    }

    eParticleEmiter& eParticleEmiter::operator = (const eParticleEmiter &other)
    {
        if ((&other) != this)
        {
            eGroup::operator = (other);

            /****************/

            soundEmiter->decRef();

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eParticleEmiter::cloneFromMe() const
    {
        return nullptr;
    }


    ////////////////////////////////////////////////////////////////
    // eParticleEmiter: serialization
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
