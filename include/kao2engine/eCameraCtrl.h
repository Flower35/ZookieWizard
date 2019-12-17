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

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eCameraCtrl TypeInfo
    // <kao2.004823D0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_CAMERACTRL_ID = 0x00202122;

    extern TypeInfo E_CAMERACTRL_TYPEINFO;

}

#endif
