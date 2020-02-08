#include <kao2engine/eReadySteadyGo.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eReadySteadyGo interface
    // <kao2.0045B390> (constructor)
    // <kao2.0045B4A0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_READYSTEADYGO_TYPEINFO
    (
        E_READYSTEADYGO_ID,
        "eReadySteadyGo",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eReadySteadyGo;
        }
    );

    TypeInfo* eReadySteadyGo::getType() const
    {
        return &E_READYSTEADYGO_TYPEINFO;
    }

    eReadySteadyGo::eReadySteadyGo()
    : Gadget()
    {}

    eReadySteadyGo::~eReadySteadyGo() {}

}
