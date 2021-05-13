#ifndef H_KAO2AR_FOLLOWCAMERACTRL
#define H_KAO2AR_FOLLOWCAMERACTRL

#include <ElephantEngine/eCameraTarget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFollowCameraCtrl interface
    // <kao2.005D4BA8> (vptr)
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

        private:

            void createFromOtherObject(const eFollowCameraCtrl &other);

        public:

            eFollowCameraCtrl(const eFollowCameraCtrl &other);
            eFollowCameraCtrl& operator = (const eFollowCameraCtrl &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eFollowCameraCtrl TypeInfo
    // <kao2.00514720> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_FOLLOWCAMERACTRL_ID = 0x12455672;

    extern TypeInfo E_FOLLOWCAMERACTRL_TYPEINFO;

}

#endif
