#ifndef H_KAO2AR_AFTERINSTRUCTION
#define H_KAO2AR_AFTERINSTRUCTION

#include <kao2engine/VoidInstruction.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // AfterInstruction interface
    ////////////////////////////////////////////////////////////////

    class AfterInstruction : public VoidInstruction
    {

        /*** Properties ***/

        protected:

            /*[0x08]*/
            /*[0x0C]*/ float time;
            /*[0x10]*/ VoidInstruction* instruction;

        /*** Methods ***/

        public:

            AfterInstruction();
            ~AfterInstruction();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            void saveInstructionToTextFile(FileOperator &file, int32_t indentation) const override;
    };


    ////////////////////////////////////////////////////////////////
    // AfterInstruction TypeInfo
    // <kao2.00591E90> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_AFTERINSTRUCTION_ID = 0x00020019;

    extern TypeInfo E_AFTERINSTRUCTION_TYPEINFO;

}

#endif
