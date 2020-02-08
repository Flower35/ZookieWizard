#ifndef H_KAO2AR_MOTORBOATCAMERACTRL
#define H_KAO2AR_MOTORBOATCAMERACTRL

#include <kao2engine/eFollowCameraCtrl.h>

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

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eMotorboatCameraCtrl TypeInfo
    // <kao2.004D6810> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_MOTORBOATCAMERACTRL_ID = 0x123400CC;

    extern TypeInfo E_MOTORBOATCAMERACTRL_TYPEINFO;

}

#endif
