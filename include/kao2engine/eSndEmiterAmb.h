#ifndef H_KAO2AR_SNDEMITERAMB
#define H_KAO2AR_SNDEMITERAMB

#include <kao2engine/eSndEmiter.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSndEmiterAmb interface
    ////////////////////////////////////////////////////////////////

    class eSndEmiterAmb : public eSndEmiter
    {

        /*** Properties ***/

        protected:

            /*[0x08]*/ int32_t unknown08;

        /*** Methods ***/

        public:

            eSndEmiterAmb();
            ~eSndEmiterAmb();

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eSndEmiterAmb TypeInfo
    // <kao2.0056C4C0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SNDEMITERAMB_ID = 0x09994523;

    extern TypeInfo E_SNDEMITERAMB_TYPEINFO;

}

#endif
