#ifndef H_KAO2AR_FSSPRITE
#define H_KAO2AR_FSSPRITE

#include <kao2engine/eFSOp.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFSSprite interface
    ////////////////////////////////////////////////////////////////

    class eFSSprite : public eFSOp
    {

        /*** Properties ***/

        protected:

            /*(...)*/
            /*[0x74]*/

        /*** Methods ***/

        public:

            eFSSprite();
            ~eFSSprite();

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eFSSprite TypeInfo
    // <kao2.00553EE0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_FSSPRITE_ID = 0xFF777790;

    extern TypeInfo E_FSSPRITE_TYPEINFO;


    ////////////////////////////////////////////////////////////////
    // Static Gadget
    ////////////////////////////////////////////////////////////////

    extern eFSSprite theFSSprite;

}

#endif
