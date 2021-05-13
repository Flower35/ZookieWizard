#ifndef H_KAO2AR_CREDITS
#define H_KAO2AR_CREDITS

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCredits interface
    // <kao2.005D02B8> (vptr)
    ////////////////////////////////////////////////////////////////

    class eCredits : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x50]*/

        /*** Methods ***/

        public:

            eCredits();
            ~eCredits();

        private:

            void createFromOtherObject(const eCredits &other);

        public:

            eCredits(const eCredits &other);
            eCredits& operator = (const eCredits &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eCredits TypeInfo
    // <kao2.00461310> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_CREDITS_ID = 0x3B601778;

    extern TypeInfo E_CREDITS_TYPEINFO;

}

#endif
