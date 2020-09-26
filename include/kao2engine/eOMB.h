#ifndef H_KAO2AR_OMB
#define H_KAO2AR_OMB

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eOMB interface
    // <kao2.005D7378> (vptr)
    ////////////////////////////////////////////////////////////////

    class eOMB : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x0010]*/
            /*(...)*/
            /*[0x02D0]*/

        /*** Methods ***/

        public:

            eOMB();
            ~eOMB();

        private:

            void createFromOtherObject(const eOMB &other);

        public:

            eOMB(const eOMB &other);
            eOMB& operator = (const eOMB &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eOMB TypeInfo
    // <kao2.00568480> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_OMB_ID = 0xFFEEF789;

    extern TypeInfo E_OMB_TYPEINFO;

}

#endif
