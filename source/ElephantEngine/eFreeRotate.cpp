#include <ElephantEngine/eFreeRotate.h>
#include <ElephantBase/Archive.h>

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

    const TypeInfo* eFreeRotate::getType() const
    {
        return &E_FREEROTATE_TYPEINFO;
    }

    eFreeRotate::eFreeRotate()
    : Gadget()
    {}

    eFreeRotate::~eFreeRotate()
    {}


    ////////////////////////////////////////////////////////////////
    // eFreeRotate: cloning the object
    ////////////////////////////////////////////////////////////////

    void eFreeRotate::createFromOtherObject(const eFreeRotate &other)
    {}

    eFreeRotate::eFreeRotate(const eFreeRotate &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eFreeRotate& eFreeRotate::operator = (const eFreeRotate &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eFreeRotate::cloneFromMe() const
    {
        return new eFreeRotate(*this);
    }

}
