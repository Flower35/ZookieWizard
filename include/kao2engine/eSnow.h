#ifndef H_KAO2AR_SNOW
#define H_KAO2AR_SNOW

#include <kao2engine/eParticleGeometry.h>

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

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eSnow TypeInfo
    // <kao2.00560C80> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SNOW_ID = 0x0333A7F7;

    extern TypeInfo E_SNOW_TYPEINFO;

}

#endif
