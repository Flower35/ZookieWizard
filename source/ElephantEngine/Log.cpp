#include <ElephantEngine/Log.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Log interface
    // <kao2.0059B4E0> (constructor)
    // <kao2.0059B5C0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_LOG_TYPEINFO
    (
        E_LOG_ID,
        "Log",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new Log;
        }
    );

    TypeInfo* Log::getType() const
    {
        return &E_LOG_TYPEINFO;
    }

    Log::Log()
    : Gadget()
    {
        name = "log";
    }

    Log::~Log()
    {}


    ////////////////////////////////////////////////////////////////
    // Log: cloning the object
    ////////////////////////////////////////////////////////////////

    void Log::createFromOtherObject(const Log &other)
    {}

    Log::Log(const Log &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    Log& Log::operator = (const Log &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* Log::cloneFromMe() const
    {
        return new Log(*this);
    }


    ////////////////////////////////////////////////////////////////
    // Log: get default name (scripting shenanigans)
    ////////////////////////////////////////////////////////////////
    eString Log::getDefaultGadgetName() const
    {
        return "log";
    }


    ////////////////////////////////////////////////////////////////
    // Log: print text
    ////////////////////////////////////////////////////////////////
    void Log::print(eString what) const
    {
        std::printf("\n");

        std::printf(what.getText());
    }


    ////////////////////////////////////////////////////////////////
    // Log: print object
    ////////////////////////////////////////////////////////////////
    void Log::print(eObject* what) const
    {
        std::printf
        (
            "\n" \
            "--------------------------------\n"
        );

        std::printf(what->getLogPrintMessage().getText());

        std::printf("\n");
    }


    ////////////////////////////////////////////////////////////////
    // Static Gadget
    ////////////////////////////////////////////////////////////////

    Log theLog;

}
