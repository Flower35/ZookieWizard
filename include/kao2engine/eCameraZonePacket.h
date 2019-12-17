#ifndef H_KAO2AR_CAMERAZONEPACKET
#define H_KAO2AR_CAMERAZONEPACKET

#include <kao2engine/eRefCounter.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCameraZonePacket interface
    // <kao2.005D4CBC> (vptr)
    ////////////////////////////////////////////////////////////////

    class eCameraZonePacket : public eRefCounter
    {

        /*** Properties ***/

        protected:

            /*[0x08]*/ int32_t unknown_08;
            /*[0x0C]*/ float unknown_0C;
            /*[0x10]*/ float unknown_10;
            /*[0x14]*/ float unknown_14;
            /*[0x18]*/ float unknown_18;
            /*[0x1C]*/ float unknown_1C;

        /*** Methods ***/

        public:

            eCameraZonePacket();
            ~eCameraZonePacket();

            void serialize(Archive &ar) override;
            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eCameraZonePacket TypeInfo
    // <kao2.00514820> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_CAMERAZONEPACKET_ID = 0xCA3E7A05;

    extern TypeInfo E_CAMERAZONEPACKET_TYPEINFO;

}

#endif
