#ifndef H_KAO2AR_TARGETING
#define H_KAO2AR_TARGETING

#include <kao2engine/eEmptyCtrl.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eTargeting interface
    // <kao2.005CE7C0> (vptr)
    ////////////////////////////////////////////////////////////////

    class eTargeting : public eEmptyCtrl
    {

        /*** Properties ***/

        protected:

            /*[0x5C]*/
            /*(...)*/
            /*[0x6C]*/

        /*** Methods ***/

        public:

            eTargeting();
            ~eTargeting();

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eTargeting TypeInfo
    // <kao2.0042E6D0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_TARGETING_ID = 0xF002A029;

    extern TypeInfo E_TARGETING_TYPEINFO;

}

#endif
