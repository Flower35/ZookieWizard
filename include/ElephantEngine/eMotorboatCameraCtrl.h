#ifndef H_KAO2AR_MOTORBOATCAMERACTRL
#define H_KAO2AR_MOTORBOATCAMERACTRL

#include <ElephantEngine/eFollowCameraCtrl.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eMotorboatCameraCtrl interface
    // <kao2.005D2D30> (vptr)
    ////////////////////////////////////////////////////////////////

    class eMotorboatCameraCtrl : public eFollowCameraCtrl
    {
        /*** Properties ***/

        protected:

            /*[0x0438]*/
            /*(...)*/
            /*[0x04DC]*/

        /*** Methods ***/

        public:

            eMotorboatCameraCtrl();
            ~eMotorboatCameraCtrl();

        private:

            void createFromOtherObject(const eMotorboatCameraCtrl &other);

        public:

            eMotorboatCameraCtrl(const eMotorboatCameraCtrl &other);
            eMotorboatCameraCtrl& operator = (const eMotorboatCameraCtrl &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;
    };


    ////////////////////////////////////////////////////////////////
    // eMotorboatCameraCtrl TypeInfo
    // <kao2.004D67E0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_MOTORBOATCAMERACTRL_ID = 0x123400CC;

    extern TypeInfo E_MOTORBOATCAMERACTRL_TYPEINFO;

}

#endif
