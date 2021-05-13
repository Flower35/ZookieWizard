#ifndef H_KAO2AR_BONUSSHOOTING
#define H_KAO2AR_BONUSSHOOTING

#include <ElephantEngine/Gadget.h>

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

        private:

            void createFromOtherObject(const eBonusShooting &other);

        public:

            eBonusShooting(const eBonusShooting &other);
            eBonusShooting& operator = (const eBonusShooting &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;
    };


    ////////////////////////////////////////////////////////////////
    // eBonusShooting TypeInfo
    // <kao_tw.00650F70> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_BONUSSHOOTING_ID = 0x4147EF6E;

    extern TypeInfo E_BONUSSHOOTING_TYPEINFO;

}

#endif
