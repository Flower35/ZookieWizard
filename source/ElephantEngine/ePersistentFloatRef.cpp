#include <ElephantEngine/ePersistentFloatRef.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePersistentFloatRef interface
    // <kao2.005284D0> (constructor)
    // <kao2.00528540> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_PERSISTENTFLOATREF_TYPEINFO
    (
        E_PERSISTENTFLOATREF_ID,
        "ePersistentFloatRef",
        &E_FLOAT_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new ePersistentFloatRef;
        }
    );

    TypeInfo* ePersistentFloatRef::getType() const
    {
        return &E_PERSISTENTFLOATREF_TYPEINFO;
    }

    ePersistentFloatRef::ePersistentFloatRef()
    : Float()
    {
        id = 0;
    }

    ePersistentFloatRef::~ePersistentFloatRef()
    {}


    ////////////////////////////////////////////////////////////////
    // ePersistentFloatRef: cloning the object
    ////////////////////////////////////////////////////////////////

    void ePersistentFloatRef::createFromOtherObject(const ePersistentFloatRef &other)
    {}

    ePersistentFloatRef::ePersistentFloatRef(const ePersistentFloatRef &other)
    : Float(other)
    {
        createFromOtherObject(other);
    }

    ePersistentFloatRef& ePersistentFloatRef::operator = (const ePersistentFloatRef &other)
    {
        if ((&other) != this)
        {
            Float::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* ePersistentFloatRef::cloneFromMe() const
    {
        return new ePersistentFloatRef(*this);
    }

}
