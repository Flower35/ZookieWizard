#ifndef H_KAO2AR_VIBRATE
#define H_KAO2AR_VIBRATE

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eVibrate interface
    // <kao2.005D2A40> (vptr)
    ////////////////////////////////////////////////////////////////

    class eVibrate : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x44]*/

        /*** Methods ***/

        public:

            eVibrate();
            ~eVibrate();

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eVibrate TypeInfo
    // <kao2.004CFB20> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_VIBRATE_ID = 0x0002FBAE;

    extern TypeInfo E_VIBRATE_TYPEINFO;

}

#endif
