#ifndef H_KAO2AR_SNOWCAMERACTRL
#define H_KAO2AR_SNOWCAMERACTRL

#include <kao2engine/eFollowCameraCtrl.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSnowCameraCtrl interface
    // <kao2.005D4D00> (vptr)
    ////////////////////////////////////////////////////////////////

    class eSnowCameraCtrl : public eFollowCameraCtrl
    {

        /*** Properties ***/

        protected:

            /*[0x0438]*/
            /*(...)*/
            /*[0x0454]*/

        /*** Methods ***/

        public:

            eSnowCameraCtrl();
            ~eSnowCameraCtrl();

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eSnowCameraCtrl TypeInfo
    // <kao2.005162D0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SNOWCAMERACTRL_ID = 0xCA3E7A33;

    extern TypeInfo E_SNOWCAMERACTRL_TYPEINFO;

}

#endif
