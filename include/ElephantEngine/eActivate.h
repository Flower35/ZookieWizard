#ifndef H_KAO2AR_ACTIVATE
#define H_KAO2AR_ACTIVATE

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eActivate interface
    // <kao2.005D8780> (vptr)
    ////////////////////////////////////////////////////////////////

    class eActivate : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/

        /*** Methods ***/

        public:

            eActivate();
            ~eActivate();

        private:

            void createFromOtherObject(const eActivate &other);

        public:

            eActivate(const eActivate &other);
            eActivate& operator = (const eActivate &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eActivate TypeInfo
    // <kao2.005A3450> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_ACTIVATE_ID = 0x358E5A86;

    extern TypeInfo E_ACTIVATE_TYPEINFO;

}

#endif
