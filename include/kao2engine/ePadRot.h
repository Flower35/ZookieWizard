#ifndef H_KAO2AR_PADROT
#define H_KAO2AR_PADROT

#include <kao2engine/eLookAtCtrl.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePadRot interface
    // <kao2.005D3018> (vptr)
    ////////////////////////////////////////////////////////////////

    class ePadRot : public eLookAtCtrl
    {

        /*** Properties ***/

        protected:

            /*[0x2C]*/
            /*(...)*/
            /*[0x54]*/

        /*** Methods ***/

        public:

            ePadRot();
            ~ePadRot();

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // ePadRot TypeInfo
    // <kao2.004DBDA0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_PADROT_ID = 0x3C1A9105;

    extern TypeInfo E_PADROT_TYPEINFO;

}

#endif
