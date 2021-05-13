#include <ElephantEngine/eTimerGadget.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eTimerGadget interface
    // <kao2.0051E990> (constructor)
    // <kao2.0051EA60> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_TIMERGADGET_TYPEINFO
    (
        E_TIMERGADGET_ID,
        "eTimerGadget",
        &E_TEXTWRITERFIELDS2_TYPEINFO,
        []() -> eObject*
        {
            return new eTimerGadget;
        }
    );

    TypeInfo* eTimerGadget::getType() const
    {
        return &E_TIMERGADGET_TYPEINFO;
    }

    eTimerGadget::eTimerGadget()
    : eTextWriterFields2()
    {}

    eTimerGadget::~eTimerGadget()
    {}


    ////////////////////////////////////////////////////////////////
    // eTimerGadget: cloning the object
    ////////////////////////////////////////////////////////////////

    void eTimerGadget::createFromOtherObject(const eTimerGadget &other)
    {}

    eTimerGadget::eTimerGadget(const eTimerGadget &other)
    : eTextWriterFields2(other)
    {
        createFromOtherObject(other);
    }

    eTimerGadget& eTimerGadget::operator = (const eTimerGadget &other)
    {
        if ((&other) != this)
        {
            eTextWriterFields2::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eTimerGadget::cloneFromMe() const
    {
        return new eTimerGadget(*this);
    }

}
