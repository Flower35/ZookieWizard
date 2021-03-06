#include <ElephantEngine/eMultiCtrl.h>
#include <ElephantBase/Archive.h>

#include <ElephantBase/eAnimate.h>

#include <ElephantEngine/eSRPCombineCtrl.h>
#include <ElephantEngine/eLeafCtrl.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eMultiCtrl interfaces
    ////////////////////////////////////////////////////////////////

    TypeInfo E_MULTICTRL_ESRP_TYPEINFO
    (
        E_MULTICTRL_ESRP_ID,
        "eMultiCtrl<eSRPCtrl>",
        &E_CTRL_ESRP_TYPEINFO,
        []() -> eObject*
        {
            return new eMultiCtrl<eSRP>;
        }
    );

    const TypeInfo* eMultiCtrl<eSRP>::getType() const
    {
        return &E_MULTICTRL_ESRP_TYPEINFO;
    }

    extern TypeInfo E_MULTICTRL_FLOAT_TYPEINFO
    (
        E_MULTICTRL_FLOAT_ID,
        "eMultiCtrl<eFloatCtrl>",
        &E_CTRL_FLOAT_TYPEINFO,
        []() -> eObject*
        {
            return new eMultiCtrl<float>;
        }
    );

    const TypeInfo* eMultiCtrl<float>::getType() const
    {
        return &E_MULTICTRL_FLOAT_TYPEINFO;
    }

    template <typename T>
    eMultiCtrl<T>::eMultiCtrl()
    : eCtrl<T>()
    {}

    template <typename T>
    eMultiCtrl<T>::~eMultiCtrl()
    {}


    ////////////////////////////////////////////////////////////////
    // eMultiCtrl: cloning the object
    ////////////////////////////////////////////////////////////////

    template <typename T>
    void eMultiCtrl<T>::createFromOtherObject(const eMultiCtrl<T> &other)
    {
        controllers = other.controllers;
    }

    template <typename T>
    eMultiCtrl<T>::eMultiCtrl(const eMultiCtrl<T> &other)
    : eCtrl<T>(other)
    {
        createFromOtherObject(other);
    }

    template <typename T>
    eMultiCtrl<T>& eMultiCtrl<T>::operator = (const eMultiCtrl<T> &other)
    {
        if ((&other) != this)
        {
            eCtrl<T>::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    template <typename T>
    eObject* eMultiCtrl<T>::cloneFromMe() const
    {
        return new eMultiCtrl<T>(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eMultiCtrl: serialization
    // <kao2.????????>
    ////////////////////////////////////////////////////////////////

    void eMultiCtrl<eSRP>::serialize(Archive &ar)
    {
        controllers.serialize(ar, &E_SRPCOMBINECTRL_TYPEINFO);
    }

    void eMultiCtrl<float>::serialize(Archive &ar)
    {
        controllers.serialize(ar, &E_LEAFCTRL_FLOAT_TYPEINFO);
    }


    ////////////////////////////////////////////////////////////////
    // eMultiCtrl: animation function
    // [[vptr]+0x24] Modify [scale/rotation/position] based on given "eAnimate"
    // <kao2.004A19C0>: "eMultiCtrl<eSRPCtrl>"
    // <kao2.004A1FC0>: "eMultiCtrl<eFloatCtrl>"
    ////////////////////////////////////////////////////////////////
    template <typename T>
    T eMultiCtrl<T>::ctrlGetTransform(T e, eAnimate* anim) const
    {
        int32_t id;
        eCtrl<T>* controller;

        if (nullptr != anim)
        {
            id = anim->currentAnimState[0].getAnimId();

            controller = (eCtrl<T>*)controllers.getIthChild(id);

            if (nullptr != controller)
            {
                controller->ctrlApplyTransform(&e, anim->currentAnimState[0].getTime());
            }
        }

        return e;
    }


    ////////////////////////////////////////////////////////////////
    // eMultiCtrl: animation function
    // [[vptr]+0x28] Modify [scale/rotation/position] based on current time
    // <kao2.004A1D20>: "eMultiCtrl<eSRPCtrl>"
    ////////////////////////////////////////////////////////////////
    template <typename T>
    void eMultiCtrl<T>::ctrlApplyTransform(T* e, float time) const
    {
        eCtrl<T>* controller;

        if (nullptr != e)
        {
            if (controllers.getSize() >= 1)
            {
                controller = (eCtrl<T>*)controllers.getIthChild(0);

                if (nullptr != controller)
                {
                    controller->ctrlApplyTransform(e, time);
                }
            }
            else
            {
                (*e) = {0};
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eMultiCtrl: set static keyframes for fun
    ////////////////////////////////////////////////////////////////
    template <typename T>
    void eMultiCtrl<T>::ctrlSetStaticKeyframe(T &new_value, int32_t param)
    {
        int id;
        eCtrl<T>* controller;

        if (0 != param)
        {
            for (id = 0; id < controllers.getSize(); id++)
            {
                controller = (eCtrl<T>*)controllers.getIthChild(id);

                if (nullptr != controller)
                {
                    controller->ctrlSetStaticKeyframe(new_value, param);
                }
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eMultiCtrl: clear keyframes for specific animation
    ////////////////////////////////////////////////////////////////
    template <typename T>
    void eMultiCtrl<T>::ctrlClearKeyframes(int32_t anim_id)
    {
        eCtrl<T>* controller = (eCtrl<T>*)controllers.getIthChild(anim_id);

        if (nullptr != controller)
        {
            controller->ctrlClearKeyframes(anim_id);
        }
    }


    ////////////////////////////////////////////////////////////////
    // eMultiCtrl: set loop type
    ////////////////////////////////////////////////////////////////
    template <typename T>
    void eMultiCtrl<T>::ctrlSetLoopType(int32_t anim_id, int32_t loop_type, int32_t param)
    {
        eCtrl<T>* controller = (eCtrl<T>*)controllers.getIthChild(anim_id);

        if (nullptr != controller)
        {
            controller->ctrlSetLoopType(anim_id, loop_type, param);
        }
    }


    ////////////////////////////////////////////////////////////////
    // eMultiCtrl: update specific animation
    ////////////////////////////////////////////////////////////////
    template <typename T>
    void eMultiCtrl<T>::ctrlAddKeyframe(int32_t anim_id, float new_time, T &new_data, int32_t param)
    {
        if (0 != param)
        {
            eCtrl<T>* controller = (eCtrl<T>*)controllers.getIthChild(anim_id);

            if (nullptr != controller)
            {
                controller->ctrlAddKeyframe(anim_id, new_time, new_data, param);
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eMultiCtrl: set a minimal number of controllers
    // (Kao2 engine requires that the children controllers cannot be `NULL`!)
    ////////////////////////////////////////////////////////////////

    void eMultiCtrl<eSRP>::multiCtrl_SetSize(int32_t new_size)
    {
        eSRPCombineCtrl* dummy_controller;

        for (int i = controllers.getSize(); i < new_size; i++)
        {
            dummy_controller = new eSRPCombineCtrl;

            controllers.appendChild(dummy_controller);
        }
    }

    void eMultiCtrl<float>::multiCtrl_SetSize(int32_t new_size)
    {
        eLeafCtrl<float>* dummy_controller;

        for (int i = controllers.getSize(); i < new_size; i++)
        {
            dummy_controller = new eLeafCtrl<float>;

            controllers.appendChild(dummy_controller);
        }
    }


    ////////////////////////////////////////////////////////////////
    // eMultiCtrl: replace specific controller
    ////////////////////////////////////////////////////////////////

    void eMultiCtrl<eSRP>::multiCtrl_SetTrack(int32_t id, void* new_controller)
    {
        eSRPCombineCtrl* dummy_track = (eSRPCombineCtrl*)new_controller;

        if (nullptr != dummy_track)
        {
            if (false == dummy_track->getType()->checkHierarchy(&E_SRPCOMBINECTRL_TYPEINFO))
            {
                return;
            }

            controllers.setIthChild(id, dummy_track);
        }
    }

    void eMultiCtrl<float>::multiCtrl_SetTrack(int32_t id, void* new_controller)
    {
        eLeafCtrl<float>* dummy_track = (eLeafCtrl<float>*)new_controller;

        if (nullptr != dummy_track)
        {
            if (false == dummy_track->getType()->checkHierarchy(&E_LEAFCTRL_FLOAT_TYPEINFO))
            {
                return;
            }

            controllers.setIthChild(id, dummy_track);
        }
    }


    ////////////////////////////////////////////////////////////////
    // eMultiCtrl: delete specific controller
    ////////////////////////////////////////////////////////////////
    template <typename T>
    void eMultiCtrl<T>::multiCtrl_DeleteTrack(int32_t deleted_id)
    {
        controllers.deleteIthChild(deleted_id);
    }


    ////////////////////////////////////////////////////////////////
    // Explicit templates
    ////////////////////////////////////////////////////////////////

    template class eMultiCtrl<float>;

    template class eMultiCtrl<eSRP>;

}
