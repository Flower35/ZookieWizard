#ifndef H_KAO2AR_STATUSINSTRUCTION
#define H_KAO2AR_STATUSINSTRUCTION

#include <kao2engine/BaseStatusInstruction.h>

namespace ZookieWizard
{
    class Gadget;

    ////////////////////////////////////////////////////////////////
    // StatusInstruction interface
    ////////////////////////////////////////////////////////////////

    class StatusInstruction : public BaseStatusInstruction
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/ Gadget* unknown_10;
            int32_t unknown_new_id;

        /*** Methods ***/

        public:

            StatusInstruction();
            ~StatusInstruction();

            void serialize(Archive &ar) override;
            TypeInfo* getType() override;

            eString generateScriptText() override;
    };


    ////////////////////////////////////////////////////////////////
    // StatusInstruction TypeInfo
    // <kao2.0058E080> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_STATUSINSTRUCTION_ID = 0x00022008;

    extern TypeInfo E_STATUSINSTRUCTION_TYPEINFO;

}

#endif
