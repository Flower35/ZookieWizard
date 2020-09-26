#include <kao2engine/eSecondCameraTarget.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSecondCameraTarget interface
    // <kao2.00516ED1> (constructor)
    // <kao2.00516F50> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SECONDCAMERATARGET_TYPEINFO
    (
        E_SECONDCAMERATARGET_ID,
        "eSecondCameraTarget",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eSecondCameraTarget;
        }
    );

    TypeInfo* eSecondCameraTarget::getType() const
    {
        return &E_SECONDCAMERATARGET_TYPEINFO;
    }

    eSecondCameraTarget::eSecondCameraTarget()
    : Gadget()
    {}

    eSecondCameraTarget::~eSecondCameraTarget()
    {}


    ////////////////////////////////////////////////////////////////
    // eSecondCameraTarget: cloning the object
    ////////////////////////////////////////////////////////////////

    void eSecondCameraTarget::createFromOtherObject(const eSecondCameraTarget &other)
    {}

    eSecondCameraTarget::eSecondCameraTarget(const eSecondCameraTarget &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eSecondCameraTarget& eSecondCameraTarget::operator = (const eSecondCameraTarget &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eSecondCameraTarget::cloneFromMe() const
    {
        return new eSecondCameraTarget(*this);
    }

}
