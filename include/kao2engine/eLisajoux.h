#ifndef H_KAO2AR_LISAJOUX
#define H_KAO2AR_LISAJOUX

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eLisajoux interface
    ////////////////////////////////////////////////////////////////

    class eLisajoux : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x50]*/

        /*** Methods ***/

        public:

            eLisajoux();
            ~eLisajoux();

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eLisajoux TypeInfo
    // <kao2.00565210> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_LISAJOUX_ID = 0x3BEBD8FA;

    extern TypeInfo E_LISAJOUX_TYPEINFO;

}

#endif
