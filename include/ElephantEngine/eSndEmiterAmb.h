#ifndef H_KAO2AR_SNDEMITERAMB
#define H_KAO2AR_SNDEMITERAMB

#include <ElephantEngine/eSndEmiter.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSndEmiterAmb interface
    // <kao2.005CEF28> (vptr)
    ////////////////////////////////////////////////////////////////

    class eSndEmiterAmb : public eSndEmiter
    {
        /*** Properties ***/

        protected:

            /*[0x08]*/ int32_t unknown_08;

        /*** Methods ***/

        public:

            eSndEmiterAmb();
            ~eSndEmiterAmb();

        private:

            void createFromOtherObject(const eSndEmiterAmb &other);

        public:

            eSndEmiterAmb(const eSndEmiterAmb &other);
            eSndEmiterAmb& operator = (const eSndEmiterAmb &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eSndEmiterAmb TypeInfo
    // <kao2.0056C490> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SNDEMITERAMB_ID = 0x09994523;

    extern TypeInfo E_SNDEMITERAMB_TYPEINFO;

}

#endif
