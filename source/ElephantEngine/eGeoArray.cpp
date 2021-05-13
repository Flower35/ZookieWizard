#include <ElephantEngine/eGeoArray.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eGeoArray interfaces
    ////////////////////////////////////////////////////////////////

    TypeInfo E_GEOARRAY_USHORT_TYPEINFO
    (
        E_GEOARRAY_USHORT_ID,
        "eGeoArray<ushort>",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return new eGeoArray<ushort>;
        }
    );

    const TypeInfo* eGeoArray<ushort>::getType() const
    {
        return &E_GEOARRAY_USHORT_TYPEINFO;
    }

    TypeInfo E_GEOARRAY_EPOINT2_TYPEINFO
    (
        E_GEOARRAY_EPOINT2_ID,
        "eGeoArray<ePoint2>",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return new eGeoArray<ePoint2>;
        }
    );

    const TypeInfo* eGeoArray<ePoint2>::getType() const
    {
        return &E_GEOARRAY_EPOINT2_TYPEINFO;
    }

    TypeInfo E_GEOARRAY_EPOINT3_TYPEINFO
    (
        E_GEOARRAY_EPOINT3_ID,
        "eGeoArray<ePoint3>",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return new eGeoArray<ePoint3>;
        }
    );

    const TypeInfo* eGeoArray<ePoint3>::getType() const
    {
        return &E_GEOARRAY_EPOINT3_TYPEINFO;
    }

    TypeInfo E_GEOARRAY_EPOINT4_TYPEINFO
    (
        E_GEOARRAY_EPOINT4_ID,
        "eGeoArray<ePoint4>",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return new eGeoArray<ePoint4>;
        }
    );

    const TypeInfo* eGeoArray<ePoint4>::getType() const
    {
        return &E_GEOARRAY_EPOINT4_TYPEINFO;
    }

    TypeInfo E_GEOARRAY_EABB_TYPEINFO
    (
        E_GEOARRAY_EABB_ID,
        "eGeoArray<eABB>",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return new eGeoArray<eABB>;
        }
    );

    const TypeInfo* eGeoArray<eABB>::getType() const
    {
        return &E_GEOARRAY_EABB_TYPEINFO;
    }

    TypeInfo E_GEOARRAY_EPHYVERTEX_TYPEINFO
    (
        E_GEOARRAY_EPHYVERTEX_ID,
        "eGeoArray<ePhyVertex>",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return new eGeoArray<ePhyVertex>;
        }
    );

    const TypeInfo* eGeoArray<ePhyVertex>::getType() const
    {
        return &E_GEOARRAY_EPHYVERTEX_TYPEINFO;
    }

    template <typename T>
    eGeoArray<T>::eGeoArray()
    : eRefCounter()
    {
        /*[0x08]*/ data = nullptr;
        /*[0x0C]*/ length = 0;
    }

    template <typename T>
    eGeoArray<T>::~eGeoArray()
    {
        if (nullptr != data)
        {
            delete[](data);
        }
    }


    ////////////////////////////////////////////////////////////////
    // eGeoArray: cloning the object
    ////////////////////////////////////////////////////////////////

    template <typename T>
    void eGeoArray<T>::createFromOtherObject(const eGeoArray<T> &other)
    {
        if (other.length > 0)
        {
            length = other.length;

            data = new T [length];

            for (int32_t a = 0; a < length; a++)
            {
                data[a] = other.data[a];
            }
        }
        else
        {
            length = 0;
            data = nullptr;
        }
    }

    template <typename T>
    eGeoArray<T>::eGeoArray(const eGeoArray<T> &other)
    : eRefCounter(other)
    {
        createFromOtherObject(other);
    }

    template <typename T>
    eGeoArray<T>& eGeoArray<T>::operator = (const eGeoArray<T> &other)
    {
        if ((&other) != this)
        {
            eRefCounter::operator = (other);

            /****************/

            if (nullptr != data)
            {
                delete[](data);
                data = nullptr;
            }

            length = 0;

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    template <typename T>
    eObject* eGeoArray<T>::cloneFromMe() const
    {
        return new eGeoArray<T>(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eGeoArray: serialization
    ////////////////////////////////////////////////////////////////
    template <typename T>
    void eGeoArray<T>::serialize(Archive &ar)
    {
        ar.readOrWrite(&length, 0x04);

        if (ar.isInReadMode())
        {
            if (nullptr != data)
            {
                delete[](data);
            }

            data = new T [length];
        }

        ar.readOrWrite(data, (sizeof(T) * length));
    }


    ////////////////////////////////////////////////////////////////
    // eGeoArray: return data pointer
    ////////////////////////////////////////////////////////////////
    template <typename T>
    T* eGeoArray<T>::getData() const
    {
        if (nullptr != this)
        {
            return data;
        }

        return nullptr;
    }


    ////////////////////////////////////////////////////////////////
    // eGeoArray: return number of elements
    ////////////////////////////////////////////////////////////////
    template <typename T>
    int32_t eGeoArray<T>::getLength() const
    {
        if (nullptr != this)
        {
            return length;
        }

        return 0;
    }


    ////////////////////////////////////////////////////////////////
    // eGeoArray: setup
    ////////////////////////////////////////////////////////////////
    template <typename T>
    void eGeoArray<T>::setup(int32_t new_length, T* new_data)
    {
        if (nullptr != data)
        {
            delete[](data);
        }

        data = new_data;
        length = new_length;
    }


    ////////////////////////////////////////////////////////////////
    // Explicit templates
    ////////////////////////////////////////////////////////////////

    template class eGeoArray<ushort>;

    template class eGeoArray<ePoint2>;

    template class eGeoArray<ePoint3>;

    template class eGeoArray<ePoint4>;

    template class eGeoArray<ePhyVertex>;

    template class eGeoArray<eABB>;

}
