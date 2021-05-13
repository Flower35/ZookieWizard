#ifndef H_KAO2AR_ANDINSTRUCTION
#define H_KAO2AR_ANDINSTRUCTION

#include <ElephantEngine/BoolInstruction.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // AndInstruction interface
    ////////////////////////////////////////////////////////////////

    class AndInstruction : public BoolInstruction
    {

        /*** Properties ***/

        protected:

            /*[0x08]*/ BoolInstruction* unknown_08;
            /*[0x0C]*/ BoolInstruction* unknown_0C;

        /*** Methods ***/

        public:

            AndInstruction(BoolInstruction* x, BoolInstruction* y);
            ~AndInstruction();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            eString generateScriptText() const override;
    };


    ////////////////////////////////////////////////////////////////
    // AndInstruction TypeInfo
    // <kao2.0058CF50> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_ANDINSTRUCTION_ID = 0x00022005;

    extern TypeInfo E_ANDINSTRUCTION_TYPEINFO;

}

#endif
