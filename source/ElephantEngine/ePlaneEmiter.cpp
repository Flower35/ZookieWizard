#include <ElephantEngine/ePlaneEmiter.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePlaneEmiter interface
    // <kao2.00552C50> (constructor)
    // <kao2.00552D90> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_PLANEEMITER_TYPEINFO
    (
        E_PLANEEMITER_ID,
        "ePlaneEmiter",
        &E_PARTICLEEMITER_TYPEINFO,
        []() -> eObject*
        {
            return new ePlaneEmiter;
        }
    );

    const TypeInfo* ePlaneEmiter::getType() const
    {
        return &E_PLANEEMITER_TYPEINFO;
    }

    ePlaneEmiter::ePlaneEmiter()
    : eParticleEmiter()
    {
        /*[0x0054]*/ unknown_0054 = 0;
        /*[0x0050]*/ unknown_0050 = 0;

        /*[0x021C]*/ unknown_021C = 256.0f;
        /*[0x0220]*/ unknown_0220 = 256.0f;
    }

    ePlaneEmiter::~ePlaneEmiter()
    {}


    ////////////////////////////////////////////////////////////////
    // ePlaneEmiter: cloning the object
    ////////////////////////////////////////////////////////////////

    void ePlaneEmiter::createFromOtherObject(const ePlaneEmiter &other)
    {
        unknown_021C = other.unknown_021C;
        unknown_0220 = other.unknown_0220;
    }

    ePlaneEmiter::ePlaneEmiter(const ePlaneEmiter &other)
    : eParticleEmiter(other)
    {
        createFromOtherObject(other);
    }

    ePlaneEmiter& ePlaneEmiter::operator = (const ePlaneEmiter &other)
    {
        if ((&other) != this)
        {
            eParticleEmiter::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* ePlaneEmiter::cloneFromMe() const
    {
        return new ePlaneEmiter(*this);
    }


    ////////////////////////////////////////////////////////////////
    // ePlaneEmiter: serialization
    // <kao2.005530E0>
    ////////////////////////////////////////////////////////////////
    void ePlaneEmiter::serialize(Archive &ar)
    {
        eParticleEmiter::serialize(ar);

        /* [0x021C] unknown */
        ar.readOrWrite(&unknown_021C, 0x04);

        /* [0x0220] unknown */
        ar.readOrWrite(&unknown_0220, 0x04);
    }

}
