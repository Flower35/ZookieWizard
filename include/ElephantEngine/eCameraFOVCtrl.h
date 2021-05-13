#ifndef H_KAO2AR_CAMERAFOVCTRL
#define H_KAO2AR_CAMERAFOVCTRL

#include <ElephantEngine/Gadget.h>

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

        private:

            void createFromOtherObject(const eCameraFOVCtrl &other);

        public:

            eCameraFOVCtrl(const eCameraFOVCtrl &other);
            eCameraFOVCtrl& operator = (const eCameraFOVCtrl &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eCameraFOVCtrl TypeInfo
    // <kao2.004D5B60> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_CAMERAFOVCTRL_ID = 0xCA3E7A0F;

    extern TypeInfo E_CAMERAFOVCTRL_TYPEINFO;

}

#endif
