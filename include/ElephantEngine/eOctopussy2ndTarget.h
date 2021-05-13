#ifndef H_KAO2AR_OCTOPUSSY2NDTARGET
#define H_KAO2AR_OCTOPUSSY2NDTARGET

#include <ElephantEngine/eSecondCameraTarget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eOctopussy2ndTarget interface
    // <kao2.005D4F48> (vptr)
    ////////////////////////////////////////////////////////////////

    class eOctopussy2ndTarget : public eSecondCameraTarget
    {
        /*** Properties ***/

        protected:

            /*[0x48]*/
            /*[0x4C]*/

        /*** Methods ***/

        public:

            eOctopussy2ndTarget();
            ~eOctopussy2ndTarget();

        private:

            void createFromOtherObject(const eOctopussy2ndTarget &other);

        public:

            eOctopussy2ndTarget(const eOctopussy2ndTarget &other);
            eOctopussy2ndTarget& operator = (const eOctopussy2ndTarget &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eOctopussy2ndTarget TypeInfo
    // <kao2.00516FA0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_OCTOPUSSY2NDTARGET_ID = 0xCA3E7A21;

    extern TypeInfo E_OCTOPUSSY2NDTARGET_TYPEINFO;

}

#endif
