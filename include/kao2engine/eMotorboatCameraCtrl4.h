#ifndef H_KAO2AR_MOTORBOATCAMERACTRL4
#define H_KAO2AR_MOTORBOATCAMERACTRL4

#include <kao2engine/eFollowCameraCtrl.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eMotorboatCameraCtrl4 interface
    // <kao_tw.006A223C> (vptr)
    ////////////////////////////////////////////////////////////////

    class eMotorboatCameraCtrl4 : public eFollowCameraCtrl
    {

        /*** Properties ***/

        protected:

            /*[0x0010]*/
            /*(...)*/
            /*[0x1078]*/

        /*** Methods ***/

        public:

            eMotorboatCameraCtrl4();
            ~eMotorboatCameraCtrl4();

            void serialize(Archive &ar) override;
            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eMotorboatCameraCtrl4 TypeInfo
    // <kao_tw.005ABC30> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_MOTORBOATCAMERACTRL4_ID = 0x123400CF;

    extern TypeInfo E_MOTORBOATCAMERACTRL4_TYPEINFO;

}

#endif
