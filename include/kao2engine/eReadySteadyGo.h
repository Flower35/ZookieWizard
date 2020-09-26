#ifndef H_KAO2AR_READYSTEADYGO
#define H_KAO2AR_READYSTEADYGO

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eReadySteadyGo interface
    // <kao2.005D00A8> (vptr)
    ////////////////////////////////////////////////////////////////

    class eReadySteadyGo : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x54]*/

        /*** Methods ***/

        public:

            eReadySteadyGo();
            ~eReadySteadyGo();

        private:

            void createFromOtherObject(const eReadySteadyGo &other);

        public:

            eReadySteadyGo(const eReadySteadyGo &other);
            eReadySteadyGo& operator = (const eReadySteadyGo &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eReadySteadyGo TypeInfo
    // <kao2.0045BE10> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_READYSTEADYGO_ID = 0x3B97B235;

    extern TypeInfo E_READYSTEADYGO_TYPEINFO;

}

#endif
