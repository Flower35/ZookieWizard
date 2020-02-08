#ifndef H_KAO2AR_FOLLOWCAMERACTRL
#define H_KAO2AR_FOLLOWCAMERACTRL

#include <kao2engine/eCameraTarget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFollowCameraCtrl interface
    ////////////////////////////////////////////////////////////////

    class eFollowCameraCtrl : public eCameraTarget
    {

        /*** Properties ***/

        protected:

            /*[0x01F8]*/
            /*(...)*/
            /*[0x0434]*/

        /*** Methods ***/

        public:

            eFollowCameraCtrl();
            ~eFollowCameraCtrl();

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eFollowCameraCtrl TypeInfo
    // <kao2.00514750> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_FOLLOWCAMERACTRL_ID = 0x12455672;

    extern TypeInfo E_FOLLOWCAMERACTRL_TYPEINFO;

}

#endif
