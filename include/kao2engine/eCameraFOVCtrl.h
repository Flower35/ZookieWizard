#ifndef H_KAO2AR_CAMERAFOVCTRL
#define H_KAO2AR_CAMERAFOVCTRL

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCameraFOVCtrl interface
    // <kao2.005D2CB8> (vptr)
    ////////////////////////////////////////////////////////////////

    class eCameraFOVCtrl : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x2C]*/

        /*** Methods ***/

        public:

            eCameraFOVCtrl();
            ~eCameraFOVCtrl();

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eCameraFOVCtrl TypeInfo
    // <kao2.004D5B90> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_CAMERAFOVCTRL_ID = 0xCA3E7A0F;

    extern TypeInfo E_CAMERAFOVCTRL_TYPEINFO;

}

#endif
