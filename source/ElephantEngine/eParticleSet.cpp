#include <ElephantEngine/eParticleSet.h>
#include <ElephantBase/Archive.h>

#include <ElephantEngine/eOscilationCtrl.h>
#include <ElephantEngine/ePosCtrl.h>
#include <ElephantEngine/eRotCtrl.h>
#include <ElephantEngine/eColorCtrl.h>

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

    const TypeInfo* eParticleSet::getType() const
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

        /*[0x013C]*/ unknown_013C = 0.5f;
        /*[0x0140]*/ unknown_0140 = 0x00;

        /*(...)*/

        /*[0x14]*/ name = "Particle Set";
    }

    eParticleSet::~eParticleSet()
    {
        unknown_00E0->decRef();
        unknown_00DC->decRef();
        unknown_00D8->decRef();
        unknown_00D4->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // eParticleSet: cloning the object
    ////////////////////////////////////////////////////////////////

    void eParticleSet::createFromOtherObject(const eParticleSet &other)
    {
        groupA_MaxLength = other.groupA_Count;

        if (groupA_MaxLength > 0)
        {
            groupA = new eParticleSetBase [groupA_MaxLength];

            for (groupA_Count = 0; groupA_Count < groupA_MaxLength; groupA_Count++)
            {
                groupA[groupA_Count] = other.groupA[groupA_Count];
            }
        }
        else
        {
            groupA_Count = 0;
            groupA = nullptr;
        }

        /****************/

        unknown_00D4 = other.unknown_00D4;
        if (nullptr != unknown_00D4)
        {
            unknown_00D4->incRef();
        }

        unknown_00D8 = other.unknown_00D8;
        if (nullptr != unknown_00D8)
        {
            unknown_00D8->incRef();
        }

        unknown_00DC = other.unknown_00DC;
        if (nullptr != unknown_00DC)
        {
            unknown_00DC->incRef();
        }

        unknown_00E0 = other.unknown_00E0;
        if (nullptr != unknown_00E0)
        {
            unknown_00E0->incRef();
        }

        /****************/

        unknown_0124 = other.unknown_0124;
        unknown_0128 = other.unknown_0128;

        unknown_011E = other.unknown_011E;

        unknown_00E4 = other.unknown_00E4;
        unknown_BC   = other.unknown_BC;
        unknown_00E8 = other.unknown_00E8;
        unknown_00EC = other.unknown_00EC;
        unknown_00F0 = other.unknown_00F0;

        unknown_00F4 = other.unknown_00F4;
        unknown_00FC = other.unknown_00FC;
        unknown_00F8 = other.unknown_00F8;
        unknown_0100 = other.unknown_0100;
        unknown_0104 = other.unknown_0104;
        unknown_0118 = other.unknown_0118;
        unknown_0119 = other.unknown_0119;
        unknown_011A = other.unknown_011A;
        unknown_0108 = other.unknown_0108;
        unknown_010C = other.unknown_010C;
        unknown_0110 = other.unknown_0110;
        unknown_0114 = other.unknown_0114;
        unknown_011B = other.unknown_011B;
        unknown_011C = other.unknown_011C;
        unknown_011D = other.unknown_011D;
        unknown_0120 = other.unknown_0120;

        unknown_0134 = other.unknown_0134;
        unknown_013C = other.unknown_013C;
        unknown_0140 = other.unknown_0140;
    }

    eParticleSet::eParticleSet(const eParticleSet &other)
    : eParticleGeometry(other)
    {
        createFromOtherObject(other);
    }

    eParticleSet& eParticleSet::operator = (const eParticleSet &other)
    {
        if ((&other) != this)
        {
            eParticleGeometry::operator = (other);

            /****************/

            unknown_00E0->decRef();
            unknown_00DC->decRef();
            unknown_00D8->decRef();
            unknown_00D4->decRef();

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eParticleSet::cloneFromMe() const
    {
        return new eParticleSet(*this);
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
    // eParticleSet: serialization
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
        ar.readOrWrite(&unknown_00E8, 0x04);  // "particle set count"
        ar.readOrWrite(&unknown_00EC, 0x04);
        ar.readOrWrite(&unknown_00F0, 0x04);

        /* unknown values */

        ar.readOrWrite(&unknown_00F4, 0x04);

        if (ar.getVersion() >= 0x97)
        {
            ar.serializeString(unknown_0134);
            ar.readOrWrite(&unknown_013C, 0x04);
        }

        if (ar.getVersion() >= 0xA2)
        {
            ar.readOrWrite(&unknown_0140, 0x01);
        }

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
