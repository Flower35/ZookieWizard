#ifndef H_KAO2AR_RND
#define H_KAO2AR_RND

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Rnd interface
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

            TypeInfo* getType() const override;

            eString getDefaultGadgetName() const override;
    };


    ////////////////////////////////////////////////////////////////
    // Rnd TypeInfo
    // <kao2.0059B410> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_RND_ID = 0x00020004;

    extern TypeInfo E_RND_TYPEINFO;


    ////////////////////////////////////////////////////////////////
    // Static Gadget
    ////////////////////////////////////////////////////////////////

    extern Rnd theRnd;

}

#endif
