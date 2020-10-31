#ifndef H_KAO2AR_MATERIALSTATE
#define H_KAO2AR_MATERIALSTATE

#include <kao2engine/eRefCounter.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eMaterialState interface
    // <kao2.005D0F68> (vptr)
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
            /*[0x4C]*/ bool useGlobalAmbientLight;

        /*** Methods ***/

        public:

            eMaterialState();
            ~eMaterialState();

        private:

            void createFromOtherObject(const eMaterialState &other);

        public:

            eMaterialState(const eMaterialState &other);
            eMaterialState& operator = (const eMaterialState &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            /* << eMaterialState >> */

            bool checkSimilarityToAnotherState(const eMaterialState &other) const;

            void getAmbientColor(float* values) const;
            void getDiffuseColor(float* values) const;
            void getEmissiveColor(float* values) const;
            void getSpecularColor(float* values) const;
            float getShininess() const;
            bool getGlobalAmbientLightState() const;

            void setAmbientColor(float* values);
            void setDiffuseColor(float* values);
            void setEmissiveColor(float* values);
            void setSpecularColor(float* values);
            void setShininess(float value);
            void setGlobalAmbientLightState(bool value);
    };


    ////////////////////////////////////////////////////////////////
    // eMaterialState TypeInfo
    // <kao2.00482B20> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_MATERIALSTATE_ID = 0x1005;

    extern TypeInfo E_MATERIALSTATE_TYPEINFO;


    ////////////////////////////////////////////////////////////////
    // Global Material States counter
    ////////////////////////////////////////////////////////////////

    extern int32_t theMaterialStatesCounter;

}

#endif
