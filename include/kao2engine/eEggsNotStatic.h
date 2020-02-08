#ifndef H_KAO2AR_EGGSNOTSTATIC
#define H_KAO2AR_EGGSNOTSTATIC

#include <kao2engine/eEggsFactory.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eEggsNotStatic interface
    // <kao2.005D4658> (vptr)
    ////////////////////////////////////////////////////////////////

    class eEggsNotStatic : public eEggsFactory
    {

        /*** Methods ***/

        public:

            eEggsNotStatic();
            ~eEggsNotStatic();

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eEggsNotStatic TypeInfo
    // <kao2.005069A0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_EGGSNOTSTATIC_ID = 0x3BF54C40;

    extern TypeInfo E_EGGSNOTSTATIC_TYPEINFO;

}

#endif
