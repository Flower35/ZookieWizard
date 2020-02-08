#ifndef H_KAO2AR_SND
#define H_KAO2AR_SND

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSnd interface
    ////////////////////////////////////////////////////////////////

    class eSnd : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x68]*/

        /*** Methods ***/

        public:

            eSnd();
            ~eSnd();

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eSnd TypeInfo
    // <kao2.00439D80> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SND_ID = 0x39D5A028;

    extern TypeInfo E_SND_TYPEINFO;

}

#endif
