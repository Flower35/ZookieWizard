#ifndef H_KAO2AR_LAVAFLAKES
#define H_KAO2AR_LAVAFLAKES

#include <kao2engine/eSnow.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eLavaFlakes interface
    // <kao2.005D6EC8> (vptr)
    ////////////////////////////////////////////////////////////////

    class eLavaFlakes : public eSnow
    {

        /*** Methods ***/

        public:

            eLavaFlakes();
            ~eLavaFlakes();

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eLavaFlakes TypeInfo
    // <kao2.00561700> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_LAVAFLAKES_ID = 0x0323A7F9;

    extern TypeInfo E_LAVAFLAKES_TYPEINFO;

}

#endif
