#ifndef H_KAO2AR_DIRECTIONALLIGHT
#define H_KAO2AR_DIRECTIONALLIGHT

#include <kao2engine/eLight.h>

namespace ZookieWizard
{
    class eTransform;

    ////////////////////////////////////////////////////////////////
    // eDirectionalLight interface
    ////////////////////////////////////////////////////////////////

    class eDirectionalLight : public eLight
    {

        /*** Properties ***/

        protected:

            /*[0x6C-0x74]*/ float direction[3];
            /*[0x78]*/ eTransform* unknown_78;

        /*** Methods ***/

        public:

            eDirectionalLight();
            ~eDirectionalLight();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eDirectionalLight TypeInfo
    // <kao2.0047FC90> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_DIRECTIONALLIGHT_ID = 0x03454501;

    extern TypeInfo E_DIRECTIONALLIGHT_TYPEINFO;

}

#endif
