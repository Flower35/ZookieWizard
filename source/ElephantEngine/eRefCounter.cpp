#include <ElephantEngine/eRefCounter.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eRefCounter interface
    // <kao2.004632B8> (constructor)
    // <kao2.????????> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_REFCOUNTER_TYPEINFO
    (
        E_REFCOUNTER_ID,
        "eRefCounter",
        &E_OBJECT_TYPEINFO,
        []() -> eObject*
        {
            return new eRefCounter;
        }
    );

    const TypeInfo* eRefCounter::getType() const
    {
        return &E_REFCOUNTER_TYPEINFO;
    }

    eRefCounter::eRefCounter()
    : eObject()
    {
        /*[0x04]*/ referenceCount = 0;
    }

    eRefCounter::~eRefCounter()
    {}


    ////////////////////////////////////////////////////////////////
    // eRefCounter: cloning the object
    ////////////////////////////////////////////////////////////////

    void eRefCounter::createFromOtherObject(const eRefCounter &other)
    {
        /* << MUST BE RESOLVED! >> */
        referenceCount = 0;
    }

    eRefCounter::eRefCounter(const eRefCounter &other)
    : eObject(other)
    {
        createFromOtherObject(other);
    }

    eRefCounter& eRefCounter::operator = (const eRefCounter &other)
    {
        if ((&other) != this)
        {
            eObject::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eRefCounter::cloneFromMe() const
    {
        return new eRefCounter(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eRefCounter: increase reference
    ////////////////////////////////////////////////////////////////
    void eRefCounter::incRef()
    {
        if (nullptr != this)
        {
            referenceCount++;
        }
        else
        {
            throw ErrorMessage
            (
                "eRefCounter::incRef():\n" \
                "object does not exist! (pointer not initialized or memory allocation error)"
            );
        }
    }


    ////////////////////////////////////////////////////////////////
    // eRefCounter: decrease reference
    // <kao2.00402950>
    ////////////////////////////////////////////////////////////////
    void eRefCounter::decRef()
    {
        if (nullptr != this)
        {
            referenceCount--;

            if (0 == referenceCount)
            {
                delete this;
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eRefCounter: get reference count
    ////////////////////////////////////////////////////////////////
    int32_t eRefCounter::getReferenceCount() const
    {
        return referenceCount;
    }


    ////////////////////////////////////////////////////////////////
    // Archive: macro for objects with reference counters
    ////////////////////////////////////////////////////////////////
    void ArFunctions::serialize_eRefCounter(Archive &ar, eRefCounter** o, const TypeInfo* t)
    {
        if (ar.isInReadMode())
        {
            (*o)->decRef();
            (*o) = nullptr;
        }

        try
        {
            ar.serialize((eObject**)o, t);
        }
        catch (std::bad_alloc)
        {
            if (ar.isInReadMode() && (nullptr != (*o)))
            {
                (*o)->incRef();
            }

            /* Catch "std::bad_alloc" in `Archive::serialize()`! */
            throw;
        }
        catch (ErrorMessage)
        {
            if (ar.isInReadMode() && (nullptr != (*o)))
            {
                (*o)->incRef();
            }

            /* Catch "ErrorMessage" in `Archive::serialize()`! */
            throw;
        }

        if (ar.isInReadMode() && (nullptr != (*o)))
        {
            (*o)->incRef();
        }
    }

}
