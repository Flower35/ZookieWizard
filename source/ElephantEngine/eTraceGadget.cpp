#include <ElephantEngine/eTraceGadget.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eTraceGadget interface
    // <kao2.0050D8C0> (constructor)
    // <kao2.0050D9C0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_TRACEGADGET_TYPEINFO
    (
        E_TRACEGADGET_ID,
        "eTraceGadget",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eTraceGadget;
        }
    );

    const TypeInfo* eTraceGadget::getType() const
    {
        return &E_TRACEGADGET_TYPEINFO;
    }

    eTraceGadget::eTraceGadget()
    : Gadget()
    {}

    eTraceGadget::~eTraceGadget()
    {}


    ////////////////////////////////////////////////////////////////
    // eTraceGadget: cloning the object
    ////////////////////////////////////////////////////////////////

    void eTraceGadget::createFromOtherObject(const eTraceGadget &other)
    {}

    eTraceGadget::eTraceGadget(const eTraceGadget &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eTraceGadget& eTraceGadget::operator = (const eTraceGadget &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eTraceGadget::cloneFromMe() const
    {
        return new eTraceGadget(*this);
    }

}
