#ifndef H_KAO2AR_KEY
#define H_KAO2AR_KEY

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Key interface
    // <kao2.005D8378> (vptr)
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

        private:

            void createFromOtherObject(const Key &other);

        public:

            Key(const Key &other);
            Key& operator = (const Key &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;

            /* << Gadget >> */

            eString getDefaultGadgetName() const override;
    };


    ////////////////////////////////////////////////////////////////
    // Key TypeInfo
    // <kao2.0059AFD0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_KEY_ID = 0x00020003;

    extern TypeInfo E_KEY_TYPEINFO;


    ////////////////////////////////////////////////////////////////
    // Static Gadget
    ////////////////////////////////////////////////////////////////

    extern Key theKey;

}

#endif
