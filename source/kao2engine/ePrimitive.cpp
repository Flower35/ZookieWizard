#include <kao2engine/ePrimitive.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePrimitive interface
    // <kao2.????????> (constructor)
    // <kao2.????????> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_PRIMITIVE_TYPEINFO
    (
        E_PRIMITIVE_ID,
        "ePrimitive",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return nullptr;
        }
    );

    TypeInfo* ePrimitive::getType() const
    {
        return &E_PRIMITIVE_TYPEINFO;
    }

    ePrimitive::ePrimitive()
    : eRefCounter()
    {}

    ePrimitive::~ePrimitive()
    {}


    ////////////////////////////////////////////////////////////////
    // ePrimitive: cloning the object
    ////////////////////////////////////////////////////////////////

    void ePrimitive::createFromOtherObject(const ePrimitive &other)
    {}

    ePrimitive::ePrimitive(const ePrimitive &other)
    : eRefCounter(other)
    {
        createFromOtherObject(other);
    }

    ePrimitive& ePrimitive::operator = (const ePrimitive &other)
    {
        if ((&other) != this)
        {
            eRefCounter::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* ePrimitive::cloneFromMe() const
    {
        return nullptr;
    }

}
