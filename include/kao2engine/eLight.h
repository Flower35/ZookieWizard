#ifndef H_KAO2AR_LIGHT
#define H_KAO2AR_LIGHT

#include <kao2engine/eNode.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eLight interface
    ////////////////////////////////////////////////////////////////

    class eLight : public eNode
    {

        /*** Properties ***/

        protected:

            /*[0x3C-0x48]*/ float diffuse[4];
            /*[0x4C-0x58]*/ float ambient[4];
            /*[0x5C-0x68]*/ float specular[4];

        /*** Methods ***/

        public:

            eLight();
            ~eLight();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eLight TypeInfo
    // <kao2.0047F0F0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_LIGHT_ID = 0x03454500;

    extern TypeInfo E_LIGHT_TYPEINFO;

}

#endif
