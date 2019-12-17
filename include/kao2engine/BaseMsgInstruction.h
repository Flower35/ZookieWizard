#ifndef H_KAO2AR_BASEMSGINSTRUCTION
#define H_KAO2AR_BASEMSGINSTRUCTION

#include <kao2engine/VoidInstruction.h>

namespace ZookieWizard
{
    ////////////////////////////////////////////////////////////////
    // BaseMsgInstruction interface
    ////////////////////////////////////////////////////////////////

    class BaseMsgInstruction : public VoidInstruction
    {

        /*** Properties ***/

        protected:

            /*[0x08]*/ eString message;
            /*[0x0C]*/ eRefCounter* argument; // "NodeRef" or "eFloat"

        /*** Methods ***/

        public:

            BaseMsgInstruction();
            ~BaseMsgInstruction();

            void serialize(Archive &ar) override;
            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // BaseMsgInstruction TypeInfo
    // <kao2.0058E8B0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_BASEMSGINSTRUCTION_ID = 0x0002220B;

    extern TypeInfo E_BASEMSGINSTRUCTION_TYPEINFO;

}

#endif
