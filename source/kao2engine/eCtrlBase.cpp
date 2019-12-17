#include <kao2engine/eCtrlBase.h>
#include <kao2ar/Archive.h>

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
    TypeInfo* eCtrlBase::getType()
    {
        return &E_CTRLBASE_TYPEINFO;
    }

    eCtrlBase::eCtrlBase()
    : eRefCounter()
    {}

    eCtrlBase::~eCtrlBase() {}

}
