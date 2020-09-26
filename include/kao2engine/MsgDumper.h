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

        private:

            void createFromOtherObject(const MsgDumper &other);

        public:

            MsgDumper(const MsgDumper &other);
            MsgDumper& operator = (const MsgDumper &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // MsgDumper TypeInfo
    // <kao2.005B0070> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_MSGDUMPER_ID = 0x07EA1005;

    extern TypeInfo E_MSGDUMPER_TYPEINFO;

}

#endif
