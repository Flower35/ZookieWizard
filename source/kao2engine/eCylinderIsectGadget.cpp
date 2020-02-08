#include <kao2engine/eCylinderIsectGadget.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCylinderIsectGadget interface
    // <kao2.00521411> (constructor)
    // <kao2.00521490> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_CYLINDERISECTGADGET_TYPEINFO
    (
        E_CYLINDERISECTGADGET_ID,
        "eCylinderIsectGadget",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eCylinderIsectGadget;
        }
    );

    TypeInfo* eCylinderIsectGadget::getType() const
    {
        return &E_CYLINDERISECTGADGET_TYPEINFO;
    }

    eCylinderIsectGadget::eCylinderIsectGadget()
    : Gadget()
    {}

    eCylinderIsectGadget::~eCylinderIsectGadget() {}

}
