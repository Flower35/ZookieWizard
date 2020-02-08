#ifndef H_KAO2AR_ENUMNAVI
#define H_KAO2AR_ENUMNAVI

#include <kao2engine/eNaviCtrl.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eEnumNavi interface
    // <kao2.005CE578> (vptr)
    ////////////////////////////////////////////////////////////////

    class eEnumNavi : public eNaviCtrl
    {

        /*** Properties ***/

        protected:

            /*[0x1C]*/
            /*(...)*/
            /*[0x3C]*/

        /*** Methods ***/

        public:

            eEnumNavi();
            ~eEnumNavi();

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eEnumNavi TypeInfo
    // <kao2.00429F60> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_ENUMNAVI_ID = 0xFEC10030;

    extern TypeInfo E_ENUMNAVI_TYPEINFO;

}

#endif
