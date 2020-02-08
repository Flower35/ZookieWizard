#ifndef H_KAO2AR_ANIMSTATE
#define H_KAO2AR_ANIMSTATE

#include <kao2engine/eRefCounter.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eAnimState interface
    ////////////////////////////////////////////////////////////////

    class eAnimState : public eRefCounter
    {

        /*** Properties ***/

        protected:

            /*[0x08]*/ int32_t aID; // ID tracka w arrayu innego obiektu do animacji.
            /*[0x0C]*/ float unknown0C;
            /*[0x10]*/ float time; // ogólny czas liczony w "keyframes", wci¹¿ roœnie.
            /*[0x14]*/ float unknown14;
            /*[0x18]*/ float citt; // obecny "keyframe"
            /*[0x1C]*/ float pitt; // obecny "keyframe"
            /*[0x20]*/ float cott;
            /*[0x24]*/ float pott;
            /*[0x28]*/ float bt;
            /*[0x2C]*/ float bs;
            /*[0x30]*/ float w;
            /*[0x34]*/ float startFrame; // kopia z eTrack[0x08]
            /*[0x38]*/ float endFrame; // kopia z eTrack[0x10]
            /*[0x3C]*/ int32_t loopType; // kopia z eTrack[0x14]
            /*[0x40]*/ float bef;
            /*[0x44]*/ float bet;

        /*** Methods ***/

        public:

            eAnimState();
            ~eAnimState();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            float getTime() const;
            void setTime(float current_time);

            int getAnimId() const;
            void setAnimId(int32_t current_anim_id);
    };


    ////////////////////////////////////////////////////////////////
    // eAnimState TypeInfo
    // <kao2.004B6850> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_ANIMSTATE_ID = 0xAC000001;

    extern TypeInfo E_ANIMSTATE_TYPEINFO;

}

#endif
