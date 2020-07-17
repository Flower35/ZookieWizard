#include <kao2engine/eSRPCombineCtrl.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSRPCombineCtrl interface
    // <kao2.004A1759> (constructor)
    // <kao2.0044B7D0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SRPCOMBINECTRL_TYPEINFO
    (
        E_SRPCOMBINECTRL_ID,
        "eSRPCombineCtrl",
        &E_CTRL_ESRP_TYPEINFO,
        []() -> eObject*
        {
            return new eSRPCombineCtrl;
        }
    );

    TypeInfo* eSRPCombineCtrl::getType() const
    {
        return &E_SRPCOMBINECTRL_TYPEINFO;
    }

    eSRPCombineCtrl::eSRPCombineCtrl()
    : eCtrl<eSRP>()
    {
        /*[0x08]*/ sclCtrl = nullptr;
        /*[0x0C]*/ rotCtrl = nullptr;
        /*[0x10]*/ posCtrl = nullptr;
    }

    eSRPCombineCtrl::~eSRPCombineCtrl()
    {
        sclCtrl->decRef();
        rotCtrl->decRef();
        posCtrl->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // eSRPCombineCtrl: animation function
    // [[vptr]+0x28] Modify "eSRP" based on current time
    // <kao2.0044B480>
    ////////////////////////////////////////////////////////////////
    void eSRPCombineCtrl::ctrlApplyTransform(eSRP* e, float time) const
    {
        if (nullptr != e)
        {
            /* Position controller */

            if (nullptr != posCtrl)
            {
                posCtrl->ctrlApplyTransform(&(e->pos), time);
            }
            else
            {
                e->pos = {0, 0, 0};
            }

            /* Rotation controller */

            if (nullptr != rotCtrl)
            {
                rotCtrl->ctrlApplyTransform(&(e->rot), time);
            }
            else
            {
                e->rot = {0, 0, 0, 1.0f};
            }

            /* Scale controller */

            if (nullptr != sclCtrl)
            {
                sclCtrl->ctrlApplyTransform(&(e->scale), time);
            }
            else
            {
                e->scale = 1.0f;
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eSRPCombineCtrl serialization
    // <kao2.0044B550>
    ////////////////////////////////////////////////////////////////
    void eSRPCombineCtrl::serialize(Archive &ar)
    {
        /* Scale conroller */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&sclCtrl, &E_LEAFCTRL_FLOAT_TYPEINFO);

        /* Rotation controller */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&rotCtrl, &E_CTRL_EQUAT_TYPEINFO);

        /* Position controller */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&posCtrl, &E_CTRL_EPOINT3_TYPEINFO);
    }


    ////////////////////////////////////////////////////////////////
    // eSRPCombineCtrl: set static keyframes for fun
    ////////////////////////////////////////////////////////////////
    void eSRPCombineCtrl::ctrlSetStaticKeyframe(eSRP &new_value, int32_t param)
    {
        eLeafCtrl<float>* dummy_scl_ctrl;
        eLeafCtrl<eQuat>* dummy_rot_ctrl;
        eLeafCtrl<ePoint3>* dummy_pos_ctrl;

        if ((0x01 << 0) & param)
        {
            if (nullptr != sclCtrl)
            {
                sclCtrl->decRef();
            }

            dummy_scl_ctrl = new eLeafCtrl<float>;
            dummy_scl_ctrl->setDefaultValue(new_value.scale);

            sclCtrl = dummy_scl_ctrl;
            sclCtrl->incRef();
        }

        if ((0x01 << 1) & param)
        {
            if (nullptr != rotCtrl)
            {
                rotCtrl->decRef();
            }

            dummy_rot_ctrl = new eLeafCtrl<eQuat>;
            dummy_rot_ctrl->setDefaultValue(new_value.rot);

            rotCtrl = dummy_rot_ctrl;
            rotCtrl->incRef();
        }

        if ((0x01 << 2) & param)
        {
            if (nullptr != posCtrl)
            {
                posCtrl->decRef();
            }

            dummy_pos_ctrl = new eLeafCtrl<ePoint3>;
            dummy_pos_ctrl->setDefaultValue(new_value.pos);

            posCtrl = dummy_pos_ctrl;
            posCtrl->incRef();
        }
    }


    ////////////////////////////////////////////////////////////////
    // eSRPCombineCtrl: set loop type
    ////////////////////////////////////////////////////////////////
    void eSRPCombineCtrl::ctrlSetLoopType(int32_t anim_id, int32_t loop_type, int32_t param)
    {
        if ((0x01 << 0) & param)
        {
            if (nullptr != sclCtrl)
            {
                sclCtrl->ctrlSetLoopType(anim_id, loop_type, 0x01);
            }
        }

        if ((0x01 << 1) & param)
        {
            if (nullptr != rotCtrl)
            {
                rotCtrl->ctrlSetLoopType(anim_id, loop_type, 0x01);
            }
        }

        if ((0x01 << 2) & param)
        {
            if (nullptr != posCtrl)
            {
                posCtrl->ctrlSetLoopType(anim_id, loop_type, 0x01);
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eSRPCombineCtrl: clear keyframes for specific animation
    ////////////////////////////////////////////////////////////////
    void eSRPCombineCtrl::ctrlClearKeyframes(int32_t anim_id)
    {
        if (nullptr != sclCtrl)
        {
            sclCtrl->ctrlClearKeyframes(anim_id);
        }

        if (nullptr != rotCtrl)
        {
            rotCtrl->ctrlClearKeyframes(anim_id);
        }

        if (nullptr != posCtrl)
        {
            posCtrl->ctrlClearKeyframes(anim_id);
        }
    }


    ////////////////////////////////////////////////////////////////
    // eSRPCombineCtrl: update specific animation
    ////////////////////////////////////////////////////////////////
    void eSRPCombineCtrl::ctrlAddKeyframe(int32_t anim_id, float new_time, eSRP &new_data, int32_t param)
    {
        eLeafCtrl<float>* dummy_scl_ctrl;
        eLeafCtrl<eQuat>* dummy_rot_ctrl;
        eLeafCtrl<ePoint3>* dummy_pos_ctrl;

        if ((0x01 << 0) & param)
        {
            if (nullptr == sclCtrl)
            {
                dummy_scl_ctrl = new eLeafCtrl<float>;
                dummy_scl_ctrl->setDefaultValue(new_data.scale);

                sclCtrl = dummy_scl_ctrl;
                sclCtrl->incRef();
            }

            sclCtrl->ctrlAddKeyframe(anim_id, new_time, new_data.scale, 0x01);
        }

        if ((0x01 << 1) & param)
        {
            if (nullptr == rotCtrl)
            {
                dummy_rot_ctrl = new eLeafCtrl<eQuat>;
                dummy_rot_ctrl->setDefaultValue(new_data.rot);

                rotCtrl = dummy_rot_ctrl;
                rotCtrl->incRef();
            }

            rotCtrl->ctrlAddKeyframe(anim_id, new_time, new_data.rot, 0x01);
        }

        if ((0x01 << 2) & param)
        {
            if (nullptr == posCtrl)
            {
                dummy_pos_ctrl = new eLeafCtrl<ePoint3>;
                dummy_pos_ctrl->setDefaultValue(new_data.pos);

                posCtrl = dummy_pos_ctrl;
                posCtrl->incRef();
            }

            posCtrl->ctrlAddKeyframe(anim_id, new_time, new_data.pos, 0x01);
        }
    }

}
