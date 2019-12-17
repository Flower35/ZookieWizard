#ifndef H_KAO2AR_PLASZCZKA
#define H_KAO2AR_PLASZCZKA

#include <kao2engine/eWalk.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePlaszczka interface
    // <kao2.005CFA28> (vptr)
    ////////////////////////////////////////////////////////////////

    class ePlaszczka : public eWalk
    {

        /*** Properties ***/

        protected:

            /*[0x88]*/
            /*(...)*/
            /*[0xA0]*/

        /*** Methods ***/

        public:

            ePlaszczka();
            ~ePlaszczka();

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // ePlaszczka TypeInfo
    // <kao2.0044DB20> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_PLASZCZKA_ID = 0xF0C1A024;

    extern TypeInfo E_PLASZCZKA_TYPEINFO;

}

#endif
