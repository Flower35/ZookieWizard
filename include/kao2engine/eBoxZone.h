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

            bool renderObject(int32_t draw_flags, eAnimate* anim, eSRP &parent_srp, int32_t marked_id) override;

            ePoint3 editingGetCenterPoint() const override;
            void editingApplyNewTransform(eSRP &new_transform, int32_t marked_id) override;
    };


    ////////////////////////////////////////////////////////////////
    // eBoxZone TypeInfo
    // <kao2.0049E340> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_BOXZONE_ID = 0xFE02;

    extern TypeInfo E_BOXZONE_TYPEINFO;

}

#endif
