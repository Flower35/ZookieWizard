#include <kao2engine/eCameraCtrl.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCameraCtrl interface
    // <kao2.????????> (constructor)
    // <kao2.????????> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_CAMERACTRL_TYPEINFO
    (
        E_CAMERACTRL_ID,
        "eCameraCtrl",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return nullptr;
        }
    );

    TypeInfo* eCameraCtrl::getType() const
    {
        return &E_CAMERACTRL_TYPEINFO;
    }

    eCameraCtrl::eCameraCtrl()
    : eRefCounter()
    {}

    eCameraCtrl::~eCameraCtrl()
    {}


    ////////////////////////////////////////////////////////////////
    // eCameraCtrl: cloning the object
    ////////////////////////////////////////////////////////////////

    void eCameraCtrl::createFromOtherObject(const eCameraCtrl &other)
    {}

    eCameraCtrl::eCameraCtrl(const eCameraCtrl &other)
    : eRefCounter(other)
    {
        createFromOtherObject(other);
    }

    eCameraCtrl& eCameraCtrl::operator = (const eCameraCtrl &other)
    {
        if ((&other) != this)
        {
            eRefCounter::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eCameraCtrl::cloneFromMe() const
    {
        return nullptr;
    }

}
