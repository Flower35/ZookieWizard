#ifndef H_KAO2AR_TURNCOLLISIONOFF
#define H_KAO2AR_TURNCOLLISIONOFF

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eTurnCollisionOff interface
    // <kao2.005D8288> (vptr)
    ////////////////////////////////////////////////////////////////

    class eTurnCollisionOff : public Gadget
    {

        /*** Methods ***/

        public:

            eTurnCollisionOff();
            ~eTurnCollisionOff();

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eTurnCollisionOff TypeInfo
    // <kao2.0059A1B0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_TURNCOLLISIONOFF_ID = 0x0002FCC1;

    extern TypeInfo E_TURNCOLLISIONOFF_TYPEINFO;

}

#endif
