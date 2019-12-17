#ifndef H_KAO2AR_FLOATCTRLOBJECT
#define H_KAO2AR_FLOATCTRLOBJECT

#include <kao2engine/eFloatObject.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFloatCtrlObject interface
    // <kao2.005CF208> (vptr)
    ////////////////////////////////////////////////////////////////

    class eFloatCtrlObject : public eFloatObject
    {

        /*** Properties ***/

        protected:

            /*[0x008C]*/
            /*(...)*/
            /*[0x0160]*/

        /*** Methods ***/

        public:

            eFloatCtrlObject();
            ~eFloatCtrlObject();

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eFloatCtrlObject TypeInfo
    // <kao2.0043DC20> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_FLOATCTRLOBJECT_ID = 0x3A5612B8;

    extern TypeInfo E_FLOATCTRLOBJECT_TYPEINFO;

}

#endif
