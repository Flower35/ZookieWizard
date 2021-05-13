#ifndef H_KAO2AR_HITFORCECTRL
#define H_KAO2AR_HITFORCECTRL

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eHitForceCtrl interface
    // <kao2.005CFB18> (vptr)
    ////////////////////////////////////////////////////////////////

    class eHitForceCtrl : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x3C]*/

        /*** Methods ***/

        public:

            eHitForceCtrl();
            ~eHitForceCtrl();

        private:

            void createFromOtherObject(const eHitForceCtrl &other);

        public:

            eHitForceCtrl(const eHitForceCtrl &other);
            eHitForceCtrl& operator = (const eHitForceCtrl &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eHitForceCtrl TypeInfo
    // <kao2.0044FA60> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_HITFORCECTRL_ID = 0x3D33D5B7;

    extern TypeInfo E_HITFORCECTRL_TYPEINFO;

}

#endif
