#ifndef H_KAO2AR_PARENTLISTENER
#define H_KAO2AR_PARENTLISTENER

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eParentListener interface
    // <kao2.005D4FE8> (vptr)
    ////////////////////////////////////////////////////////////////

    class eParentListener : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x0010]*/
            /*(...)*/
            /*[0x0744]*/

        /*** Methods ***/

        public:

            eParentListener();
            ~eParentListener();

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eParentListener TypeInfo
    // <kao2.00517410> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_PARENTLISTENER_ID = 0x00002CDF;

    extern TypeInfo E_PARENTLISTENER_TYPEINFO;

}

#endif
