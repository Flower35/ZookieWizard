#ifndef H_KAO2AR_OMNILIGHT
#define H_KAO2AR_OMNILIGHT

#include <kao2engine/eLight.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eOmniLight interface
    ////////////////////////////////////////////////////////////////

    class eOmniLight : public eLight
    {

        /*** Properties ***/

        protected:

            /*[0x6C-0x80]*/ float direction[6];

        /*** Methods ***/

        public:

            eOmniLight();
            ~eOmniLight();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eOmniLight TypeInfo
    // <kao2.0047F5D0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_OMNILIGHT_ID = 0x03454502;

    extern TypeInfo E_OMNILIGHT_TYPEINFO;

}

#endif
