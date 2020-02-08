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

            TypeInfo* getType() const override;

            eString getDefaultGadgetName() const override;

            void print(eString what) const;
            void print(eObject* what) const;
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
