#ifndef H_KAO2AR_SPLINEWALK
#define H_KAO2AR_SPLINEWALK

#include <ElephantEngine/eSplineBase.h>

namespace ZookieWizard
{
    class eGroundTest;

    ////////////////////////////////////////////////////////////////
    // eSplineWalk interface
    // <kao2.005CF3D8> (vptr)
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

        private:

            void createFromOtherObject(const eSplineWalk &other);

        public:

            eSplineWalk(const eSplineWalk &other);
            eSplineWalk& operator = (const eSplineWalk &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eSplineWalk TypeInfo
    // <kao2.0043F9A0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SPLINEWALK_ID = 0x3B93177B;

    extern TypeInfo E_SPLINEWALK_TYPEINFO;

}

#endif
