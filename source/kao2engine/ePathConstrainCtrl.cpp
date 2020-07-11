#include <kao2engine/ePathConstrainCtrl.h>
#include <kao2ar/Archive.h>

#include <kao2engine/eBezierSplineNode.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePathConstrainCtrl interface
    // <kao2.004A7960> (constructor)
    // <kao2.004A79E0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_PATHCONSTRAINCTRL_TYPEINFO
    (
        E_PATHCONSTRAINCTRL_ID,
        "ePathConstrainCtrl",
        &E_CTRL_EPOINT3_TYPEINFO,
        []() -> eObject*
        {
            return new ePathConstrainCtrl;
        }
    );

    TypeInfo* ePathConstrainCtrl::getType() const
    {
        return &E_PATHCONSTRAINCTRL_TYPEINFO;
    }

    ePathConstrainCtrl::ePathConstrainCtrl()
    : eCtrl<ePoint3>()
    {
        /*[0x08]*/ unknown_08 = nullptr;
        /*[0x0C]*/ unknown_0C = nullptr;
    }

    ePathConstrainCtrl::~ePathConstrainCtrl()
    {
        unknown_0C->decRef();
        unknown_08->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // ePathConstrainCtrl: animation function
    // [[vptr]+0x28] Modify "ePoint3" based on current time
    // <kao2.004A7B00>
    ////////////////////////////////////////////////////////////////
    void ePathConstrainCtrl::ctrlApplyTransform(ePoint3* e, float time) const
    {
        float test;

        unknown_0C->ctrlApplyTransform(&test, time);

        /* (--dsp--) calls <kao2.004A7630> */
        /* object = [0x08] (eBezierSplineNode) */
        /* arg1 = `ePoint3 e`, arg2 = `float test`. */
    }


    ////////////////////////////////////////////////////////////////
    // ePathConstrainCtrl serialization
    // <kao2.004A7B70>
    ////////////////////////////////////////////////////////////////
    void ePathConstrainCtrl::serialize(Archive &ar)
    {
        /* [0x08] eBezierSplineNode */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&unknown_08, &E_BEZIERSPLINENODE_TYPEINFO);

        /* [0x0C] eLeafCtrl<float> */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&unknown_0C, &E_LEAFCTRL_FLOAT_TYPEINFO);
    }


    ////////////////////////////////////////////////////////////////
    // ePathConstrainCtrl: set static keyframes for fun
    ////////////////////////////////////////////////////////////////
    void ePathConstrainCtrl::ctrlSetStaticKeyframe(ePoint3 &new_value, int32_t param)
    {
        /* (...) don't know what to do... */
        return;
    }


    ////////////////////////////////////////////////////////////////
    // ePathConstrainCtrl: clear keyframes for specific animation
    ////////////////////////////////////////////////////////////////
    void ePathConstrainCtrl::ctrlClearKeyframes(int anim_id)
    {
        if (nullptr != unknown_0C)
        {
            unknown_0C->ctrlClearKeyframes(anim_id);
        }

        /* (...) don't know what to do... */
        return;
    }


    ////////////////////////////////////////////////////////////////
    // ePathConstrainCtrl: update specific animation
    ////////////////////////////////////////////////////////////////
    void ePathConstrainCtrl::ctrlAddKeyframe(int anim_id, float new_time, ePoint3 &new_data, int param)
    {
        /* (...) don't know what to do... */
        return;
    }

}
