#ifndef H_KAO2AR_MSGINSTRUCTION
#define H_KAO2AR_MSGINSTRUCTION

#include <kao2engine/BaseMsgInstruction.h>

namespace ZookieWizard
{
    class Gadget;

    ////////////////////////////////////////////////////////////////
    // MsgInstruction interface
    ////////////////////////////////////////////////////////////////

    class MsgInstruction : public BaseMsgInstruction
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/ Gadget* receiver;
            int32_t unknown_new_id;

        /*** Methods ***/

        public:

            MsgInstruction();
            ~MsgInstruction();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            void saveInstructionToTextFile(FileOperator &file, int32_t indentation) const override;
    };


    ////////////////////////////////////////////////////////////////
    // MsgInstruction TypeInfo
    // <kao2.0058EC00> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_MSGINSTRUCTION_ID = 0x0002200B;

    extern TypeInfo E_MSGINSTRUCTION_TYPEINFO;

}

#endif
