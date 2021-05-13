#ifndef H_KAO2AR_CAMERATARGET
#define H_KAO2AR_CAMERATARGET

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCameraTarget interface
    // <kao2.005D4AD0> (vptr)
    ////////////////////////////////////////////////////////////////

    class eCameraTarget : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x0010]*/
            /*(...)*/
            /*[0x01F4]*/

        /*** Methods ***/

        public:

            eCameraTarget();
            ~eCameraTarget();

        private:

            void createFromOtherObject(const eCameraTarget &other);

        public:

            eCameraTarget(const eCameraTarget &other);
            eCameraTarget& operator = (const eCameraTarget &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eCameraTarget TypeInfo
    // <kao2.00510A40> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_CAMERATARGET_ID = 0xCA3E7A10;

    extern TypeInfo E_CAMERATARGET_TYPEINFO;

}

#endif
