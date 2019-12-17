#ifndef H_KAO2AR_DOUBLECAMERATARGET
#define H_KAO2AR_DOUBLECAMERATARGET

#include <kao2engine/eCameraTarget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eDoubleCameraTarget interface
    // <kao2.005D4E50> (vptr)
    ////////////////////////////////////////////////////////////////

    class eDoubleCameraTarget : public eCameraTarget
    {

        /*** Properties ***/

        protected:

            /*[0x01F8]*/
            /*(...)*/
            /*[0x021C]*/

        /*** Methods ***/

        public:

            eDoubleCameraTarget();
            ~eDoubleCameraTarget();

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eDoubleCameraTarget TypeInfo
    // <kao2.00516720> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_DOUBLECAMERATARGET_ID = 0xCA3E7A12;

    extern TypeInfo E_DOUBLECAMERATARGET_TYPEINFO;

}

#endif
