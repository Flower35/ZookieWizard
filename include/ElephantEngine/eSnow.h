#ifndef H_KAO2AR_SNOW
#define H_KAO2AR_SNOW

#include <ElephantEngine/eParticleGeometry.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSnow interface
    // <kao2.005D6D88> (vptr)
    ////////////////////////////////////////////////////////////////

    class eSnow : public eParticleGeometry
    {
        /*** Properties ***/

        protected:

            /*[0xC8]*/
            /*(...)*/
            /*[0xFC]*/

        /*** Methods ***/

        public:

            eSnow();
            ~eSnow();

        private:

            void createFromOtherObject(const eSnow &other);

        public:

            eSnow(const eSnow &other);
            eSnow& operator = (const eSnow &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;
    };


    ////////////////////////////////////////////////////////////////
    // eSnow TypeInfo
    // <kao2.00560C50> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SNOW_ID = 0x0333A7F7;

    extern TypeInfo E_SNOW_TYPEINFO;

}

#endif
