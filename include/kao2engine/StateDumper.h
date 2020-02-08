#ifndef H_KAO2AR_STATEDUMPER
#define H_KAO2AR_STATEDUMPER

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // StateDumper interface
    // <kao2.005E12C8> (vptr)
    ////////////////////////////////////////////////////////////////

    class StateDumper : public Gadget
    {

        /*** Methods ***/

        public:

            StateDumper();
            ~StateDumper();

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // StateDumper TypeInfo
    // <kao2.005AFF80> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_STATEDUMPER_ID = 0x07EA1234;

    extern TypeInfo E_STATEDUMPER_TYPEINFO;

}

#endif
