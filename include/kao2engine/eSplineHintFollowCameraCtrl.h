#ifndef H_KAO2AR_SPLINEHINTFOLLOWCAMERACTRL
#define H_KAO2AR_SPLINEHINTFOLLOWCAMERACTRL

#include <kao2engine/eFollowCameraCtrl.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSplineHintFollowCameraCtrl interface
    // <kao2.005D2E18> (vptr)
    ////////////////////////////////////////////////////////////////

    class eSplineHintFollowCameraCtrl : public eFollowCameraCtrl
    {

        /*** Properties ***/

        protected:

            /*[0x0438]*/

        /*** Methods ***/

        public:

            eSplineHintFollowCameraCtrl();
            ~eSplineHintFollowCameraCtrl();

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eSplineHintFollowCameraCtrl TypeInfo
    // <kao2.004D79A0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SPLINEHINTFOLLOWCAMERACTRL_ID = 0x123400CD;

    extern TypeInfo E_SPLINEHINTFOLLOWCAMERACTRL_TYPEINFO;

}

#endif
