#ifndef H_KAO2AR_EMPTYVOIDINSTRUCTION
#define H_KAO2AR_EMPTYVOIDINSTRUCTION

#include <kao2engine/VoidInstruction.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // EmptyVoidInstruction interface
    ////////////////////////////////////////////////////////////////

    class EmptyVoidInstruction : public VoidInstruction
    {
        /*** Methods ***/

        public:

            EmptyVoidInstruction();
            ~EmptyVoidInstruction();

            TypeInfo* getType() const override;

            void saveInstructionToTextFile(FileOperator &file, int32_t indentation) const override;
    };


    ////////////////////////////////////////////////////////////////
    // EmptyVoidInstruction TypeInfo
    // <kao2.005918B0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_EMPTYVOIDINSTRUCTION_ID = 0x00022017;

    extern TypeInfo E_EMPTYVOIDINSTRUCTION_TYPEINFO;

}

#endif
