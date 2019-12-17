#ifndef H_KAO2AR_HEROPARENT
#define H_KAO2AR_HEROPARENT

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eHeroParent interface
    // <kao2.005D5038> (vptr)
    ////////////////////////////////////////////////////////////////

    class eHeroParent : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x54]*/

        /*** Methods ***/

        public:

            eHeroParent();
            ~eHeroParent();

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eHeroParent TypeInfo
    // <kao2.00518140> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_HEROPARENT_ID = 0x00002CDE;

    extern TypeInfo E_HEROPARENT_TYPEINFO;

}

#endif
