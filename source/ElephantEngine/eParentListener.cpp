#include <ElephantEngine/eParentListener.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eParentListener interface
    // <kao2.00517446> (constructor)
    // <kao2.005174E0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_PARENTLISTENER_TYPEINFO
    (
        E_PARENTLISTENER_ID,
        "eParentListener",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eParentListener;
        }
    );

    const TypeInfo* eParentListener::getType() const
    {
        return &E_PARENTLISTENER_TYPEINFO;
    }

    eParentListener::eParentListener()
    : Gadget()
    {}

    eParentListener::~eParentListener()
    {}


    ////////////////////////////////////////////////////////////////
    // eParentListener: cloning the object
    ////////////////////////////////////////////////////////////////

    void eParentListener::createFromOtherObject(const eParentListener &other)
    {}

    eParentListener::eParentListener(const eParentListener &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eParentListener& eParentListener::operator = (const eParentListener &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eParentListener::cloneFromMe() const
    {
        return new eParentListener(*this);
    }

}
