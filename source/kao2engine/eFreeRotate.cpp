#include <kao2engine/eFreeRotate.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFreeRotate interface
    // <kao2.00527F51> (constructor)
    // <kao2.00527FC0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_FREEROTATE_TYPEINFO
    (
        E_FREEROTATE_ID,
        "eFreeRotate",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eFreeRotate;
        }
    );

    TypeInfo* eFreeRotate::getType()
    {
        return &E_FREEROTATE_TYPEINFO;
    }

    eFreeRotate::eFreeRotate()
    : Gadget()
    {}

    eFreeRotate::~eFreeRotate() {}

}
