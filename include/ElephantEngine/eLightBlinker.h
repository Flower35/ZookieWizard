#ifndef H_KAO2AR_LIGHTBLINKER
#define H_KAO2AR_LIGHTBLINKER

#include <ElephantEngine/Gadget.h>

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

        private:

            void createFromOtherObject(const eLightBlinker &other);

        public:

            eLightBlinker(const eLightBlinker &other);
            eLightBlinker& operator = (const eLightBlinker &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eLightBlinker TypeInfo
    // <kao2.005293D0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_LIGHTBLINKER_ID = 0x12344321;

    extern TypeInfo E_LIGHTBLINKER_TYPEINFO;

}

#endif
