#include <kao2engine/eDirectionCtrlEx.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eDirectionCtrlEx interface
    // <kao2.00461981> (constructor)
    // <kao2.00461A00> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_DIRECTIONCTRLEX_TYPEINFO
    (
        E_DIRECTIONCTRLEX_ID,
        "eDirectionCtrlEx",
        &E_DIRECTIONCTRL_TYPEINFO,
        []() -> eObject*
        {
            return new eDirectionCtrlEx;
        }
    );

    TypeInfo* eDirectionCtrlEx::getType() const
    {
        return &E_DIRECTIONCTRLEX_TYPEINFO;
    }

    eDirectionCtrlEx::eDirectionCtrlEx()
    : eDirectionCtrl()
    {}

    eDirectionCtrlEx::~eDirectionCtrlEx()
    {}


    ////////////////////////////////////////////////////////////////
    // eDirectionCtrlEx: cloning the object
    ////////////////////////////////////////////////////////////////

    void eDirectionCtrlEx::createFromOtherObject(const eDirectionCtrlEx &other)
    {}

    eDirectionCtrlEx::eDirectionCtrlEx(const eDirectionCtrlEx &other)
    : eDirectionCtrl(other)
    {
        createFromOtherObject(other);
    }

    eDirectionCtrlEx& eDirectionCtrlEx::operator = (const eDirectionCtrlEx &other)
    {
        if ((&other) != this)
        {
            eDirectionCtrl::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eDirectionCtrlEx::cloneFromMe() const
    {
        return new eDirectionCtrlEx(*this);
    }

}
