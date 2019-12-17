#ifndef H_KAO2AR_BUBBLEFLAKES
#define H_KAO2AR_BUBBLEFLAKES

#include <kao2engine/eForrestFlakes.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eBubbleFlakes interface
    // <kao2.005D7250> (vptr)
    ////////////////////////////////////////////////////////////////

    class eBubbleFlakes : public eForrestFlakes
    {

        /*** Methods ***/

        public:

            eBubbleFlakes();
            ~eBubbleFlakes();

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eBubbleFlakes TypeInfo
    // <kao2.005662E0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_BUBBLEFLAKES_ID = 0x0323A7E8;

    extern TypeInfo E_BUBBLEFLAKES_TYPEINFO;

}

#endif
