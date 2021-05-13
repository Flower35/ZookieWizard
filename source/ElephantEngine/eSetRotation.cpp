#include <ElephantEngine/eSetRotation.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSetRotation interface
    // <kao2.00523511> (constructor)
    // <kao2.00523580> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SETROTATION_TYPEINFO
    (
        E_SETROTATION_ID,
        "eSetRotation",
        &E_LOOKATCTRL_TYPEINFO,
        []() -> eObject*
        {
            return new eSetRotation;
        }
    );

    const TypeInfo* eSetRotation::getType() const
    {
        return &E_SETROTATION_TYPEINFO;
    }

    eSetRotation::eSetRotation()
    : eLookAtCtrl()
    {}

    eSetRotation::~eSetRotation()
    {}


    ////////////////////////////////////////////////////////////////
    // eSetRotation: cloning the object
    ////////////////////////////////////////////////////////////////

    void eSetRotation::createFromOtherObject(const eSetRotation &other)
    {}

    eSetRotation::eSetRotation(const eSetRotation &other)
    : eLookAtCtrl(other)
    {
        createFromOtherObject(other);
    }

    eSetRotation& eSetRotation::operator = (const eSetRotation &other)
    {
        if ((&other) != this)
        {
            eLookAtCtrl::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eSetRotation::cloneFromMe() const
    {
        return new eSetRotation(*this);
    }

}
