#ifndef H_KAO2AR_SPHEREEMITER
#define H_KAO2AR_SPHEREEMITER

#include <ElephantEngine/eParticleEmiter.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSphereEmiter interface
    // <kao2.005D6720> (vptr)
    ////////////////////////////////////////////////////////////////

    class eSphereEmiter : public eParticleEmiter
    {
        /*** Properties ***/

        protected:

            /*[0x021C]*/ float unknown_021C;
            /*[0x0220]*/ uint8_t unknown_0220;

        /*** Methods ***/

        public:

            eSphereEmiter();
            ~eSphereEmiter();

        private:

            void createFromOtherObject(const eSphereEmiter &other);

        public:

            eSphereEmiter(const eSphereEmiter &other);
            eSphereEmiter& operator = (const eSphereEmiter &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;
    };


    ////////////////////////////////////////////////////////////////
    // eSphereEmiter TypeInfo
    // <kao2.00553910> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SPHEREEMITER_ID = 0x0001E004;

    extern TypeInfo E_SPHEREEMITER_TYPEINFO;

}

#endif
