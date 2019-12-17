#ifndef H_KAO2AR_MULTITRANSFORM
#define H_KAO2AR_MULTITRANSFORM

#include <kao2engine/eGroup.h>

namespace ZookieWizard
{
    ////////////////////////////////////////////////////////////////
    // Transform structure
    ////////////////////////////////////////////////////////////////

    struct eMultiTransformBase
    {
        /*** Properties ***/

            /*[0x00-0x08]*/ float unknown_00[3];
            /*[0x0C]*/ uint8_t unknown_0C[4];
            /*[0x10-0x18]*/ float unknown_10[3];
            /*[0x1C]*/ float unknown_1C;

            /*[0x20-0x2C]*/ float unknown_20[4];
            /*[0x30-0x3C]*/ float unknown_30[4];

        /*** Methods ***/

            void serializeTransform(Archive &ar);
    };


    ////////////////////////////////////////////////////////////////
    // eMultiTransform interface
    ////////////////////////////////////////////////////////////////

    class eMultiTransform : public eGroup
    {

        /*** Properties ***/

        protected:

            /*[0x48]*/ int32_t transformsCount;
            /*[0x4C]*/ int32_t transformsMaxLength;
            /*[0x50]*/ eMultiTransformBase* transforms;

            /*[0x54]*/ float unknown_54;
            /*[0x58]*/ float unknown_58;
            /*[0x5C]*/ float unknown_5C;
            /*[0x60]*/ float unknown_60;
            /*[0x64]*/ int32_t unknown_64;

        /*** Methods ***/

        public:

            eMultiTransform();
            ~eMultiTransform();

            void serialize(Archive &ar) override;
            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eMultiTransform TypeInfo
    // <kao2.004B12C0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_MULTITRANSFORM_ID = 0x81128112;

    extern TypeInfo E_MULTITRANSFORM_TYPEINFO;

}

#endif
