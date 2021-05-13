#ifndef H_KAO2AR_SPLINEHINTFOLLOWCAMERACTRL
#define H_KAO2AR_SPLINEHINTFOLLOWCAMERACTRL

#include <ElephantEngine/eFollowCameraCtrl.h>

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

        private:

            void createFromOtherObject(const eSplineHintFollowCameraCtrl &other);

        public:

            eSplineHintFollowCameraCtrl(const eSplineHintFollowCameraCtrl &other);
            eSplineHintFollowCameraCtrl& operator = (const eSplineHintFollowCameraCtrl &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eSplineHintFollowCameraCtrl TypeInfo
    // <kao2.004D7970> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SPLINEHINTFOLLOWCAMERACTRL_ID = 0x123400CD;

    extern TypeInfo E_SPLINEHINTFOLLOWCAMERACTRL_TYPEINFO;

}

#endif
