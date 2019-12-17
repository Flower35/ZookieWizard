#ifndef H_KAO2AR_WALK
#define H_KAO2AR_WALK

#include <kao2engine/ePathCtrl.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eWalk interface
    // <kao2.005CE1D0> (vptr)
    ////////////////////////////////////////////////////////////////

    class eWalk : public ePathCtrl
    {

        /*** Properties ***/

        protected:

            /*[0x50]*/
            /*(...)*/
            /*[0x84]*/

        /*** Methods ***/

        public:

            eWalk();
            ~eWalk();

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eWalk TypeInfo
    // <kao2.00425680> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_WALK_ID = 0xF0010024;

    extern TypeInfo E_WALK_TYPEINFO;

}

#endif
