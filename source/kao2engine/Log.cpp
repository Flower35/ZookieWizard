#include <kao2engine/Log.h>
#include <kao2ar/Archive.h>

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

    TypeInfo* Log::getType()
    {
        return &E_LOG_TYPEINFO;
    }

    Log::Log()
    : Gadget()
    {
        name = "log";
    }

    Log::~Log() {}


    ////////////////////////////////////////////////////////////////
    // Static Gadget
    ////////////////////////////////////////////////////////////////

    Log theLog;


    ////////////////////////////////////////////////////////////////
    // Log: get default name (scripting shenanigans)
    ////////////////////////////////////////////////////////////////
    eString Log::getDefaultGadgetName()
    {
        return "log";
    }


    ////////////////////////////////////////////////////////////////
    // Log: print text
    ////////////////////////////////////////////////////////////////
    void Log::print(eString what)
    {
        std::printf("\n");

        std::printf(what.getText());
    }


    ////////////////////////////////////////////////////////////////
    // Log: print object
    ////////////////////////////////////////////////////////////////
    void Log::print(eObject* what)
    {
        std::printf
        (
            "\n" \
            "--------------------------------\n"
        );

        std::printf(what->getLogPrintMessage().getText());

        std::printf("\n");
    }

}
