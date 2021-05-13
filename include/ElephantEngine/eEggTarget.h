#ifndef H_KAO2AR_EGGTARGET
#define H_KAO2AR_EGGTARGET

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eEggTarget interface
    // <kao2.005D4388> (vptr)
    ////////////////////////////////////////////////////////////////

    class eEggTarget : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x34]*/

        /*** Methods ***/

        public:

            eEggTarget();
            ~eEggTarget();

        private:

            void createFromOtherObject(const eEggTarget &other);

        public:

            eEggTarget(const eEggTarget &other);
            eEggTarget& operator = (const eEggTarget &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eEggTarget TypeInfo
    // <kao2.00502680> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_EGGTARGET_ID = 0x3BF45DCD;

    extern TypeInfo E_EGGTARGET_TYPEINFO;

}

#endif
