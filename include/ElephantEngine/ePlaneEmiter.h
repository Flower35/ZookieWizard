#ifndef H_KAO2AR_PLANEEMITER
#define H_KAO2AR_PLANEEMITER

#include <ElephantEngine/eParticleEmiter.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePlaneEmiter interface
    // <kao2.005D6658> (vptr)
    ////////////////////////////////////////////////////////////////

    class ePlaneEmiter : public eParticleEmiter
    {
        /*** Properties ***/

        protected:

            /*[0x021C]*/ float unknown_021C;
            /*[0x0220]*/ float unknown_0220;

        /*** Methods ***/

        public:

            ePlaneEmiter();
            ~ePlaneEmiter();

        private:

            void createFromOtherObject(const ePlaneEmiter &other);

        public:

            ePlaneEmiter(const ePlaneEmiter &other);
            ePlaneEmiter& operator = (const ePlaneEmiter &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
            void serialize(Archive &ar) override;
    };


    ////////////////////////////////////////////////////////////////
    // ePlaneEmiter TypeInfo
    // <kao2.00553840> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_PLANEEMITER_ID = 0x0001E003;

    extern TypeInfo E_PLANEEMITER_TYPEINFO;

}

#endif
