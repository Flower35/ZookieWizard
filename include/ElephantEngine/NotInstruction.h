#ifndef H_KAO2AR_NOTINSTRUCTION
#define H_KAO2AR_NOTINSTRUCTION

#include <ElephantEngine/BoolInstruction.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // NotInstruction interface
    // <kao2.005D7DB0> (vptr)
    ////////////////////////////////////////////////////////////////

    class NotInstruction : public BoolInstruction
    {

        /*** Properties ***/

        protected:

            /*[0x08]*/ BoolInstruction* unknown_08;

        /*** Methods ***/

        public:

            NotInstruction(BoolInstruction* x);
            ~NotInstruction();

            void serialize(Archive &ar) override;
            const TypeInfo* getType() const override;

            eString generateScriptText() const override;
    };


    ////////////////////////////////////////////////////////////////
    // NotInstruction TypeInfo
    // <kao2.0058D360> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_NOTINSTRUCTION_ID = 0x00022006;

    extern TypeInfo E_NOTINSTRUCTION_TYPEINFO;

}

#endif
