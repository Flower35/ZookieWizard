#ifndef H_KAO2AR_BUTTERFLY
#define H_KAO2AR_BUTTERFLY

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eButterfly interface
    // <kao2.005CEC58> (vptr)
    ////////////////////////////////////////////////////////////////

    class eButterfly : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x50]*/

        /*** Methods ***/

        public:

            eButterfly();
            ~eButterfly();

        private:

            void createFromOtherObject(const eButterfly &other);

        public:

            eButterfly(const eButterfly &other);
            eButterfly& operator = (const eButterfly &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eButterfly TypeInfo
    // <kao2.00436780> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_BUTTERFLY_ID = 0x3BF56DDF;

    extern TypeInfo E_BUTTERFLY_TYPEINFO;

}

#endif
