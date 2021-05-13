#ifndef H_KAO2AR_MCASTCLASSINSTRUCTION
#define H_KAO2AR_MCASTCLASSINSTRUCTION

#include <ElephantEngine/SendInstruction.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // McastClassInstruction interface
    // <kao2.005D7B10> (vptr)
    ////////////////////////////////////////////////////////////////

    class McastClassInstruction : public SendInstruction
    {

        /*** Properties ***/

        protected:

            /*[0x0C]*/ eString className;

        /*** Methods ***/

        public:

            McastClassInstruction();
            ~McastClassInstruction();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            void saveInstructionToTextFile(FileOperator &file, int32_t indentation) const override;
    };


    ////////////////////////////////////////////////////////////////
    // McastClassInstruction TypeInfo
    // <kao2.00590D20> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_MCASTCLASSINSTRUCTION_ID = 0x00020014;

    extern TypeInfo E_MCASTCLASSINSTRUCTION_TYPEINFO;

}

#endif
