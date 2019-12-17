#ifndef H_KAO2AR_LOG
#define H_KAO2AR_LOG

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Log interface
    ////////////////////////////////////////////////////////////////

    class Log : public Gadget
    {
        /*** Methods ***/

        public:

            Log();
            ~Log();

            TypeInfo* getType() override;

            eString getDefaultGadgetName() override;

            void print(eString what);
            void print(eObject* what);
    };


    ////////////////////////////////////////////////////////////////
    // Log TypeInfo
    // <kao2.0059B970> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_LOG_ID = 0x00020005;

    extern TypeInfo E_LOG_TYPEINFO;


    ////////////////////////////////////////////////////////////////
    // Static Gadget
    ////////////////////////////////////////////////////////////////

    extern Log theLog;
}

#endif
