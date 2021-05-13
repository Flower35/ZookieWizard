#ifndef H_KAO2AR_FLOATCTRLOBJECT
#define H_KAO2AR_FLOATCTRLOBJECT

#include <ElephantEngine/eFloatObject.h>

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

        private:

            void createFromOtherObject(const eFloatCtrlObject &other);

        public:

            eFloatCtrlObject(const eFloatCtrlObject &other);
            eFloatCtrlObject& operator = (const eFloatCtrlObject &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eFloatCtrlObject TypeInfo
    // <kao2.0043DBF0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_FLOATCTRLOBJECT_ID = 0x3A5612B8;

    extern TypeInfo E_FLOATCTRLOBJECT_TYPEINFO;

}

#endif
