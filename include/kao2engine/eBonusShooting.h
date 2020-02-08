#ifndef H_KAO2AR_BONUSSHOOTING
#define H_KAO2AR_BONUSSHOOTING

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eBonusShooting interface
    // <kao_tw.006A80B0> (vptr)
    ////////////////////////////////////////////////////////////////

    class eBonusShooting : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x38]*/

        /*** Methods ***/

        public:

            eBonusShooting();
            ~eBonusShooting();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eBonusShooting TypeInfo
    // <kao_tw.00650FA0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_BONUSSHOOTING_ID = 0x4147EF6E;

    extern TypeInfo E_BONUSSHOOTING_TYPEINFO;

}

#endif
