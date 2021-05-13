#include <ElephantEngine/eCtrlBase.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCtrlBase interface
    // <kao2.004A00E0> (constructor)
    // <kao2.004A0150> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_CTRLBASE_TYPEINFO
    (
        E_CTRLBASE_ID,
        "eCtrlBase",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return new eCtrlBase;
        }
    );
    TypeInfo* eCtrlBase::getType() const
    {
        return &E_CTRLBASE_TYPEINFO;
    }

    eCtrlBase::eCtrlBase()
    : eRefCounter()
    {}

    eCtrlBase::~eCtrlBase()
    {}


    ////////////////////////////////////////////////////////////////
    // eCtrlBase: cloning the object
    ////////////////////////////////////////////////////////////////

    void eCtrlBase::createFromOtherObject(const eCtrlBase &other)
    {}

    eCtrlBase::eCtrlBase(const eCtrlBase &other)
    : eRefCounter(other)
    {
        createFromOtherObject(other);
    }

    eCtrlBase& eCtrlBase::operator = (const eCtrlBase &other)
    {
        if ((&other) != this)
        {
            eRefCounter::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eCtrlBase::cloneFromMe() const
    {
        return new eCtrlBase(*this);
    }

}
