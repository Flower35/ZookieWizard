#ifndef H_KAO2AR_BOOLINSTRUCTION
#define H_KAO2AR_BOOLINSTRUCTION

#include <ElephantEngine/eRefCounter.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // BoolInstruction interface
    ////////////////////////////////////////////////////////////////

    class BoolInstruction : public eRefCounter
    {
        /*** Methods ***/

        public:

            BoolInstruction();
            ~BoolInstruction();

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // BoolInstruction TypeInfo
    // <kao2.0058C500> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_BOOLINSTRUCTION_ID = 0x00022002;

    extern TypeInfo E_BOOLINSTRUCTION_TYPEINFO;

}

#endif
