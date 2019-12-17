#ifndef H_KAO2AR_LINKTOOBJECT
#define H_KAO2AR_LINKTOOBJECT

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eLinkToObject interface
    ////////////////////////////////////////////////////////////////

    class eLinkToObject : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x38]*/

        /*** Methods ***/

        public:

            eLinkToObject();
            ~eLinkToObject();

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eLinkToObject TypeInfo
    // <kao2.0044AAE0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_LINKTOOBJECT_ID = 0x3BA2CFFF;

    extern TypeInfo E_LINKTOOBJECT_TYPEINFO;

}

#endif
