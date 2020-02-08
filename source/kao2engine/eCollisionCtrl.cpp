#include <kao2engine/eCollisionCtrl.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCollisionCtrl interface
    // <kao2.00432D00> (constructor)
    // <kao2.00432D90> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_COLLISIONCTRL_TYPEINFO
    (
        E_COLLISIONCTRL_ID,
        "eCollisionCtrl",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eCollisionCtrl;
        }
    );

    TypeInfo* eCollisionCtrl::getType() const
    {
        return &E_COLLISIONCTRL_TYPEINFO;
    }

    eCollisionCtrl::eCollisionCtrl()
    : Gadget()
    {}

    eCollisionCtrl::~eCollisionCtrl() {}

}
