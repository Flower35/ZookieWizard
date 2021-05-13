#ifndef H_KAO2AR_IFELSEINSTRUCTION
#define H_KAO2AR_IFELSEINSTRUCTION

#include <ElephantEngine/IfInstruction.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // IfElseInstruction interface
    // <kao2.005D7DD4> (vptr)
    ////////////////////////////////////////////////////////////////

    class IfElseInstruction : public IfInstruction
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/ VoidInstruction* otherInstruction;

        /*** Methods ***/

        public:

            IfElseInstruction(BoolInstruction* x, VoidInstruction* y, VoidInstruction* z);
            ~IfElseInstruction();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            void saveInstructionToTextFile(FileOperator &file, int32_t indentation) const override;
    };


    ////////////////////////////////////////////////////////////////
    // IfElseInstruction TypeInfo
    // <kao2.0058D8A0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_IFELSEINSTRUCTION_ID = 0x00022007;

    extern TypeInfo E_IFELSEINSTRUCTION_TYPEINFO;

}

#endif
