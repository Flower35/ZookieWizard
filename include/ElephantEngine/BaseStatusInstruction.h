#ifndef H_KAO2AR_BASESTATUSINSTRUCTION
#define H_KAO2AR_BASESTATUSINSTRUCTION

#include <ElephantEngine/BoolInstruction.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // BaseStatusInstruction interface
    ////////////////////////////////////////////////////////////////

    class BaseStatusInstruction : public BoolInstruction
    {

        /*** Properties ***/

        protected:

            /*[0x08]*/ eString unknown_08;
            /*[0x0C]*/ eRefCounter* unknown_0C; // "eFloat", "eString2".

        /*** Methods ***/

        public:

            BaseStatusInstruction();
            ~BaseStatusInstruction();

            void serialize(Archive &ar) override;
            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // BaseStatusInstruction TypeInfo
    // <kao2.0058DD30> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_BASESTATUSINSTRUCTION_ID = 0x00022208;

    extern TypeInfo E_BASESTATUSINSTRUCTION_TYPEINFO;

}

#endif
