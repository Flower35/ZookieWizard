#ifndef H_KAO2AR_WALK
#define H_KAO2AR_WALK

#include <ElephantEngine/ePathCtrl.h>

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

        private:

            void createFromOtherObject(const eWalk &other);

        public:

            eWalk(const eWalk &other);
            eWalk& operator = (const eWalk &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eWalk TypeInfo
    // <kao2.00425650> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_WALK_ID = 0xF0010024;

    extern TypeInfo E_WALK_TYPEINFO;

}

#endif
