#ifndef H_KAO2AR_EGGSFACTORY
#define H_KAO2AR_EGGSFACTORY

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eEggsFactory interface
    // <kao2.005D46A8> (vptr)
    ////////////////////////////////////////////////////////////////

    class eEggsFactory : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x34]*/

        /*** Methods ***/

        public:

            eEggsFactory();
            ~eEggsFactory();

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eEggsFactory TypeInfo
    // <kao2.005068D0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_EGGSFACTORY_ID = 0x3BF54C3F;

    extern TypeInfo E_EGGSFACTORY_TYPEINFO;

}

#endif
