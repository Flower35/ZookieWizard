#ifndef H_KAO2AR_CAMERACTRL
#define H_KAO2AR_CAMERACTRL

#include <kao2engine/eRefCounter.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCameraCtrl interface
    ////////////////////////////////////////////////////////////////

    class eCameraCtrl : public eRefCounter
    {
        /*** Methods ***/

        public:

            eCameraCtrl();
            ~eCameraCtrl();

        private:

            void createFromOtherObject(const eCameraCtrl &other);

        public:

            eCameraCtrl(const eCameraCtrl &other);
            eCameraCtrl& operator = (const eCameraCtrl &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eCameraCtrl TypeInfo
    // <kao2.004823A0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_CAMERACTRL_ID = 0x00202122;

    extern TypeInfo E_CAMERACTRL_TYPEINFO;

}

#endif
