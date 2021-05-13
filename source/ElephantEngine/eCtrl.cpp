#include <ElephantEngine/eCtrl.h>
#include <ElephantBase/Archive.h>

#include <ElephantBase/eAnimate.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCtrl abstract interfaces
    ////////////////////////////////////////////////////////////////

    TypeInfo E_CTRL_ESRP_TYPEINFO
    (
        E_CTRL_ESRP_ID,
        "eCtrl<eSRP>",
        &E_CTRLBASE_TYPEINFO,
        []() -> eObject*
        {
            return nullptr;
        }
    );

    TypeInfo* eCtrl<eSRP>::getType() const
    {
        return &E_CTRL_ESRP_TYPEINFO;
    }

    TypeInfo E_CTRL_EPOINT3_TYPEINFO
    (
        E_CTRL_EPOINT3_ID,
        "eCtrl<ePoint3>",
        &E_CTRLBASE_TYPEINFO,
        []() -> eObject*
        {
            return nullptr;
        }
    );

    TypeInfo* eCtrl<ePoint3>::getType() const
    {
        return &E_CTRL_EPOINT3_TYPEINFO;
    }

    TypeInfo E_CTRL_EQUAT_TYPEINFO
    (
        E_CTRL_EQUAT_ID,
        "eCtrl<eQuat>",
        &E_CTRLBASE_TYPEINFO,
        []() -> eObject*
        {
            return nullptr;
        }
    );

    TypeInfo* eCtrl<eQuat>::getType() const
    {
        return &E_CTRL_EQUAT_TYPEINFO;
    }

    TypeInfo E_CTRL_FLOAT_TYPEINFO
    (
        E_CTRL_FLOAT_ID,
        "eCtrl<float>",
        &E_CTRLBASE_TYPEINFO,
        []() -> eObject*
        {
            return nullptr;
        }
    );

    TypeInfo* eCtrl<float>::getType() const
    {
        return &E_CTRL_FLOAT_TYPEINFO;
    }

    template <typename T>
    eCtrl<T>::eCtrl()
    : eCtrlBase()
    {}

    template <typename T>
    eCtrl<T>::~eCtrl()
    {}


    ////////////////////////////////////////////////////////////////
    // eCtrl: cloning the object
    ////////////////////////////////////////////////////////////////

    template <typename T>
    void eCtrl<T>::createFromOtherObject(const eCtrl<T> &other)
    {}

    template <typename T>
    eCtrl<T>::eCtrl(const eCtrl<T> &other)
    : eCtrlBase(other)
    {
        createFromOtherObject(other);
    }

    template <typename T>
    eCtrl<T>& eCtrl<T>::operator = (const eCtrl<T> &other)
    {
        if ((&other) != this)
        {
            eCtrlBase::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    template <typename T>
    eObject* eCtrl<T>::cloneFromMe() const
    {
        return nullptr;
    }


    ////////////////////////////////////////////////////////////////
    // eCtrl: animation function
    // [[vptr]+0x24] Modify [scale/rotation/position] based on given "eAnimate"
    // <kao2.0043AFD0>: "eCtrl<eSRP>"
    // <kao2.004A5FE0>: "eCtrl<ePoint3>"
    ////////////////////////////////////////////////////////////////
    template <typename T>
    T eCtrl<T>::ctrlGetTransform(T e, eAnimate* anim) const
    {
        if (nullptr != anim)
        {
            ctrlApplyTransform(&e, anim->currentAnimState[0].getTime());
        }

        return e;
    }


    ////////////////////////////////////////////////////////////////
    // Explicit templates
    ////////////////////////////////////////////////////////////////

    template class eCtrl<eSRP>;

    template class eCtrl<ePoint3>;

    template class eCtrl<eQuat>;

    template class eCtrl<float>;

}
