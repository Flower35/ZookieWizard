#ifndef H_KAO2AR_STATICMSGINSTRUCTION
#define H_KAO2AR_STATICMSGINSTRUCTION

#include <kao2engine/BaseMsgInstruction.h>

namespace ZookieWizard
{
    class Gadget;

    ////////////////////////////////////////////////////////////////
    // StaticMsgInstruction interface
    ////////////////////////////////////////////////////////////////

    class StaticMsgInstruction : public BaseMsgInstruction
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/ Gadget* link;

        /*** Methods ***/

        public:

            StaticMsgInstruction();
            ~StaticMsgInstruction();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            void saveInstructionToTextFile(FileOperator &file, int32_t indentation) const override;
    };


    ////////////////////////////////////////////////////////////////
    // StaticMsgInstruction TypeInfo
    // <kao2.0058EE60> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_STATICMSGINSTRUCTION_ID = 0x0002230B;

    extern TypeInfo E_STATICMSGINSTRUCTION_TYPEINFO;

}

#endif
