#ifndef H_KAO2AR_ENUMNAVI
#define H_KAO2AR_ENUMNAVI

#include <ElephantEngine/eNaviCtrl.h>

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

        private:

            void createFromOtherObject(const eEnumNavi &other);

        public:

            eEnumNavi(const eEnumNavi &other);
            eEnumNavi& operator = (const eEnumNavi &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eEnumNavi TypeInfo
    // <kao2.00429F30> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_ENUMNAVI_ID = 0xFEC10030;

    extern TypeInfo E_ENUMNAVI_TYPEINFO;

}

#endif
