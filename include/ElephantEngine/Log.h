#ifndef H_KAO2AR_LOG
#define H_KAO2AR_LOG

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Log interface
    // <kao2.005D8418> (vptr)
    ////////////////////////////////////////////////////////////////

    class Log : public Gadget
    {
        /*** Methods ***/

        public:

            Log();
            ~Log();

        private:

            void createFromOtherObject(const Log &other);

        public:

            Log(const Log &other);
            Log& operator = (const Log &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;

            /* << Gadget >> */

            eString getDefaultGadgetName() const override;

            /* << Log >> */

            void print(eString what) const;
            void print(eObject* what) const;
    };


    ////////////////////////////////////////////////////////////////
    // Log TypeInfo
    // <kao2.0059B940> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_LOG_ID = 0x00020005;

    extern TypeInfo E_LOG_TYPEINFO;


    ////////////////////////////////////////////////////////////////
    // Static Gadget
    ////////////////////////////////////////////////////////////////

    extern Log theLog;
}

#endif
