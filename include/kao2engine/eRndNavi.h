#ifndef H_KAO2AR_RNDNAVI
#define H_KAO2AR_RNDNAVI

#include <kao2engine/eNaviCtrl.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eRndNavi interface
    // <kao2.005CE4C0> (vptr)
    ////////////////////////////////////////////////////////////////

    class eRndNavi : public eNaviCtrl
    {

        /*** Properties ***/

        protected:

            /*[0x1C]*/
            /*(...)*/
            /*[0x38]*/

        /*** Methods ***/

        public:

            eRndNavi();
            ~eRndNavi();

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eRndNavi TypeInfo
    // <kao2.00429DC0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_RNDNAVI_ID = 0xFE010030;

    extern TypeInfo E_RNDNAVI_TYPEINFO;

}

#endif
