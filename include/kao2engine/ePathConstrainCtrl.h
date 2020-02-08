#ifndef H_KAO2AR_PATHCONSTRAINCTRL
#define H_KAO2AR_PATHCONSTRAINCTRL

#include <kao2engine/eCtrl.h>

#include <kao2engine/eLeafCtrl.h>

namespace ZookieWizard
{
    class eBezierSplineNode;

    ////////////////////////////////////////////////////////////////
    // ePathConstrainCtrl interface
    ////////////////////////////////////////////////////////////////

    class ePathConstrainCtrl : public eCtrl<ePoint3>
    {

        /*** Properties ***/

        protected:

            /*[0x08]*/ eBezierSplineNode* unknown_08;
            /*[0x0C]*/ eLeafCtrl<float>* unknown_0C;

        /*** Methods ***/

        public:

            ePathConstrainCtrl();
            ~ePathConstrainCtrl();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            /*[[vptr]+0x28]*/ void ctrlApplyTransform(ePoint3*, float) const override;
    };


    ////////////////////////////////////////////////////////////////
    // ePathConstrainCtrl TypeInfo
    // <kao2.004A78D0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_PATHCONSTRAINCTRL_ID = 0x9001FFF0;

    extern TypeInfo E_PATHCONSTRAINCTRL_TYPEINFO;

}

#endif
