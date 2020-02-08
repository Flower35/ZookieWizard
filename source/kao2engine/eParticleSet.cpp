#include <kao2engine/eParticleSet.h>
#include <kao2ar/Archive.h>

#include <kao2engine/eOscilationCtrl.h>
#include <kao2engine/ePosCtrl.h>
#include <kao2engine/eRotCtrl.h>
#include <kao2engine/eColorCtrl.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eParticleSet interface
    // <kao2.00558050> (constructor)
    // <kao2.005587B0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_PARTICLESET_TYPEINFO
    (
        E_PARTICLESET_ID,
        "eParticleSet",
        &E_PARTICLEGEOMETRY_TYPEINFO,
        []() -> eObject*
        {
            return new eParticleSet;
        }
    );

    TypeInfo* eParticleSet::getType() const
    {
        return &E_PARTICLESET_TYPEINFO;
    }

    eParticleSet::eParticleSet()
    : eParticleGeometry()
    {
        /*[0x00C8]*/ groupA_Count = 0;
        /*[0x00CC]*/ groupA_MaxLength = 0;
        /*[0x00D0]*/ groupA = nullptr;

        /*[0x00D4]*/ unknown_00D4 = nullptr;
        /*[0x00D8]*/ unknown_00D8 = nullptr;
        /*[0x00DC]*/ unknown_00DC = nullptr;
        /*[0x00E0]*/ unknown_00E0 = nullptr;

        unknown_00D8 = new eRotCtrl;
        unknown_00D8->incRef();

        unknown_00D4 = new ePosCtrl;
        unknown_00D4->incRef();

        unknown_00DC = new eColorCtrl;
        unknown_00DC->incRef();

        unknown_00E0 = new eOscilationCtrl;
        unknown_00E0->incRef();

        /*[0x1C]*/ flags |= 0x40;

        /*[0x00EC]*/ unknown_00EC = 0;
        /*[0x00F0]*/ unknown_00F0 = 0;
        /*[0x0120]*/ unknown_0120 = 0;
        /*[0x011D]*/ unknown_011D = 0x00;
        /*[0x0124]*/ unknown_0124 = 0;
        /*[0x0128]*/ unknown_0128 = 0;
        /*[0x011E]*/ unknown_011E = 0x00;
        /*[0x012C]*/ unknown_012C = 0.5f;
        /*[0x0131]*/ unknown_0131 = 0x00;

        /*(...)*/

        /*[0x14]*/ name = "Particle Set";
    }

    eParticleSet::~eParticleSet()
    {
        if (nullptr != unknown_00E0)
        {
            unknown_00E0->decRef();
        }

        if (nullptr != unknown_00DC)
        {
            unknown_00DC->decRef();
        }

        if (nullptr != unknown_00D8)
        {
            unknown_00D8->decRef();
        }

        if (nullptr != unknown_00D4)
        {
            unknown_00D4->decRef();
        }
    }


    ////////////////////////////////////////////////////////////////
    // Unknown structure
    // <kao2.005594A0> (serialization)
    ////////////////////////////////////////////////////////////////

    void eParticleSetBase::serialize(Archive &ar)
    {
        ar.readOrWrite(&unknown_0C, 0x04);

        ar.readOrWrite(&unknown_1C, 0x04);

        ar.readOrWrite(&unknown_24, 0x04);
        ar.readOrWrite(&unknown_28, 0x04);
        ar.readOrWrite(&unknown_2C, 0x04);

        ar.readOrWrite(&unknown_34, 0x04);

        ar.readOrWrite(&unknown_00, 0x04);
        ar.readOrWrite(&unknown_04, 0x04);
        ar.readOrWrite(&unknown_08, 0x04);

        ar.readOrWrite(&unknown_10, 0x04);
        ar.readOrWrite(&unknown_14, 0x04);
        ar.readOrWrite(&unknown_18, 0x04);

        ar.readOrWrite(&unknown_30, 0x04);

        ar.readOrWrite(&unknown_38, 0x04);
        ar.readOrWrite(&unknown_3C, 0x04);
    }


    ////////////////////////////////////////////////////////////////
    // eParticleSet serialization
    // <kao2.00558FF0>
    ////////////////////////////////////////////////////////////////
    void eParticleSet::serialize(Archive &ar)
    {
        int32_t i;

        eGeometry::serialize(ar);

        /* [0xC8] unknown group */

        if (ar.isInReadMode())
        {
            ar.readOrWrite(&groupA_MaxLength, 0x04);

            if (nullptr != groupA)
            {
                delete[](groupA);
                groupA = nullptr;

                groupA_Count = 0;
            }

            groupA = new eParticleSetBase [groupA_MaxLength];

            for (i = 0; i < groupA_MaxLength; i++)
            {
                groupA[i].serialize(ar);

                groupA_Count = (i+1);
            }
        }
        else
        {
            ar.readOrWrite(&groupA_Count, 0x04);

            for (i = 0; i < groupA_Count; i++)
            {
                groupA[i].serialize(ar);
            }
        }

        /* [0x0124] unknown */
        
        ar.readOrWrite(&unknown_0124, 0x04);

        /* [0x0128] unknown */

        ar.readOrWrite(&unknown_0128, 0x04);

        /* [0x00E0] unknown (eOscilationCtrl) */

        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&unknown_00E0, &E_OSCILATIONCTRL_TYPEINFO);

        /* [0x011E] unknown */

        ar.readOrWrite(&unknown_011E, 0x01);

        /* [0x00D4] unknown (ePosCtrl) */

        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&unknown_00D4, &E_POSCTRL_TYPEINFO);

        /* [0x00D8] unknown (eRotCtrl) */

        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&unknown_00D8, &E_ROTCTRL_TYPEINFO);

        /* [0x00DC] unknown (eColorCtrl) */

        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&unknown_00DC, &E_COLORCTRL_TYPEINFO);

        /* unknown values */

        ar.readOrWrite(&unknown_00E4, 0x04);
        ar.readOrWrite(&unknown_BC, 0x04);
        ar.readOrWrite(&unknown_00E8, 0x04);
        ar.readOrWrite(&unknown_00EC, 0x04);
        ar.readOrWrite(&unknown_00F0, 0x04);

        /* unknown values */

        ar.readOrWrite(&unknown_00F4, 0x04);
        ar.readOrWrite(&unknown_00FC, 0x04);
        ar.readOrWrite(&unknown_00F8, 0x04);
        ar.readOrWrite(&unknown_0100, 0x04);
        ar.readOrWrite(&unknown_0104, 0x04);
        ar.readOrWrite(&unknown_0118, 0x01);
        ar.readOrWrite(&unknown_0119, 0x01);
        ar.readOrWrite(&unknown_011A, 0x01);
        ar.readOrWrite(&unknown_0108, 0x04);
        ar.readOrWrite(&unknown_010C, 0x04);
        ar.readOrWrite(&unknown_0110, 0x04);
        ar.readOrWrite(&unknown_0114, 0x04);
        ar.readOrWrite(&unknown_011B, 0x01);
        ar.readOrWrite(&unknown_011C, 0x01);
        ar.readOrWrite(&unknown_011D, 0x01);
        ar.readOrWrite(&unknown_0120, 0x04);
    }

}
