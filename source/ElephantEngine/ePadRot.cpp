#include <ElephantEngine/ePadRot.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePadRot interface
    // <kao2.004DBDD3> (constructor)
    // <kao2.004DC1D0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_PADROT_TYPEINFO
    (
        E_PADROT_ID,
        "ePadRot",
        &E_LOOKATCTRL_TYPEINFO,
        []() -> eObject*
        {
            return new ePadRot;
        }
    );

    const TypeInfo* ePadRot::getType() const
    {
        return &E_PADROT_TYPEINFO;
    }

    ePadRot::ePadRot()
    : eLookAtCtrl()
    {}

    ePadRot::~ePadRot()
    {}


    ////////////////////////////////////////////////////////////////
    // ePadRot: cloning the object
    ////////////////////////////////////////////////////////////////

    void ePadRot::createFromOtherObject(const ePadRot &other)
    {}

    ePadRot::ePadRot(const ePadRot &other)
    : eLookAtCtrl(other)
    {
        createFromOtherObject(other);
    }

    ePadRot& ePadRot::operator = (const ePadRot &other)
    {
        if ((&other) != this)
        {
            eLookAtCtrl::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* ePadRot::cloneFromMe() const
    {
        return new ePadRot(*this);
    }

}
