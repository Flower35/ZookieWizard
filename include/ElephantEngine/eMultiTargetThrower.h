#ifndef H_KAO2AR_MULTITARGETTHROWER
#define H_KAO2AR_MULTITARGETTHROWER

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eMultiTargetThrower interface
    // <kao2.005D4608> (vptr)
    ////////////////////////////////////////////////////////////////

    class eMultiTargetThrower : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x7C]*/

        /*** Methods ***/

        public:

            eMultiTargetThrower();
            ~eMultiTargetThrower();

        private:

            void createFromOtherObject(const eMultiTargetThrower &other);

        public:

            eMultiTargetThrower(const eMultiTargetThrower &other);
            eMultiTargetThrower& operator = (const eMultiTargetThrower &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eMultiTargetThrower TypeInfo
    // <kao2.005046C0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_MULTITARGETTHROWER_ID = 0x3BF54DDF;

    extern TypeInfo E_MULTITARGETTHROWER_TYPEINFO;

}

#endif
