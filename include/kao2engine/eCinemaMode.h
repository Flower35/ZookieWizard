#ifndef H_KAO2AR_CINEMAMODE
#define H_KAO2AR_CINEMAMODE

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCinemaMode interface
    ////////////////////////////////////////////////////////////////

    class eCinemaMode : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x40]*/

        /*** Methods ***/

        public:

            eCinemaMode();
            ~eCinemaMode();

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eCinemaMode TypeInfo
    // <kao2.0043BD90> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_CINEMAMODE_ID = 0x394321F4;

    extern TypeInfo E_CINEMAMODE_TYPEINFO;

}

#endif
