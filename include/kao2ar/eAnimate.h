#ifndef H_KAO2_ANIMATE
#define H_KAO2_ANIMATE

#include <kao2engine/eAnimState.h>

#include <kao2ar/Collection.h>

namespace ZookieWizard
{
    class Archive;

    ////////////////////////////////////////////////////////////////
    // 
    ////////////////////////////////////////////////////////////////

    struct eAnimate
    {
        /*** Properties ***/

            /*[0x04-0x0C]*/ Collection<ArFunctions::serialize_eRefCounter> tracks;
            /*[0x10]*/ eAnimState** stateA;
            /*[0x14]*/ eAnimState** stateB;
            /*[0x18]*/ bool unknown18;
            /*[0x34]*/ int32_t unknown34;
            /*[0x38]*/ bool unknown38;

            /*(kao3)[0x0120]*/ int32_t states_count;
            /*(kao3)[0x012C]*/ eAnimState state[1];

        /*** Methods ***/

            eAnimate();
            ~eAnimate();

            void serialize(Archive &ar);

            void setAnimation(int32_t anim_id, float time);
    };

    namespace ArFunctions
    {
        void serialize_AnimStates(Archive &ar, eAnimState** &s);
    }

}

#endif
