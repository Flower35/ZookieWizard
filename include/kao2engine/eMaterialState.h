#ifndef H_KAO2AR_MATERIALSTATE
#define H_KAO2AR_MATERIALSTATE

#include <kao2engine/eRefCounter.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eMaterialState interface
    ////////////////////////////////////////////////////////////////

    class eMaterialState : public eRefCounter
    {

        /*** Properties ***/

        protected:

            /*[0x08-0x14]*/ float ambient[4];
            /*[0x18-0x24]*/ float diffuse[4];
            /*[0x28-0x34]*/ float emissive[4];
            /*[0x38-0x44]*/ float specular[4];
            /*[0x48]*/ float shininess;
            /*[0x4C]*/ bool unknown_4C;

        /*** Methods ***/

        public:

            eMaterialState();
            ~eMaterialState();

            void serialize(Archive &ar) override;
            TypeInfo* getType() override;

            void getAmbientColor(float* values);
            void getDiffuseColor(float* values);
            void getSpecularColor(float* values);
            float getShininess();

            void setAmbientColor(float* values);
            void setDiffuseColor(float* values);
            void setSpecularColor(float* values);
            void setShininess(float value);
    };


    ////////////////////////////////////////////////////////////////
    // eMaterialState TypeInfo
    // <kao2.00482B50> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_MATERIALSTATE_ID = 0x1005;

    extern TypeInfo E_MATERIALSTATE_TYPEINFO;

}

#endif
