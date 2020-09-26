#include <kao2engine/eHitForceCtrl.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eHitForceCtrl interface
    // <kao2.0044F0E0> (constructor)
    // <kao2.0044F170> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_HITFORCECTRL_TYPEINFO
    (
        E_HITFORCECTRL_ID,
        "eHitForceCtrl",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eHitForceCtrl;
        }
    );

    TypeInfo* eHitForceCtrl::getType() const
    {
        return &E_HITFORCECTRL_TYPEINFO;
    }

    eHitForceCtrl::eHitForceCtrl()
    : Gadget()
    {}

    eHitForceCtrl::~eHitForceCtrl()
    {}


    ////////////////////////////////////////////////////////////////
    // eHitForceCtrl: cloning the object
    ////////////////////////////////////////////////////////////////

    void eHitForceCtrl::createFromOtherObject(const eHitForceCtrl &other)
    {}

    eHitForceCtrl::eHitForceCtrl(const eHitForceCtrl &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eHitForceCtrl& eHitForceCtrl::operator = (const eHitForceCtrl &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eHitForceCtrl::cloneFromMe() const
    {
        return new eHitForceCtrl(*this);
    }

}
