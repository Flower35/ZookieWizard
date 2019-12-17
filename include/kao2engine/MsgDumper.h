#ifndef H_KAO2AR_MSGDUMPER
#define H_KAO2AR_MSGDUMPER

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // MsgDumper interface
    // <kao2.005E1318> (vptr)
    ////////////////////////////////////////////////////////////////

    class MsgDumper : public Gadget
    {

        /*** Methods ***/

        public:

            MsgDumper();
            ~MsgDumper();

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // MsgDumper TypeInfo
    // <kao2.005B00A0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_MSGDUMPER_ID = 0x07EA1005;

    extern TypeInfo E_MSGDUMPER_TYPEINFO;

}

#endif
