#include <ElephantEngine/eReadySteadyGo.h>
#include <ElephantBase/Archive.h>

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

    eReadySteadyGo::~eReadySteadyGo()
    {}


    ////////////////////////////////////////////////////////////////
    // eReadySteadyGo: cloning the object
    ////////////////////////////////////////////////////////////////

    void eReadySteadyGo::createFromOtherObject(const eReadySteadyGo &other)
    {}

    eReadySteadyGo::eReadySteadyGo(const eReadySteadyGo &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eReadySteadyGo& eReadySteadyGo::operator = (const eReadySteadyGo &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eReadySteadyGo::cloneFromMe() const
    {
        return new eReadySteadyGo(*this);
    }

}
