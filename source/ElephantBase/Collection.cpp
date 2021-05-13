#include <ElephantBase/Collection.h>

#include <ElephantBase/Archive.h>
#include <ElephantEngine/eRefCounter.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Collection: Constructor and Destructor
    ////////////////////////////////////////////////////////////////

    template <void (*Func)(Archive&, eRefCounter**, const TypeInfo*)>
    Collection<Func>::Collection(int32_t new_size)
    {
        count = 0;
        maxLength = new_size;

        if (new_size > 0)
        {
            children = new eRefCounter* [maxLength];

            for (int32_t a = 0; a < maxLength; a++)
            {
                children[a] = nullptr;
            }
        }
        else
        {
            children = nullptr;
        }
    }

    template <void (*Func)(Archive&, eRefCounter**, const TypeInfo*)>
    Collection<Func>::~Collection()
    {
        clear();

        if (nullptr != children)
        {
            delete[](children);
        }
    }


    ////////////////////////////////////////////////////////////////
    // Collection: cloning the object
    ////////////////////////////////////////////////////////////////

    template <void (*Func)(Archive&, eRefCounter**, const TypeInfo*)>
    void Collection<Func>::createFromOtherObject(const Collection<Func> &other)
    {
        if (other.count > 0)
        {
            count = other.count;
            maxLength = count;

            children = new eRefCounter* [count];

            for (int32_t a = 0; a < count; a++)
            {
                children[a] = other.children[a];

                if (nullptr != children[a])
                {
                    children[a]->incRef();
                }
            }
        }
        else
        {
            count = 0;
            maxLength = 0;
            children = nullptr;
        }
    }

    template <void (*Func)(Archive&, eRefCounter**, const TypeInfo*)>
    Collection<Func>::Collection(const Collection<Func> &other)
    {
        createFromOtherObject(other);
    }

    template <void (*Func)(Archive&, eRefCounter**, const TypeInfo*)>
    Collection<Func>& Collection<Func>::operator = (const Collection<Func> &other)
    {
        if ((&other) != this)
        {
            clear();
            maxLength = 0;

            if (nullptr != children)
            {
                delete[](children);
                children = nullptr;
            }

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    template <void (*Func)(Archive&, eRefCounter**, const TypeInfo*)>
    Collection<Func>& Collection<Func>::deepCopy(const Collection<Func> &other)
    {
        if ((&other) != this)
        {
            clear();
            maxLength = 0;

            if (nullptr != children)
            {
                delete[](children);
                children = nullptr;
            }

            /****************/

            if (other.count > 0)
            {
                count = other.count;
                maxLength = count;

                children = new eRefCounter* [count];

                /* First mark all children as invalid, to avoid problems if any exception occurs */

                for (int32_t a = 0; a < count; a++)
                {
                    children[a] = nullptr;
                }

                for (int32_t a = 0; a < count; a++)
                {
                    if (nullptr != other.children[a])
                    {
                        children[a] = (eRefCounter*)other.children[a]->cloneFromMe();

                        if (nullptr != children[a])
                        {
                            children[a]->incRef();
                        }
                    }
                }
            }
        }

        return (*this);
    }


    ////////////////////////////////////////////////////////////////
    // Collection: Decreasing references and clearing the collection
    ////////////////////////////////////////////////////////////////
    template <void (*Func)(Archive&, eRefCounter**, const TypeInfo*)>
    void Collection<Func>::clear()
    {
        for (int32_t i = 0; i < count; i++)
        {
            if (nullptr != children[i])
            {
                children[i]->decRef();
                children[i] = nullptr;
            }
        }

        count = 0;
    }


    ////////////////////////////////////////////////////////////////
    // Collection: Serialization
    ////////////////////////////////////////////////////////////////
    template <void (*Func)(Archive&, eRefCounter**, const TypeInfo*)>
    void Collection<Func>::serialize(Archive &ar, const TypeInfo* t)
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
    // Collection: Get group size
    ////////////////////////////////////////////////////////////////
    template <void (*Func)(Archive&, eRefCounter**, const TypeInfo*)>
    int32_t Collection<Func>::getSize() const
    {
        return count;
    }


    ////////////////////////////////////////////////////////////////
    // Collection: Explicitly set the i-th object from the group
    ////////////////////////////////////////////////////////////////
    template <void (*Func)(Archive&, eRefCounter**, const TypeInfo*)>
    void Collection<Func>::setIthChild(int32_t i, eRefCounter* o)
    {
        if ((i >= 0) && (i < count))
        {
            if (children[i] != o)
            {
                if (nullptr != children[i])
                {
                    children[i]->decRef();
                }

                children[i] = o;

                if (nullptr != children[i])
                {
                    children[i]->incRef();
                }
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // Collection: Get i-th object from group
    ////////////////////////////////////////////////////////////////
    template <void (*Func)(Archive&, eRefCounter**, const TypeInfo*)>
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
    // Collection: Insert new "eRefCounter" child
    ////////////////////////////////////////////////////////////////
    template <void (*Func)(Archive&, eRefCounter**, const TypeInfo*)>
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
    // Collection: Take out i-th object from group
    ////////////////////////////////////////////////////////////////
    template <void (*Func)(Archive&, eRefCounter**, const TypeInfo*)>
    void Collection<Func>::deleteIthChild(int32_t i)
    {
        if ((i >= 0) && (i < count))
        {
            children[i]->decRef();

            /* Shift every next child back */

            for (i++; i < count; i++)
            {
                children[i - 1] = children[i];
            }

            count--;

            children[count] = nullptr;
        }
    }


    ////////////////////////////////////////////////////////////////
    // Collection: Take out specific object from group
    ////////////////////////////////////////////////////////////////
    template <void (*Func)(Archive&, eRefCounter**, const TypeInfo*)>
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
    // Collection: Swap objects by one place (backwards or forwards)
    ////////////////////////////////////////////////////////////////

    template <void (*Func)(Archive&, eRefCounter**, const TypeInfo*)>
    void Collection<Func>::swapForward(int32_t i)
    {
        eRefCounter* temp_o;

        if ((i < 0) || (i >= (count - 1)))
        {
            return;
        }

        temp_o = children[i];
        children[i] = children[i + 1];
        children[i + 1] = temp_o;
    }

    template <void (*Func)(Archive&, eRefCounter**, const TypeInfo*)>
    void Collection<Func>::swapBackward(int32_t i)
    {
        eRefCounter* temp_o;

        if ((i <= 0) || (i > (count - 1)))
        {
            return;
        }

        temp_o = children[i];
        children[i] = children[i - 1];
        children[i - 1] = temp_o;
    }


    ////////////////////////////////////////////////////////////////
    // Explicit templates
    ////////////////////////////////////////////////////////////////

    template struct Collection<ArFunctions::serialize_eRefCounter>;
    template struct Collection<ArFunctions::serialize_Property>;
    template struct Collection<ArFunctions::serialize_StringProperty>;
    template struct Collection<ArFunctions::serialize_StringSection>;

}
