#include <ElephantEngine/eDoubleCameraTarget.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eDoubleCameraTarget interface
    // <kao2.00516754> (constructor)
    // <kao2.00516BB0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_DOUBLECAMERATARGET_TYPEINFO
    (
        E_DOUBLECAMERATARGET_ID,
        "eDoubleCameraTarget",
        &E_CAMERATARGET_TYPEINFO,
        []() -> eObject*
        {
            return new eDoubleCameraTarget;
        }
    );

    const TypeInfo* eDoubleCameraTarget::getType() const
    {
        return &E_DOUBLECAMERATARGET_TYPEINFO;
    }

    eDoubleCameraTarget::eDoubleCameraTarget()
    : eCameraTarget()
    {}

    eDoubleCameraTarget::~eDoubleCameraTarget()
    {}


    ////////////////////////////////////////////////////////////////
    // eDoubleCameraTarget: cloning the object
    ////////////////////////////////////////////////////////////////

    void eDoubleCameraTarget::createFromOtherObject(const eDoubleCameraTarget &other)
    {}

    eDoubleCameraTarget::eDoubleCameraTarget(const eDoubleCameraTarget &other)
    : eCameraTarget(other)
    {
        createFromOtherObject(other);
    }

    eDoubleCameraTarget& eDoubleCameraTarget::operator = (const eDoubleCameraTarget &other)
    {
        if ((&other) != this)
        {
            eCameraTarget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eDoubleCameraTarget::cloneFromMe() const
    {
        return new eDoubleCameraTarget(*this);
    }

}
