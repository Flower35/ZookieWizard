#ifndef H_KAO2AR_ANIM
#define H_KAO2AR_ANIM

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Anim interface
    ////////////////////////////////////////////////////////////////

    class Anim : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/ uint8_t unknown_10;
            /*[0x14]*/ int32_t unknown_14;
            /*[0x18]*/ float unknown_18;

        /*** Methods ***/

        public:

            Anim();
            ~Anim();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            eString getDefaultGadgetName() const override;
    };


    ////////////////////////////////////////////////////////////////
    // Anim TypeInfo
    // <kao2.0059C760> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_ANIM_ID = 0x00020001;

    extern TypeInfo E_ANIM_TYPEINFO;

}

#endif
