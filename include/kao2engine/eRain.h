#ifndef H_KAO2AR_RAIN
#define H_KAO2AR_RAIN

#include <kao2engine/eSnow.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eRain interface
    // <kao2.005D6FF8> (vptr)
    ////////////////////////////////////////////////////////////////

    class eRain : public eSnow
    {

        /*** Properties ***/

        protected:

            /*[0x0100]*/
            /*(...)*/
            /*[0x0174]*/

        /*** Methods ***/

        public:

            eRain();
            ~eRain();

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eRain TypeInfo
    // <kao2.00564110> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_RAIN_ID = 0x0323A7F8;

    extern TypeInfo E_RAIN_TYPEINFO;

}

#endif
