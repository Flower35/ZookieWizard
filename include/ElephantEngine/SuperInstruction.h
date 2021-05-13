#ifndef H_KAO2AR_SUPERINSTRUCTION
#define H_KAO2AR_SUPERINSTRUCTION

#include <ElephantEngine/VoidInstruction.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // SuperInstruction interface
    // <kao2.005D7F48> (vptr)
    ////////////////////////////////////////////////////////////////

    class SuperInstruction : public VoidInstruction
    {

        /*** Properties ***/

        protected:

            /*[0x04]*/
            /*[0x08]*/ VoidInstruction* unknown_08;

        /*** Methods ***/

        public:

            SuperInstruction(VoidInstruction* x);
            ~SuperInstruction();

            void serialize(Archive &ar) override;
            const TypeInfo* getType() const override;

            void saveInstructionToTextFile(FileOperator &file, int32_t indentation) const override;
    };


    ////////////////////////////////////////////////////////////////
    // SuperInstruction TypeInfo
    // <kao2.0058FF80> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SUPERINSTRUCTION_ID = 0x0002200C;

    extern TypeInfo E_SUPERINSTRUCTION_TYPEINFO;

}

#endif
