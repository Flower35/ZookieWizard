#ifndef H_KAO2AR_FORRESTFLAKES
#define H_KAO2AR_FORRESTFLAKES

#include <kao2engine/eSnow.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eForrestFlakes interface
    // <kao2.005D6E28> (vptr)
    ////////////////////////////////////////////////////////////////

    class eForrestFlakes : public eSnow
    {

        /*** Methods ***/

        public:

            eForrestFlakes();
            ~eForrestFlakes();

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eForrestFlakes TypeInfo
    // <kao2.00561200> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_FORRESTFLAKES_ID = 0x0323A7F7;

    extern TypeInfo E_FORRESTFLAKES_TYPEINFO;

}

#endif
