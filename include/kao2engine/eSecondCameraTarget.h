#ifndef H_KAO2AR_SECONDCAMERATARGET
#define H_KAO2AR_SECONDCAMERATARGET

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSecondCameraTarget interface
    // <kao2.005D4EF8> (vptr)
    ////////////////////////////////////////////////////////////////

    class eSecondCameraTarget : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x40]*/

        /*** Methods ***/

        public:

            eSecondCameraTarget();
            ~eSecondCameraTarget();

        private:

            void createFromOtherObject(const eSecondCameraTarget &other);

        public:

            eSecondCameraTarget(const eSecondCameraTarget &other);
            eSecondCameraTarget& operator = (const eSecondCameraTarget &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eSecondCameraTarget TypeInfo
    // <kao2.00516E70> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SECONDCAMERATARGET_ID = 0xCA3E7A20;

    extern TypeInfo E_SECONDCAMERATARGET_TYPEINFO;

}

#endif
