#ifndef H_KAO2AR_STRAFETARGET
#define H_KAO2AR_STRAFETARGET

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eStrafeTarget interface
    // <kao2.005D3660> (vptr)
    ////////////////////////////////////////////////////////////////

    class eStrafeTarget : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x24]*/

        /*** Methods ***/

        public:

            eStrafeTarget();
            ~eStrafeTarget();

        private:

            void createFromOtherObject(const eStrafeTarget &other);

        public:

            eStrafeTarget(const eStrafeTarget &other);
            eStrafeTarget& operator = (const eStrafeTarget &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eStrafeTarget TypeInfo
    // <kao2.004E8F90> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_STRAFETARGET_ID = 0x0BA2DFF2;

    extern TypeInfo E_STRAFETARGET_TYPEINFO;

}

#endif
