#ifndef H_KAO2AR_CAMERA
#define H_KAO2AR_CAMERA

#include <kao2engine/eObserver.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCamera interface
    ////////////////////////////////////////////////////////////////

    class eCamera : public eObserver
    {

        /*** Properties ***/

        protected:

            /*[0x01CC]*/ uint8_t unknown_01CC;
            /*[0x01D0]*/ eTransform* target;
            /*[0x01D8-0x01E4]*/ float unknown_01D8[4];

        /*** Methods ***/

        public:

            eCamera();
            ~eCamera();

            void serialize(Archive &ar) override;
            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eCamera TypeInfo
    // <kao2.0050EC50> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_CAMERA_ID = 0x0CA4E7A1;

    extern TypeInfo E_CAMERA_TYPEINFO;

}

#endif
