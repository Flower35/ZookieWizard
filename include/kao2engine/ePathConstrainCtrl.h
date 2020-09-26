#ifndef H_KAO2AR_PATHCONSTRAINCTRL
#define H_KAO2AR_PATHCONSTRAINCTRL

#include <kao2engine/eCtrl.h>

#include <kao2engine/eLeafCtrl.h>

namespace ZookieWizard
{
    class eBezierSplineNode;

    ////////////////////////////////////////////////////////////////
    // ePathConstrainCtrl interface
    // <kao2.005D1C78> (vptr)
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

        private:

            void createFromOtherObject(const ePathConstrainCtrl &other);

        public:

            ePathConstrainCtrl(const ePathConstrainCtrl &other);
            ePathConstrainCtrl& operator = (const ePathConstrainCtrl &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            /* << eCtrl >> */

            /*[[vptr]+0x28]*/ void ctrlApplyTransform(ePoint3*, float) const override;

            void ctrlSetStaticKeyframe(ePoint3 &new_value, int32_t param) override;

            void ctrlClearKeyframes(int32_t anim_id) override;
            void ctrlSetLoopType(int32_t anim_id, int32_t loop_type, int32_t param) override;
            void ctrlAddKeyframe(int32_t anim_id, float new_time, ePoint3 &new_data, int32_t param) override;
    };


    ////////////////////////////////////////////////////////////////
    // ePathConstrainCtrl TypeInfo
    // <kao2.004A78A0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_PATHCONSTRAINCTRL_ID = 0x9001FFF0;

    extern TypeInfo E_PATHCONSTRAINCTRL_TYPEINFO;

}

#endif
