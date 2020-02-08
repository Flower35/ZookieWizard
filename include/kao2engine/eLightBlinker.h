#ifndef H_KAO2AR_LIGHTBLINKER
#define H_KAO2AR_LIGHTBLINKER

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eLightBlinker interface
    // <kao2.005D5A68> (vptr)
    ////////////////////////////////////////////////////////////////

    class eLightBlinker : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x8C]*/

        /*** Methods ***/

        public:

            eLightBlinker();
            ~eLightBlinker();

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eLightBlinker TypeInfo
    // <kao2.00529400> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_LIGHTBLINKER_ID = 0x12344321;

    extern TypeInfo E_LIGHTBLINKER_TYPEINFO;

}

#endif
