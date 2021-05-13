#ifndef H_KAO2AR_SENDINSTRUCTION
#define H_KAO2AR_SENDINSTRUCTION

#include <ElephantEngine/VoidInstruction.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // SendInstruction interface
    // <kao2.005D7AE4> (vptr)
    ////////////////////////////////////////////////////////////////

    class SendInstruction : public VoidInstruction
    {

        /*** Properties ***/

        protected:

            /*[0x04]*/
            /*[0x08]*/ eString unknown_08;

        /*** Methods ***/

        public:

            SendInstruction();
            ~SendInstruction();

            void serialize(Archive &ar) override;
            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // SendInstruction TypeInfo
    // <kao2.00590800> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SENDINSTRUCTION_ID = 0x00020011;

    extern TypeInfo E_SENDINSTRUCTION_TYPEINFO;

}

#endif
