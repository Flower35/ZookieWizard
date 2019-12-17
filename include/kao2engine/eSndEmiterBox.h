#ifndef H_KAO2AR_SNDEMITERBOX
#define H_KAO2AR_SNDEMITERBOX

#include <kao2engine/eSndEmiter.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSndEmiterBox interface
    // <kao2.005E1130> (vptr)
    ////////////////////////////////////////////////////////////////

    class eSndEmiterBox : public eSndEmiter
    {

        /*** Properties ***/

        protected:

            /*[0xB8]*/
            /*(...)*/

            /*[0xC8]*/ float unknown_C8;
            /*[0xCC]*/ float unknown_CC;
            /*[0xD0]*/ float unknown_D0;

            /*[0xD4]*/ float unknown_D4;
            /*[0xD8]*/ float unknown_D8;
            /*[0xDC]*/ float unknown_DC;

        /*** Methods ***/

        public:

            eSndEmiterBox();
            ~eSndEmiterBox();

            void serialize(Archive &ar) override;
            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eSndEmiterBox TypeInfo
    // <kao2.005AF040> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SNDEMITERBOX_ID = 0x09994524;

    extern TypeInfo E_SNDEMITERBOX_TYPEINFO;

}

#endif
