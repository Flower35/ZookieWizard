#ifndef H_KAO2_ANIMATE
#define H_KAO2_ANIMATE

#include <ElephantEngine/eAnimState.h>

#include <ElephantBase/Collection.h>

namespace ZookieWizard
{
    class Archive;

    ////////////////////////////////////////////////////////////////
    // Animation sub-class for "ePivot"
    ////////////////////////////////////////////////////////////////

    struct eAnimate
    {
        /*** Properties ***/

        public:

            /*[0x04-0x0C]*/ Collection<ArFunctions::serialize_eRefCounter> tracks;
            /*[0x10]*/ eAnimState** animStateA;
            /*[0x14]*/ eAnimState** animStateB;
            /*[0x18]*/ bool isPaused;
            /*[0x1C]*/ // float deltaFrameTime;
            /*[0x34]*/ int32_t unknown_34;
            /*[0x38]*/ bool unknown_38;

            /*(kao3)[0x0120]*/ int32_t animStatesCount;
            /*(kao3)[0x012C]*/ eAnimState currentAnimState[1];

        /*** Methods ***/

        public:

            eAnimate();
            ~eAnimate();

        private:

            void createFromOtherObject(const eAnimate &other);

        public:

            eAnimate(const eAnimate &other);
            eAnimate& operator = (const eAnimate &other);

            void clearAnimStateContainers();

            void serialize(Archive &ar);

            void setAnimation(int32_t anim_id, float time);

            void rebuildEmptyAnimState(bool is_root);
    };

    namespace ArFunctions
    {
        void serialize_AnimStates(Archive &ar, eAnimState** &s);
    }

}

#endif
