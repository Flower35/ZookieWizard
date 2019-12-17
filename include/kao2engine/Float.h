#ifndef H_KAO2AR_FLOAT_GADGET
#define H_KAO2AR_FLOAT_GADGET

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Float interface
    ////////////////////////////////////////////////////////////////

    class Float : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/ float value;

        /*** Methods ***/

        public:

            Float();
            ~Float();

            void serialize(Archive &ar) override;
            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // Float TypeInfo
    // <kao2.0059AD20> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_FLOAT_GADGET_ID = 0x0002000D;

    extern TypeInfo E_FLOAT_GADGET_TYPEINFO;

}

#endif
