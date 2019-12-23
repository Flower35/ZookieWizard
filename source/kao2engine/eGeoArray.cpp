#include <kao2engine/eGeoArray.h>
#include <kao2ar/Archive.h>

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

    TypeInfo* eGeoArray<ushort>::getType()
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

    TypeInfo* eGeoArray<ePoint2>::getType()
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

    TypeInfo* eGeoArray<ePoint3>::getType()
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

    TypeInfo* eGeoArray<ePoint4>::getType()
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

    TypeInfo* eGeoArray<eABB>::getType()
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

    TypeInfo* eGeoArray<ePhyVertex>::getType()
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
    // eGeoArray serialization
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
    T* eGeoArray<T>::getData()
    {
        return data;
    }


    ////////////////////////////////////////////////////////////////
    // eGeoArray: return number of elements
    ////////////////////////////////////////////////////////////////
    template <typename T>
    int32_t eGeoArray<T>::getLength()
    {
        return length;
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

    template class eGeoArray<ePoint4>;

}
