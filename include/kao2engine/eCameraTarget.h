#ifndef H_KAO2AR_CAMERATARGET
#define H_KAO2AR_CAMERATARGET

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCameraTarget interface
    ////////////////////////////////////////////////////////////////

    class eCameraTarget : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x0010]*/
            /*(...)*/
            /*[0x01F4]*/

        /*** Methods ***/

        public:

            eCameraTarget();
            ~eCameraTarget();

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eCameraTarget TypeInfo
    // <kao2.00510A70> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_CAMERATARGET_ID = 0xCA3E7A10;

    extern TypeInfo E_CAMERATARGET_TYPEINFO;

}

#endif
