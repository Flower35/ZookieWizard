#ifndef H_KAO2AR_TRANSFORM
#define H_KAO2AR_TRANSFORM

#include <kao2engine/eGroup.h>
#include <kao2engine/eCtrl.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eTransform interface
    ////////////////////////////////////////////////////////////////

    class eTransform : public eGroup
    {

        /*** Properties ***/

        protected:

            /*[0x48-0x64]*/ eSRP form01;
            /*[0x68-0x84]*/ eSRP form02;
            /*[0xA8]*/ eCtrl<eSRP>* ctrl;

            float transposedMatrix[16];

        /*** Methods ***/

        public:

            eTransform();
            ~eTransform();

            void serialize(Archive &ar) override;
            TypeInfo* getType() override;

            void renderObject(float time, int32_t draw_flags) override;
    };


    ////////////////////////////////////////////////////////////////
    // eTransform TypeInfo
    // <kao2.0047C5B0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_TRANSFORM_ID = 0x8112;

    extern TypeInfo E_TRANSFORM_TYPEINFO;

}

#endif
