#include <ElephantEngine/eEggsNotStatic.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eEggsNotStatic interface
    // <kao2.005069D1> (constructor)
    // <kao2.00506A50> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_EGGSNOTSTATIC_TYPEINFO
    (
        E_EGGSNOTSTATIC_ID,
        "eEggsNotStatic",
        &E_EGGSFACTORY_TYPEINFO,
        []() -> eObject*
        {
            return new eEggsNotStatic;
        }
    );

    TypeInfo* eEggsNotStatic::getType() const
    {
        return &E_EGGSNOTSTATIC_TYPEINFO;
    }

    eEggsNotStatic::eEggsNotStatic()
    : eEggsFactory()
    {}

    eEggsNotStatic::~eEggsNotStatic()
    {}


    ////////////////////////////////////////////////////////////////
    // eEggsNotStatic: cloning the object
    ////////////////////////////////////////////////////////////////

    void eEggsNotStatic::createFromOtherObject(const eEggsNotStatic &other)
    {}

    eEggsNotStatic::eEggsNotStatic(const eEggsNotStatic &other)
    : eEggsFactory(other)
    {
        createFromOtherObject(other);
    }

    eEggsNotStatic& eEggsNotStatic::operator = (const eEggsNotStatic &other)
    {
        if ((&other) != this)
        {
            eEggsFactory::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eEggsNotStatic::cloneFromMe() const
    {
        return new eEggsNotStatic(*this);
    }

}
