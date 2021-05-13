#ifndef H_KAO2AR_ANIM
#define H_KAO2AR_ANIM

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Anim interface
    // <kao2.005D8468> (vptr)
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

        private:

            void createFromOtherObject(const Anim &other);

        public:

            Anim(const Anim &other);
            Anim& operator = (const Anim &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            /* << Gadget >> */

            eString getDefaultGadgetName() const override;
    };


    ////////////////////////////////////////////////////////////////
    // Anim TypeInfo
    // <kao2.0059C730> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_ANIM_ID = 0x00020001;

    extern TypeInfo E_ANIM_TYPEINFO;

}

#endif
