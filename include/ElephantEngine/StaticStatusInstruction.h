#ifndef H_KAO2AR_STATICSTATUSINSTRUCTION
#define H_KAO2AR_STATICSTATUSINSTRUCTION

#include <ElephantEngine/BaseStatusInstruction.h>

namespace ZookieWizard
{
    class Gadget;

    ////////////////////////////////////////////////////////////////
    // StaticStatusInstruction interface
    // <kao2.005D7E4C> (vptr)
    ////////////////////////////////////////////////////////////////

    class StaticStatusInstruction : public BaseStatusInstruction
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/ Gadget* link;

        /*** Methods ***/

        public:

            StaticStatusInstruction();
            ~StaticStatusInstruction();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            eString generateScriptText() const override;
    };


    ////////////////////////////////////////////////////////////////
    // StaticStatusInstruction TypeInfo
    // <kao2.0058E2E0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_STATICSTATUSINSTRUCTION_ID = 0x00022308;

    extern TypeInfo E_STATICSTATUSINSTRUCTION_TYPEINFO;

}

#endif
