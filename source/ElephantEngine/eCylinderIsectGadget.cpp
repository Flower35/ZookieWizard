#include <ElephantEngine/eCylinderIsectGadget.h>
#include <ElephantBase/Archive.h>

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

    const TypeInfo* eCylinderIsectGadget::getType() const
    {
        return &E_CYLINDERISECTGADGET_TYPEINFO;
    }

    eCylinderIsectGadget::eCylinderIsectGadget()
    : Gadget()
    {}

    eCylinderIsectGadget::~eCylinderIsectGadget()
    {}


    ////////////////////////////////////////////////////////////////
    // eCylinderIsectGadget: cloning the object
    ////////////////////////////////////////////////////////////////

    void eCylinderIsectGadget::createFromOtherObject(const eCylinderIsectGadget &other)
    {}

    eCylinderIsectGadget::eCylinderIsectGadget(const eCylinderIsectGadget &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eCylinderIsectGadget& eCylinderIsectGadget::operator = (const eCylinderIsectGadget &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eCylinderIsectGadget::cloneFromMe() const
    {
        return new eCylinderIsectGadget(*this);
    }

}
