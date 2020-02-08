#ifndef H_KAO2AR_ENEMYMAPUPGRADER
#define H_KAO2AR_ENEMYMAPUPGRADER

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eEnemyMapUpgrader interface
    ////////////////////////////////////////////////////////////////

    class eEnemyMapUpgrader : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x58]*/

        /*** Methods ***/

        public:

            eEnemyMapUpgrader();
            ~eEnemyMapUpgrader();

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eEnemyMapUpgrader TypeInfo
    // <kao2.0045D410> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_ENEMYMAPUPGRADER_ID = 0x3A5EB586;

    extern TypeInfo E_ENEMYMAPUPGRADER_TYPEINFO;

}

#endif
