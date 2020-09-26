#include <kao2engine/eXYZPoint3Ctrl.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eXYZPoint3Ctrl interface
    // <kao2.004A0C69> (constructor)
    // <kao2.004A10A0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_XYZPOINT3CTRL_TYPEINFO
    (
        E_XYZPOINT3CTRL_ID,
        "eXYZPoint3Ctrl",
        &E_CTRL_EPOINT3_TYPEINFO,
        []() -> eObject*
        {
            return new eXYZPoint3Ctrl;
        }
    );

    TypeInfo* eXYZPoint3Ctrl::getType() const
    {
        return &E_XYZPOINT3CTRL_TYPEINFO;
    }

    eXYZPoint3Ctrl::eXYZPoint3Ctrl()
    : eCtrl<ePoint3>()
    {
        /*[0x08]*/ xCtrl = nullptr;
        /*[0x0C]*/ yCtrl = nullptr;
        /*[0x10]*/ zCtrl = nullptr;
    }

    eXYZPoint3Ctrl::~eXYZPoint3Ctrl()
    {
        xCtrl->decRef();
        yCtrl->decRef();
        zCtrl->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // eXYZPoint3Ctrl: cloning the object
    ////////////////////////////////////////////////////////////////

    void eXYZPoint3Ctrl::createFromOtherObject(const eXYZPoint3Ctrl &other)
    {
        xCtrl = other.xCtrl;
        if (nullptr != xCtrl)
        {
            xCtrl->incRef();
        }

        yCtrl = other.yCtrl;
        if (nullptr != yCtrl)
        {
            yCtrl->incRef();
        }

        zCtrl = other.zCtrl;
        if (nullptr != zCtrl)
        {
            zCtrl->incRef();
        }
    }

    eXYZPoint3Ctrl::eXYZPoint3Ctrl(const eXYZPoint3Ctrl &other)
    : eCtrl<ePoint3>(other)
    {
        createFromOtherObject(other);
    }

    eXYZPoint3Ctrl& eXYZPoint3Ctrl::operator = (const eXYZPoint3Ctrl &other)
    {
        if ((&other) != this)
        {
            eCtrl<ePoint3>::operator = (other);

            /****************/

            xCtrl->decRef();
            yCtrl->decRef();
            zCtrl->decRef();

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eXYZPoint3Ctrl::cloneFromMe() const
    {
        return new eXYZPoint3Ctrl(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eXYZPoint3Ctrl: serialization
    // <kao2.004A0D70>
    ////////////////////////////////////////////////////////////////
    void eXYZPoint3Ctrl::serialize(Archive &ar)
    {
        /* X-controller */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&xCtrl, &E_LEAFCTRL_FLOAT_TYPEINFO);

        /* Y-controller */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&yCtrl, &E_LEAFCTRL_FLOAT_TYPEINFO);

        /* Z-controller */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&zCtrl, &E_LEAFCTRL_FLOAT_TYPEINFO);
    }


    ////////////////////////////////////////////////////////////////
    // eXYZPoint3Ctrl: animation function
    // [[vptr]+0x28] Modify "ePoint3" based on current time
    // <kao2.004A0D20>
    ////////////////////////////////////////////////////////////////
    void eXYZPoint3Ctrl::ctrlApplyTransform(ePoint3* e, float time) const
    {
        if (nullptr != e)
        {
            /* Z-controller */

            if (nullptr != zCtrl)
            {
                zCtrl->ctrlApplyTransform(&(e->z), time);
            }
            else
            {
                e->z = 0;
            }

            /* Y-controller */

            if (nullptr != yCtrl)
            {
                yCtrl->ctrlApplyTransform(&(e->y), time);
            }
            else
            {
                e->y = 0;
            }

            /* X-controller */

            if (nullptr != xCtrl)
            {
                xCtrl->ctrlApplyTransform(&(e->x), time);
            }
            else
            {
                e->x = 0;
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eXYZPoint3Ctrl: set static keyframes for fun
    ////////////////////////////////////////////////////////////////
    void eXYZPoint3Ctrl::ctrlSetStaticKeyframe(ePoint3 &new_value, int32_t param)
    {
        eLeafCtrl<float>* dummy_ctrl;

        if (0 != param)
        {
            if (nullptr != xCtrl)
            {
                xCtrl->decRef();
            }

            dummy_ctrl = new eLeafCtrl<float>;
            dummy_ctrl->setDefaultValue(new_value.x);

            xCtrl = dummy_ctrl;
            xCtrl->incRef();

            if (nullptr != yCtrl)
            {
                yCtrl->decRef();
            }

            dummy_ctrl = new eLeafCtrl<float>;
            dummy_ctrl->setDefaultValue(new_value.y);

            yCtrl = dummy_ctrl;
            yCtrl->incRef();

            if (nullptr != zCtrl)
            {
                zCtrl->decRef();
            }

            dummy_ctrl = new eLeafCtrl<float>;
            dummy_ctrl->setDefaultValue(new_value.z);

            zCtrl = dummy_ctrl;
            zCtrl->incRef();
        }
    }


    ////////////////////////////////////////////////////////////////
    // eXYZPoint3Ctrl: clear keyframes for specific animation
    ////////////////////////////////////////////////////////////////
    void eXYZPoint3Ctrl::ctrlClearKeyframes(int32_t anim_id)
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
    // eXYZPoint3Ctrl: set loop type
    ////////////////////////////////////////////////////////////////
    void eXYZPoint3Ctrl::ctrlSetLoopType(int32_t anim_id, int32_t loop_type, int32_t param)
    {
        if (0 != param)
        {
            if (nullptr != xCtrl)
            {
                xCtrl->ctrlSetLoopType(anim_id, loop_type, 0x01);
            }

            if (nullptr != yCtrl)
            {
                yCtrl->ctrlSetLoopType(anim_id, loop_type, 0x01);
            }

            if (nullptr != zCtrl)
            {
                zCtrl->ctrlSetLoopType(anim_id, loop_type, 0x01);
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eXYZPoint3Ctrl: update specific animation
    ////////////////////////////////////////////////////////////////
    void eXYZPoint3Ctrl::ctrlAddKeyframe(int32_t anim_id, float new_time, ePoint3 &new_data, int32_t param)
    {
        eLeafCtrl<float>* dummy_ctrl;

        if (0 != param)
        {
            if (nullptr == xCtrl)
            {
                dummy_ctrl = new eLeafCtrl<float>;
                dummy_ctrl->setDefaultValue(new_data.x);

                xCtrl = dummy_ctrl;
                xCtrl->incRef();
            }

            xCtrl->ctrlAddKeyframe(anim_id, new_time, new_data.x, 0x01);

            if (nullptr == yCtrl)
            {
                dummy_ctrl = new eLeafCtrl<float>;
                dummy_ctrl->setDefaultValue(new_data.y);

                yCtrl = dummy_ctrl;
                yCtrl->incRef();
            }

            yCtrl->ctrlAddKeyframe(anim_id, new_time, new_data.y, 0x01);

            if (nullptr == zCtrl)
            {
                dummy_ctrl = new eLeafCtrl<float>;
                dummy_ctrl->setDefaultValue(new_data.z);

                zCtrl = dummy_ctrl;
                zCtrl->incRef();
            }

            zCtrl->ctrlAddKeyframe(anim_id, new_time, new_data.z, 0x01);
        }
    }

}
