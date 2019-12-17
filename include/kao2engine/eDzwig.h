#ifndef H_KAO2AR_DZWIG
#define H_KAO2AR_DZWIG

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eDzwig interface
    // <kao2.005CFA98> (vptr)
    ////////////////////////////////////////////////////////////////

    class eDzwig : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x7C]*/

        /*** Methods ***/

        public:

            eDzwig();
            ~eDzwig();

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eDzwig TypeInfo
    // <kao2.0044EF20> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_DZWIG_ID = 0x3BB66553;

    extern TypeInfo E_DZWIG_TYPEINFO;

}

#endif
