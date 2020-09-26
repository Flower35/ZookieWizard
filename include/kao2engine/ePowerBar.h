#ifndef H_KAO2AR_POWERBAR
#define H_KAO2AR_POWERBAR

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePowerBar interface
    // <kao2.005CFD28> (vptr)
    ////////////////////////////////////////////////////////////////

    class ePowerBar : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x50]*/

        /*** Methods ***/

        public:

            ePowerBar();
            ~ePowerBar();

        private:

            void createFromOtherObject(const ePowerBar &other);

        public:

            ePowerBar(const ePowerBar &other);
            ePowerBar& operator = (const ePowerBar &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // ePowerBar TypeInfo
    // <kao2.00455B70> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_POWERBAR_ID = 0x3C6F95AA;

    extern TypeInfo E_POWERBAR_TYPEINFO;

}

#endif
