#ifndef H_KAO2AR_MCASTINSTANCEINSTRUCTION
#define H_KAO2AR_MCASTINSTANCEINSTRUCTION

#include <ElephantEngine/SendInstruction.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // McastInstanceInstruction interface
    // <kao2.005D7B3C> (vptr)
    ////////////////////////////////////////////////////////////////

    class McastInstanceInstruction : public SendInstruction
    {

        /*** Properties ***/

        protected:

            /*[0x0C]*/ eString instanceName;

        /*** Methods ***/

        public:

            McastInstanceInstruction();
            ~McastInstanceInstruction();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            void saveInstructionToTextFile(FileOperator &file, int32_t indentation) const override;
    };


    ////////////////////////////////////////////////////////////////
    // McastInstanceInstruction TypeInfo
    // <kao2.00590C30> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_MCASTINSTANCEINSTRUCTION_ID = 0x00020013;

    extern TypeInfo E_MCASTINSTANCEINSTRUCTION_TYPEINFO;

}

#endif
