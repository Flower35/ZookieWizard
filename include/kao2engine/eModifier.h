#ifndef H_KAO2AR_MODIFIER
#define H_KAO2AR_MODIFIER

#include <kao2engine/eRefCounter.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eModifier interface
    ////////////////////////////////////////////////////////////////

    class eModifier : public eRefCounter
    {
        public:

            eModifier();
            ~eModifier();

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eModifier TypeInfo
    // <kao2.0046D890> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_MODIFIER_ID = 0x4004;

    extern TypeInfo E_MODIFIER_TYPEINFO;

}

#endif
