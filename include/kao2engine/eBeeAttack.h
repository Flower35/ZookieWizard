#ifndef H_KAO2AR_BEEATTACK
#define H_KAO2AR_BEEATTACK

#include <kao2engine/ePathCtrl.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eBeeAttack interface
    // <kao2.005CE828> (vptr)
    ////////////////////////////////////////////////////////////////

    class eBeeAttack : public ePathCtrl
    {
        /*** Properties ***/

        protected:

            /*[0x50]*/ float unknown_50;
            /*[0x54]*/ float unknown_54;
            /*[0x58]*/ float unknown_58;

            /*[0x5C]*/ float unknown_5C;
            /*[0x60]*/ float unknown_60;
            /*[0x64]*/ float unknown_64;

            /*[0x68]*/

        /*** Methods ***/

        public:

            eBeeAttack();
            ~eBeeAttack();

        private:

            void createFromOtherObject(const eBeeAttack &other);

        public:

            eBeeAttack(const eBeeAttack &other);
            eBeeAttack& operator = (const eBeeAttack &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;
    };


    ////////////////////////////////////////////////////////////////
    // eBeeAttack TypeInfo
    // <kao2.0042ED50> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_BEEATTACK_ID = 0xF0A2A029;

    extern TypeInfo E_BEEATTACK_TYPEINFO;

}

#endif
