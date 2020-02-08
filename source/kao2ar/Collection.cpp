#include <kao2ar/Collection.h>

#include <kao2ar/Archive.h>
#include <kao2engine/eRefCounter.h>

namespace ZookieWizard
{
    template <void (*Func)(Archive&, eRefCounter**, TypeInfo*)>
    Collection<Func>::Collection()
    {
        count = 0;
        maxLength = 0;
        children = nullptr;
    }

    template <void (*Func)(Archive&, eRefCounter**, TypeInfo*)>
    Collection<Func>::~Collection()
    {
        int32_t i;

        if (nullptr != children)
        {
            for (i = 0; i < count; i++)
            {
                children[i]->decRef();
            }

            delete[](children);
        }
    }

    template <void (*Func)(Archive&, eRefCounter**, TypeInfo*)>
    void Collection<Func>::serialize(Archive &ar, TypeInfo* t)
    {
        int32_t i;

        if (ar.isInReadMode())
        {
            if (nullptr != children)
            {
                for (i = 0; i < count; i++)
                {
                    children[i]->decRef();
                }

                count = 0;

                delete[](children);
                children = nullptr;
            }

            ar.readOrWrite(&maxLength, 0x04);

            if (maxLength > 0)
            {
                children = new eRefCounter* [maxLength];

                for (i = 0; i < maxLength; i++)
                {
                    children[i] = nullptr;

                    count = (i + 1);

                    Func(ar, &(children[i]), t);

                    /* < NOTE! > Reference must be increased inside Function: */
                    /* `children[count]->incRef();` */
                }
            }
        }
        else
        {
            ar.readOrWrite(&count, 0x04);

            for (i = 0; i < count; i++)
            {
                Func(ar, &(children[i]), t);
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // Get group size
    ////////////////////////////////////////////////////////////////
    template <void (*Func)(Archive&, eRefCounter**, TypeInfo*)>
    int32_t Collection<Func>::getSize() const
    {
        return count;
    }


    ////////////////////////////////////////////////////////////////
    // Get i-th object from group
    ////////////////////////////////////////////////////////////////
    template <void (*Func)(Archive&, eRefCounter**, TypeInfo*)>
    eRefCounter* Collection<Func>::getIthChild(int32_t i) const
    {
        if ((i >= 0) && (i < count))
        {
            return children[i];
        }
        else
        {
            return nullptr;
        }
    }


    ////////////////////////////////////////////////////////////////
    // Insert new eRefCounter child
    ////////////////////////////////////////////////////////////////
    template <void (*Func)(Archive&, eRefCounter**, TypeInfo*)>
    void Collection<Func>::appendChild(eRefCounter* o)
    {
        int32_t i;
        eRefCounter** temp;

        if ((count + 1) > maxLength)
        {
            temp = new eRefCounter* [maxLength + 1];

            if (nullptr != children)
            {
                for (i = 0; i < count; i++)
                {
                    temp[i] = children[i];
                }

                delete[](children);
            }

            children = temp;

            maxLength++;
        }

        children[count] = o;

        if (nullptr != o)
        {
            o->incRef();
        }

        count++;
    }


    ////////////////////////////////////////////////////////////////
    // Take out i-th object from group
    ////////////////////////////////////////////////////////////////
    template <void (*Func)(Archive&, eRefCounter**, TypeInfo*)>
    void Collection<Func>::deleteIthChild(int32_t i)
    {
        if ((i >= 0) && (i < count))
        {
            children[i]->decRef();
            children[i] = nullptr;

            /* Shift every next child back */

            for (i++; i < count; i++)
            {
                children[i - 1] = children[i];
                children[i] = nullptr;
            }

            count--;
        }
    }


    ////////////////////////////////////////////////////////////////
    // Take out specific object from group
    ////////////////////////////////////////////////////////////////
    template <void (*Func)(Archive&, eRefCounter**, TypeInfo*)>
    void Collection<Func>::findAndDeleteChild(eRefCounter* o)
    {
        int32_t i;

        for (i = 0; i < count; i++)
        {
            if (o == children[i])
            {
                deleteIthChild(i);
                return;
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // Explicit templates
    ////////////////////////////////////////////////////////////////

    template struct Collection<ArFunctions::serialize_eRefCounter>;
    template struct Collection<ArFunctions::serialize_Property>;
    template struct Collection<ArFunctions::serialize_StringProperty>;
    template struct Collection<ArFunctions::serialize_StringSection>;

}
