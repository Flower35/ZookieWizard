#ifndef H_KAO2AR_KEY
#define H_KAO2AR_KEY

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Key interface
    ////////////////////////////////////////////////////////////////

    class Key : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x08]*/ int32_t unknown08;

        /*** Methods ***/

        public:

            Key();
            ~Key();

            TypeInfo* getType() const override;

            eString getDefaultGadgetName() const override;
    };


    ////////////////////////////////////////////////////////////////
    // Key TypeInfo
    // <kao2.0059B000> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_KEY_ID = 0x00020003;

    extern TypeInfo E_KEY_TYPEINFO;


    ////////////////////////////////////////////////////////////////
    // Static Gadget
    ////////////////////////////////////////////////////////////////

    extern Key theKey;

}

#endif
