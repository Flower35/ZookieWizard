#ifndef H_KAO2AR_GAMECAMERA
#define H_KAO2AR_GAMECAMERA

#include <kao2engine/eCamera.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eGameCamera interface
    // <kao2.005D2EC8> (vptr)
    ////////////////////////////////////////////////////////////////

    class eGameCamera : public eCamera
    {

        /*** Properties ***/

        protected:

            /*[0x01E8]*/
            /*(...)*/
            /*[0x0408]*/

        /*** Methods ***/

        public:

            eGameCamera(eString x);
            ~eGameCamera();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eGameCamera TypeInfo
    // <kao2.004D9810> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_GAMECAMERA_ID = 0x0CA4E7A2;

    extern TypeInfo E_GAMECAMERA_TYPEINFO;

}

#endif
