#ifndef H_KAO2AR_TEMPLATES
#define H_KAO2AR_TEMPLATES

#include <ElephantBase/Archive.h>

namespace ZookieWizard
{
    struct TypeInfo;
    class eRefCounter;

    namespace ArFunctions
    {
        ////////////////////////////////////////////////////////////////
        // Serialization of object with undefined IDs (like 0xFFFFFFFF)
        // Function takes care of `incRef()` and `decRef()` instructions
        ////////////////////////////////////////////////////////////////
        template <typename T>
        void serializeKnownObject(Archive &ar, eRefCounter** o, const TypeInfo* t)
        {
            int32_t a;

            if (ar.isInReadMode())
            {
                if (nullptr != (*o))
                {
                    (*o)->decRef();
                }

                ar.readOrWrite(&a, 0x04);

                switch (a)
                {
                    case 0x00:
                    {
                        (*o) = new T;

                        (*o)->incRef();

                        ar.addItem((*o), AR_ITEM_TYPE_OBJECT);

                        (*o)->serialize(ar);

                        return;
                    }

                    case 0x01:
                    {
                        (*o) = nullptr;

                        return;
                    }

                    default:
                    {
                        (*o) = (T*)ar.getItem((a - 2), AR_ITEM_TYPE_OBJECT);

                        (*o)->incRef();

                        return;
                    }
                }
            }
            else
            {
                if (nullptr != (*o))
                {
                    a = ar.findItem(*o);

                    if (a < 0)
                    {
                        ar.addItem((*o), AR_ITEM_TYPE_OBJECT);

                        a = 0x00;
                        ar.readOrWrite(&a, 0x04);

                        (*o)->serialize(ar);

                        return;
                    }
                    else
                    {
                        a += 2;
                        ar.readOrWrite(&a, 0x04);

                        return;
                    }
                }
                else
                {
                    a = 0x01;
                    ar.readOrWrite(&a, 0x04);

                    return;
                }
            }
        }

    }
}

#endif
