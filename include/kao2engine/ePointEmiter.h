#ifndef H_KAO2AR_POINTEMITER
#define H_KAO2AR_POINTEMITER

#include <kao2engine/eParticleEmiter.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePointEmiter interface
    // <kao2.005D64E0> (vptr)
    ////////////////////////////////////////////////////////////////

    class ePointEmiter : public eParticleEmiter
    {
        /*** Methods ***/

        public:

            ePointEmiter();
            ~ePointEmiter();

        private:

            void createFromOtherObject(const ePointEmiter &other);

        public:

            ePointEmiter(const ePointEmiter &other);
            ePointEmiter& operator = (const ePointEmiter &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // ePointEmiter TypeInfo
    // <kao2.005536A0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_POINTEMITER_ID = 0x0001E001;

    extern TypeInfo E_POINTEMITER_TYPEINFO;

}

#endif
