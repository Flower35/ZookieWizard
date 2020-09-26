#include <kao2engine/eCameraTarget.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCameraTarget interface
    // <kao2.00510AA4> (constructor)
    // <kao2.00510B60> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_CAMERATARGET_TYPEINFO
    (
        E_CAMERATARGET_ID,
        "eCameraTarget",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eCameraTarget;
        }
    );

    TypeInfo* eCameraTarget::getType() const
    {
        return &E_CAMERATARGET_TYPEINFO;
    }

    eCameraTarget::eCameraTarget()
    : Gadget()
    {}

    eCameraTarget::~eCameraTarget()
    {}


    ////////////////////////////////////////////////////////////////
    // eCameraTarget: cloning the object
    ////////////////////////////////////////////////////////////////

    void eCameraTarget::createFromOtherObject(const eCameraTarget &other)
    {}

    eCameraTarget::eCameraTarget(const eCameraTarget &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eCameraTarget& eCameraTarget::operator = (const eCameraTarget &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eCameraTarget::cloneFromMe() const
    {
        return new eCameraTarget(*this);
    }

}
