#ifndef H_KAO2AR_NEARESTNAVI
#define H_KAO2AR_NEARESTNAVI

#include <ElephantEngine/eNaviCtrl.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eNearestNavi interface
    // <kao2.005CE5D0> (vptr)
    ////////////////////////////////////////////////////////////////

    class eNearestNavi : public eNaviCtrl
    {
        /*** Properties ***/

        protected:

            /*[0x1C]*/
            /*(...)*/
            /*[0x40]*/

        /*** Methods ***/

        public:

            eNearestNavi();
            ~eNearestNavi();

        private:

            void createFromOtherObject(const eNearestNavi &other);

        public:

            eNearestNavi(const eNearestNavi &other);
            eNearestNavi& operator = (const eNearestNavi &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eNearestNavi TypeInfo
    // <kao2.0042A000> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_NEARESTNAVI_ID = 0xFE010131;

    extern TypeInfo E_NEARESTNAVI_TYPEINFO;

}

#endif
