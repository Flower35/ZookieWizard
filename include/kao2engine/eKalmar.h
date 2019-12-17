#ifndef H_KAO2AR_KALMAR
#define H_KAO2AR_KALMAR

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eKalmar interface
    // <kao2.005D5900> (vptr)
    ////////////////////////////////////////////////////////////////

    class eKalmar : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x70]*/

        /*** Methods ***/

        public:

            eKalmar();
            ~eKalmar();

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eKalmar TypeInfo
    // <kao2.00527DA0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_KALMAR_ID = 0x01234321;

    extern TypeInfo E_KALMAR_TYPEINFO;

}

#endif
