#ifndef H_KAO2AR_WATERTARGET
#define H_KAO2AR_WATERTARGET

#include <kao2engine/eEggTarget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eWaterTarget interface
    // <kao2.005D46F8> (vptr)
    ////////////////////////////////////////////////////////////////

    class eWaterTarget : public eEggTarget
    {
        /*** Methods ***/

        public:

            eWaterTarget();
            ~eWaterTarget();

        private:

            void createFromOtherObject(const eWaterTarget &other);

        public:

            eWaterTarget(const eWaterTarget &other);
            eWaterTarget& operator = (const eWaterTarget &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eWaterTarget TypeInfo
    // <kao2.00507890> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_WATERTARGET_ID = 0x3BFA6DCD;

    extern TypeInfo E_WATERTARGET_TYPEINFO;

}

#endif
