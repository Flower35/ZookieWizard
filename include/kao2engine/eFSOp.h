#ifndef H_KAO2AR_FSOP
#define H_KAO2AR_FSOP

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFSOp interface
    ////////////////////////////////////////////////////////////////

    class eFSOp : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x20]*/

        /*** Methods ***/

        public:

            eFSOp();
            ~eFSOp();

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eFSOp TypeInfo
    // <kao2.0055A030> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_FSOP_ID = 0xFF777789;

    extern TypeInfo E_FSOP_TYPEINFO;

}

#endif
