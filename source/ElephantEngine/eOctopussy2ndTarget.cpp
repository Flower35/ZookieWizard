#include <ElephantEngine/eOctopussy2ndTarget.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eOctopussy2ndTarget interface
    // <kao2.00517001> (constructor)
    // <kao2.005171F0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_OCTOPUSSY2NDTARGET_TYPEINFO
    (
        E_OCTOPUSSY2NDTARGET_ID,
        "eOctopussy2ndTarget",
        &E_SECONDCAMERATARGET_TYPEINFO,
        []() -> eObject*
        {
            return new eOctopussy2ndTarget;
        }
    );

    const TypeInfo* eOctopussy2ndTarget::getType() const
    {
        return &E_OCTOPUSSY2NDTARGET_TYPEINFO;
    }

    eOctopussy2ndTarget::eOctopussy2ndTarget()
    : eSecondCameraTarget()
    {}

    eOctopussy2ndTarget::~eOctopussy2ndTarget()
    {}


    ////////////////////////////////////////////////////////////////
    // eOctopussy2ndTarget: cloning the object
    ////////////////////////////////////////////////////////////////

    void eOctopussy2ndTarget::createFromOtherObject(const eOctopussy2ndTarget &other)
    {}

    eOctopussy2ndTarget::eOctopussy2ndTarget(const eOctopussy2ndTarget &other)
    : eSecondCameraTarget(other)
    {
        createFromOtherObject(other);
    }

    eOctopussy2ndTarget& eOctopussy2ndTarget::operator = (const eOctopussy2ndTarget &other)
    {
        if ((&other) != this)
        {
            eSecondCameraTarget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eOctopussy2ndTarget::cloneFromMe() const
    {
        return new eOctopussy2ndTarget(*this);
    }

}
