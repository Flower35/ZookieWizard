#ifndef H_KAO2AR_SPLINEWALK
#define H_KAO2AR_SPLINEWALK

#include <kao2engine/eSplineBase.h>

namespace ZookieWizard
{
    class eGroundTest;

    ////////////////////////////////////////////////////////////////
    // eSplineWalk interface
    ////////////////////////////////////////////////////////////////

    class eSplineWalk : public eSplineBase
    {

        /*** Properties ***/

        protected:

            /*[0x28]*/ eGroundTest* unknown_28;
            /*(...)*/
            /*[0x84]*/

        /*** Methods ***/

        public:

            eSplineWalk();
            ~eSplineWalk();

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eSplineWalk TypeInfo
    // <kao2.0043F9D0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SPLINEWALK_ID = 0x3B93177B;

    extern TypeInfo E_SPLINEWALK_TYPEINFO;

}

#endif
