#ifndef H_KAO2AR_ENEMYMAPUPGRADER
#define H_KAO2AR_ENEMYMAPUPGRADER

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eEnemyMapUpgrader interface
    // <kao2.005D0108> (vptr)
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

        private:

            void createFromOtherObject(const eEnemyMapUpgrader &other);

        public:

            eEnemyMapUpgrader(const eEnemyMapUpgrader &other);
            eEnemyMapUpgrader& operator = (const eEnemyMapUpgrader &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eEnemyMapUpgrader TypeInfo
    // <kao2.0045D3E0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_ENEMYMAPUPGRADER_ID = 0x3A5EB586;

    extern TypeInfo E_ENEMYMAPUPGRADER_TYPEINFO;

}

#endif
