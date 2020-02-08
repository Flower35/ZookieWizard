#ifndef H_KAO2AR_IFINSTRUCTION
#define H_KAO2AR_IFINSTRUCTION

#include <kao2engine/VoidInstruction.h>

namespace ZookieWizard
{
    class BoolInstruction;

    ////////////////////////////////////////////////////////////////
    // IfInstruction interface
    // <kao2.005D7D64> (vptr)
    ////////////////////////////////////////////////////////////////

    class IfInstruction : public VoidInstruction
    {

        /*** Properties ***/

        protected:

            /*[0x08]*/ BoolInstruction* condition;
            /*[0x0C]*/ VoidInstruction* instruction;

        /*** Methods ***/

        public:

            IfInstruction(BoolInstruction* x, VoidInstruction* y);
            ~IfInstruction();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            void saveInstructionToTextFile(FileOperator &file, int32_t indentation) const override;
    };


    ////////////////////////////////////////////////////////////////
    // IfInstruction TypeInfo
    // <kao2.0058CA10> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_IFINSTRUCTION_ID = 0x00022004;

    extern TypeInfo E_IFINSTRUCTION_TYPEINFO;

}

#endif
