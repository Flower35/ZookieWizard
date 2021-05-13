#include <ElephantEngine/e3fXArray.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // e3fXArray interface
    // <kao_tw.00434902> (constructor)
    // <kao_tw.00429F90> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_3FXARRAY_TYPEINFO
    (
        E_3FXARRAY_ID,
        "e3fXArray",
        &E_GEOARRAY_EPOINT4_TYPEINFO,
        []() -> eObject*
        {
            return new e3fXArray;
        }
    );

    const TypeInfo* e3fXArray::getType() const
    {
        return &E_3FXARRAY_TYPEINFO;
    }

    e3fXArray::e3fXArray()
    : eGeoArray<ePoint4>()
    {}

    e3fXArray::~e3fXArray()
    {}


    ////////////////////////////////////////////////////////////////
    // e3fXArray: cloning the object
    ////////////////////////////////////////////////////////////////

    void e3fXArray::createFromOtherObject(const e3fXArray &other)
    {}

    e3fXArray::e3fXArray(const e3fXArray &other)
    : eGeoArray<ePoint4>(other)
    {
        createFromOtherObject(other);
    }

    e3fXArray& e3fXArray::operator = (const e3fXArray &other)
    {
        if ((&other) != this)
        {
            eGeoArray<ePoint4>::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* e3fXArray::cloneFromMe() const
    {
        return new e3fXArray(*this);
    }


    ////////////////////////////////////////////////////////////////
    // e3fXArray: wrapped serialization function
    // <kao_tw.00434610>
    ////////////////////////////////////////////////////////////////
    void ArFunctions::serialize_e3fXArray(Archive &ar, eGeoArray<ePoint4>** o)
    {
        int32_t a;

        eGeoArray<ePoint4>* test_object;
        const TypeInfo* current_type;

        if (ar.isInReadMode())
        {
            /* Dereference previous instance (if exists) */

            if (nullptr != (*o))
            {
                (*o)->decRef();

                (*o) = nullptr;
            }

            ar.readOrWrite(&a, 0x04);

            switch (a)
            {
                case 0x00:
                {
                    /* Read TypeInfo index */

                    ar.readOrWrite(&a, 0x04);

                    switch (a)
                    {
                        case E_GEOARRAY_EPOINT4_ID:
                        case E_3FXARRAY_ID:
                        {
                            break;
                        }

                        default:
                        {
                            throw ErrorMessage
                            (
                                "e3fXArray::serialize():\n" \
                                "Wrong object type in archive!\n\n" \
                                "Expected: 0x%08X [%s] or 0x%08X [%s].",
                                E_3FXARRAY_ID,
                                E_3FXARRAY_TYPEINFO.name,
                                E_GEOARRAY_EPOINT4_ID,
                                E_GEOARRAY_EPOINT4_TYPEINFO.name
                            );
                        }
                    }

                    /* Create "e3fXArray" object instance and increase reference counter */

                    (*o) = new e3fXArray;

                    (*o)->incRef();

                    /* Add item to AR list, then serialize */

                    ar.addItem((*o), AR_ITEM_TYPE_OBJECT);

                    (*o)->serialize(ar);

                    return;
                }

                case 0x01:
                {
                    /* Object pointer is already empty */

                    return;
                }

                default:
                {
                    test_object = (eGeoArray<ePoint4>*)ar.getItem((a - 2), AR_ITEM_TYPE_OBJECT);

                    /* Safety check (NOT PRESENT IN GAME): is the new object a subclass of certain type? */

                    current_type = test_object->getType();

                    if (!current_type->checkHierarchy(&E_GEOARRAY_EPOINT4_TYPEINFO))
                    {
                        throw ErrorMessage
                        (
                            "Archive::serialize():\n" \
                            "Wrong object type in archive!\n\n" \
                            "Expected: 0x%08X - %s\n" \
                            "TypeInfo: 0x%08X - %s.",
                            E_GEOARRAY_EPOINT4_ID,
                            E_GEOARRAY_EPOINT4_TYPEINFO.name,
                            current_type->id,
                            current_type->name
                        );

                        return;
                    }

                    (*o) = test_object;

                    (*o)->incRef();

                    return;
                }
            }
        }
        else
        {
            /* Writing mode */

            if (nullptr != (*o))
            {
                a = ar.findItem(*o);

                if (a < 0)
                {
                    ar.addItem((*o), AR_ITEM_TYPE_OBJECT);

                    a = 0x00;
                    ar.readOrWrite(&a, 0x04);

                    if (ar.getVersion() >= 0x89)
                    {
                        a = E_3FXARRAY_ID;
                    }
                    else
                    {
                        a = E_GEOARRAY_EPOINT4_ID;
                    }

                    ar.readOrWrite(&a, 0x04);

                    (*o)->serialize(ar);
                }
                else
                {
                    a += 2;
                    ar.readOrWrite(&a, 0x04);
                }
            }
            else
            {
                a = 0x01;
                ar.readOrWrite(&a, 0x04);
            }
        }
    }

}
