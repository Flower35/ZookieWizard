#ifndef H_KAO2AR_NODEREFSENDINSTRUCTION
#define H_KAO2AR_NODEREFSENDINSTRUCTION

#include <ElephantEngine/VoidInstruction.h>

namespace ZookieWizard
{
    class NodeRef;

    ////////////////////////////////////////////////////////////////
    // NodeRefSendInstruction interface
    ////////////////////////////////////////////////////////////////

    class NodeRefSendInstruction : public VoidInstruction
    {

        /*** Properties ***/

        protected:

            /*[0x08]*/ NodeRef* receiver;
            /*[0x0C]*/ eString message;
            /*[0x10]*/ eRefCounter* argument; // "NodeRef", "Gadget".

        /*** Methods ***/

        public:

            NodeRefSendInstruction();
            ~NodeRefSendInstruction();

            void serialize(Archive &ar) override;
            const TypeInfo* getType() const override;

            void saveInstructionToTextFile(FileOperator &file, int32_t indentation) const override;
    };


    ////////////////////////////////////////////////////////////////
    // NodeRefSendInstruction TypeInfo
    // <kao2.005916A0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_NODEREFSENDINSTRUCTION_ID = 0x00020018;

    extern TypeInfo E_NODEREFSENDINSTRUCTION_TYPEINFO;

}

#endif
