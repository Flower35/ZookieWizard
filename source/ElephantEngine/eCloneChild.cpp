#include <ElephantEngine/eCloneChild.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCloneChild interface
    // <kao2.005A50C0> (constructor)
    // <kao2.005A5150> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_CLONECHILD_TYPEINFO
    (
        E_CLONECHILD_ID,
        "eCloneChild",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eCloneChild;
        }
    );

    TypeInfo* eCloneChild::getType() const
    {
        return &E_CLONECHILD_TYPEINFO;
    }

    eCloneChild::eCloneChild()
    : Gadget()
    {}

    eCloneChild::~eCloneChild()
    {}


    ////////////////////////////////////////////////////////////////
    // eCloneChild: cloning the object
    ////////////////////////////////////////////////////////////////

    void eCloneChild::createFromOtherObject(const eCloneChild &other)
    {}

    eCloneChild::eCloneChild(const eCloneChild &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eCloneChild& eCloneChild::operator = (const eCloneChild &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eCloneChild::cloneFromMe() const
    {
        return new eCloneChild(*this);
    }

}
