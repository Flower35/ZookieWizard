#ifndef H_KAO2AR_BLOCKINSTRUCTION
#define H_KAO2AR_BLOCKINSTRUCTION

#include <ElephantEngine/VoidInstruction.h>

#include <ElephantBase/Collection.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // BlockInstruction interface
    ////////////////////////////////////////////////////////////////

    class BlockInstruction : public VoidInstruction
    {

        /*** Properties ***/

        protected:

            /*[0x08-0x10]*/ Collection<ArFunctions::serialize_eRefCounter> instructions;

        /*** Methods ***/

        public:

            BlockInstruction();
            ~BlockInstruction();

            void serialize(Archive &ar) override;
            const TypeInfo* getType() const override;

            virtual void saveInstructionToTextFile(FileOperator &file, int32_t indentation) const override;
    };


    ////////////////////////////////////////////////////////////////
    // BlockInstruction TypeInfo
    // <kao2.0058F410> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_BLOCKINSTRUCTION_ID = 0x0002200A;

    extern TypeInfo E_BLOCKINSTRUCTION_TYPEINFO;

}

#endif
