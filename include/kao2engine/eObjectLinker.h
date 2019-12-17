#ifndef H_KAO2AR_OBJECTLINKER
#define H_KAO2AR_OBJECTLINKER

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eObjectLinker interface
    ////////////////////////////////////////////////////////////////

    class eObjectLinker : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x28]*/

        /*** Methods ***/

        public:

            eObjectLinker();
            ~eObjectLinker();

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eObjectLinker TypeInfo
    // <kao2.00519B50> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_OBJECTLINKER_ID = 0x00002ABF;

    extern TypeInfo E_OBJECTLINKER_TYPEINFO;

}

#endif
