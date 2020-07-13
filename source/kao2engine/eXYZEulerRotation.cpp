#include <kao2engine/eXYZEulerRotation.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eXYZEulerRotation interface
    // <kao2.004A11F9> (constructor)
    // <kao2.004A1600> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_XYZEULERROTATION_TYPEINFO
    (
        E_XYZEULERROTATION_ID,
        "eXYZEulerRotation",
        &E_CTRL_EQUAT_TYPEINFO,
        []() -> eObject*
        {
            return new eXYZEulerRotation;
        }
    );

    TypeInfo* eXYZEulerRotation::getType() const
    {
        return &E_XYZEULERROTATION_TYPEINFO;
    }

    eXYZEulerRotation::eXYZEulerRotation()
    : eCtrl<eQuat>()
    {
        /*[0x08]*/ xCtrl = nullptr;
        /*[0x0C]*/ yCtrl = nullptr;
        /*[0x10]*/ zCtrl = nullptr;
        /*[0x14]*/ unknown_14 = 0x24;
    }

    eXYZEulerRotation::~eXYZEulerRotation()
    {
        xCtrl->decRef();
        yCtrl->decRef();
        zCtrl->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // eXYZEulerRotation: animation function
    // [[vptr]+0x28] Modify "eQuat" based on current time
    // <kao2.0049FE70>
    ////////////////////////////////////////////////////////////////
    void eXYZEulerRotation::ctrlApplyTransform(eQuat* e, float time) const
    {
        float x, y, z;

        if (nullptr != e)
        {
            /* Z-controller */

            if (nullptr != zCtrl)
            {
                zCtrl->ctrlApplyTransform(&(z), time);
            }
            else
            {
                z = 0;
            }

            /* Y-controller */

            if (nullptr != yCtrl)
            {
                yCtrl->ctrlApplyTransform(&(y), time);
            }
            else
            {
                y = 0;
            }

            /* X-controller */

            if (nullptr != xCtrl)
            {
                xCtrl->ctrlApplyTransform(&(x), time);
            }
            else
            {
                x = 0;
            }

            /* Euler rotation to Quaternion conversion */

            e->fromEulerAngles(true, x, y, z);
        }
    }


    ////////////////////////////////////////////////////////////////
    // eXYZEulerRotation serialization
    // <kao2.004A1370>
    ////////////////////////////////////////////////////////////////
    void eXYZEulerRotation::serialize(Archive &ar)
    {
        /* X-controller */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&xCtrl, &E_LEAFCTRL_FLOAT_TYPEINFO);

        /* Y-controller */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&yCtrl, &E_LEAFCTRL_FLOAT_TYPEINFO);

        /* Z-controller */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&zCtrl, &E_LEAFCTRL_FLOAT_TYPEINFO);

        /* [0x14] unknown */
        ar.readOrWrite(&unknown_14, 0x04);
    }


    ////////////////////////////////////////////////////////////////
    // eXYZEulerRotation: set static keyframes for fun
    ////////////////////////////////////////////////////////////////
    void eXYZEulerRotation::ctrlSetStaticKeyframe(eQuat &new_value, int32_t param)
    {
        eLeafCtrl<float>* dummy_ctrl;
        float angles[3];

        if (0x01 == param)
        {
            new_value.toEulerAngles(false, angles[0], angles[1], angles[2]);

            if (nullptr != xCtrl)
            {
                xCtrl->decRef();
            }

            dummy_ctrl = new eLeafCtrl<float>;
            dummy_ctrl->setDefaultValue(angles[0]);

            xCtrl = dummy_ctrl;
            xCtrl->incRef();

            if (nullptr != yCtrl)
            {
                yCtrl->decRef();
            }

            dummy_ctrl = new eLeafCtrl<float>;
            dummy_ctrl->setDefaultValue(angles[1]);

            yCtrl = dummy_ctrl;
            yCtrl->incRef();


            if (nullptr != zCtrl)
            {
                zCtrl->decRef();
            }

            dummy_ctrl = new eLeafCtrl<float>;
            dummy_ctrl->setDefaultValue(angles[2]);

            zCtrl = dummy_ctrl;
            zCtrl->incRef();
        }
    }


    ////////////////////////////////////////////////////////////////
    // eXYZEulerRotation: clear keyframes for specific animation
    ////////////////////////////////////////////////////////////////
    void eXYZEulerRotation::ctrlClearKeyframes(int anim_id)
    {
        if (nullptr != xCtrl)
        {
            xCtrl->ctrlClearKeyframes(anim_id);
        }

        if (nullptr != yCtrl)
        {
            yCtrl->ctrlClearKeyframes(anim_id);
        }

        if (nullptr != zCtrl)
        {
            zCtrl->ctrlClearKeyframes(anim_id);
        }
    }


    ////////////////////////////////////////////////////////////////
    // eXYZEulerRotation: update specific animation
    ////////////////////////////////////////////////////////////////
    void eXYZEulerRotation::ctrlAddKeyframe(int anim_id, float new_time, eQuat &new_data, int param)
    {
        eLeafCtrl<float>* dummy_ctrl;
        float angles[3];

        if (0 != param)
        {
            new_data.toEulerAngles(false, angles[0], angles[1], angles[2]);

            if (nullptr == xCtrl)
            {
                dummy_ctrl = new eLeafCtrl<float>;
                dummy_ctrl->setDefaultValue(angles[0]);

                xCtrl = dummy_ctrl;
                xCtrl->incRef();
            }

            xCtrl->ctrlAddKeyframe(anim_id, new_time, angles[0], 0x01);

            if (nullptr == yCtrl)
            {
                dummy_ctrl = new eLeafCtrl<float>;
                dummy_ctrl->setDefaultValue(angles[1]);

                yCtrl = dummy_ctrl;
                yCtrl->incRef();
            }

            yCtrl->ctrlAddKeyframe(anim_id, new_time, angles[1], 0x01);

            if (nullptr == zCtrl)
            {
                dummy_ctrl = new eLeafCtrl<float>;
                dummy_ctrl->setDefaultValue(angles[2]);

                zCtrl = dummy_ctrl;
                zCtrl->incRef();
            }

            zCtrl->ctrlAddKeyframe(anim_id, new_time, angles[2], 0x01);
        }
    }

}
