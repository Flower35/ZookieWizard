#ifndef H_KAO2AR_BOXZONE
#define H_KAO2AR_BOXZONE

#include <kao2engine/eZone.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eBoxZone interface
    ////////////////////////////////////////////////////////////////

    class eBoxZone : public eZone
    {
        /*** Methods ***/

        public:

            eBoxZone();
            ~eBoxZone();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            void renderObject(eAnimate* anim, int32_t draw_flags, eSRP &parent_srp) override;
    };


    ////////////////////////////////////////////////////////////////
    // eBoxZone TypeInfo
    // <kao2.0049E340> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_BOXZONE_ID = 0xFE02;

    extern TypeInfo E_BOXZONE_TYPEINFO;

}

#endif
