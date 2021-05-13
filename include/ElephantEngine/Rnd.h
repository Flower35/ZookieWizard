#ifndef H_KAO2AR_RND
#define H_KAO2AR_RND

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Rnd interface
    // <kao2.005D83C8> (vptr)
    ////////////////////////////////////////////////////////////////

    class Rnd : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/ int32_t unknown_10;

        /*** Methods ***/

        public:

            Rnd();
            ~Rnd();

        private:

            void createFromOtherObject(const Rnd &other);

        public:

            Rnd(const Rnd &other);
            Rnd& operator = (const Rnd &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;

            /* << Gadget >> */

            eString getDefaultGadgetName() const override;
    };


    ////////////////////////////////////////////////////////////////
    // Rnd TypeInfo
    // <kao2.0059B3E0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_RND_ID = 0x00020004;

    extern TypeInfo E_RND_TYPEINFO;


    ////////////////////////////////////////////////////////////////
    // Static Gadget
    ////////////////////////////////////////////////////////////////

    extern Rnd theRnd;

}

#endif
