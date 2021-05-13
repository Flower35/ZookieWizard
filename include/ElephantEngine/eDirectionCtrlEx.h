#ifndef H_KAO2AR_DIRECTIONCTRLEX
#define H_KAO2AR_DIRECTIONCTRLEX

#include <ElephantEngine/eDirectionCtrl.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eDirectionCtrlEx interface
    // <kao2.005D0308> (vptr)
    ////////////////////////////////////////////////////////////////

    class eDirectionCtrlEx : public eDirectionCtrl
    {
        /*** Properties ***/

        protected:

            /*[0x1C]*/

        /*** Methods ***/

        public:

            eDirectionCtrlEx();
            ~eDirectionCtrlEx();

        private:

            void createFromOtherObject(const eDirectionCtrlEx &other);

        public:

            eDirectionCtrlEx(const eDirectionCtrlEx &other);
            eDirectionCtrlEx& operator = (const eDirectionCtrlEx &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eDirectionCtrlEx TypeInfo
    // <kao2.00461920> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_DIRECTIONCTRLEX_ID = 0x00FEBEF1;

    extern TypeInfo E_DIRECTIONCTRLEX_TYPEINFO;

}

#endif
