#ifndef H_KAO2AR_CINEMAMODE
#define H_KAO2AR_CINEMAMODE

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCinemaMode interface
    // <kao2.005CF1A8> (vptr)
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

        private:

            void createFromOtherObject(const eCinemaMode &other);

        public:

            eCinemaMode(const eCinemaMode &other);
            eCinemaMode& operator = (const eCinemaMode &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eCinemaMode TypeInfo
    // <kao2.0043BD60> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_CINEMAMODE_ID = 0x394321F4;

    extern TypeInfo E_CINEMAMODE_TYPEINFO;

}

#endif
