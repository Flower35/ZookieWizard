#include <ElephantEngine/eEggsFactory.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eEggsFactory interface
    // <kao2.00506C80> (constructor)
    // <kao2.00506B80> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_EGGSFACTORY_TYPEINFO
    (
        E_EGGSFACTORY_ID,
        "eEggsFactory",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eEggsFactory;
        }
    );

    const TypeInfo* eEggsFactory::getType() const
    {
        return &E_EGGSFACTORY_TYPEINFO;
    }

    eEggsFactory::eEggsFactory()
    : Gadget()
    {}

    eEggsFactory::~eEggsFactory()
    {}


    ////////////////////////////////////////////////////////////////
    // eEggsFactory: cloning the object
    ////////////////////////////////////////////////////////////////

    void eEggsFactory::createFromOtherObject(const eEggsFactory &other)
    {}

    eEggsFactory::eEggsFactory(const eEggsFactory &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eEggsFactory& eEggsFactory::operator = (const eEggsFactory &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eEggsFactory::cloneFromMe() const
    {
        return new eEggsFactory(*this);
    }

}
