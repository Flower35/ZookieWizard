#include <ElephantEngine/eNeckCtrl.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eNeckCtrl interface
    // <kao2.00437200> (constructor)
    // <kao2.004372A0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_NECKCTRL_TYPEINFO
    (
        E_NECKCTRL_ID,
        "eNeckCtrl",
        &E_LOOKATCTRL_TYPEINFO,
        []() -> eObject*
        {
            return new eNeckCtrl;
        }
    );

    const TypeInfo* eNeckCtrl::getType() const
    {
        return &E_NECKCTRL_TYPEINFO;
    }

    eNeckCtrl::eNeckCtrl()
    : eLookAtCtrl()
    {}

    eNeckCtrl::~eNeckCtrl()
    {}


    ////////////////////////////////////////////////////////////////
    // eNeckCtrl: cloning the object
    ////////////////////////////////////////////////////////////////

    void eNeckCtrl::createFromOtherObject(const eNeckCtrl &other)
    {}

    eNeckCtrl::eNeckCtrl(const eNeckCtrl &other)
    : eLookAtCtrl(other)
    {
        createFromOtherObject(other);
    }

    eNeckCtrl& eNeckCtrl::operator = (const eNeckCtrl &other)
    {
        if ((&other) != this)
        {
            eLookAtCtrl::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eNeckCtrl::cloneFromMe() const
    {
        return new eNeckCtrl(*this);
    }

}
