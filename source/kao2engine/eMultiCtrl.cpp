#include <kao2engine/eMultiCtrl.h>
#include <kao2ar/Archive.h>

#include <kao2ar/eAnimate.h>

#include <kao2engine/eSRPCombineCtrl.h>
#include <kao2engine/eLeafCtrl.h>

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

    TypeInfo* eMultiCtrl<eSRP>::getType() const
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

    TypeInfo* eMultiCtrl<float>::getType() const
    {
        return &E_MULTICTRL_FLOAT_TYPEINFO;
    }


    ////////////////////////////////////////////////////////////////
    // eMultiCtrl: animation function
    // [[vptr]+0x28] Modify [scale/rotation/position] based on given "eAnimate"
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
            id = anim->state[0].getAnimId();

            controller = (eCtrl<T>*)controllers.getIthChild(id);

            if (nullptr != controller)
            {
                controller->ctrlApplyTransform(&e, anim->state[0].getTime());
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
    // eMultiCtrl serialization (and explicit templates)
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

}
