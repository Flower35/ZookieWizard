#ifndef H_KAO2AR_DIRECTIONCTRLEX
#define H_KAO2AR_DIRECTIONCTRLEX

#include <kao2engine/eDirectionCtrl.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eDirectionCtrlEx interface
    // <kao2.005D0308> (vptr)
    ////////////////////////////////////////////////////////////////

    class eDirectionCtrlEx : public eDirectionCtrl
    {

        /*** Properties ***/

        protected:

            /*[0x1C]*/

        /*** Methods ***/

        public:

            eDirectionCtrlEx();
            ~eDirectionCtrlEx();

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eDirectionCtrlEx TypeInfo
    // <kao2.00461950> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_DIRECTIONCTRLEX_ID = 0x00FEBEF1;

    extern TypeInfo E_DIRECTIONCTRLEX_TYPEINFO;

}

#endif
