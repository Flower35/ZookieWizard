#include <ElephantEngine/eObjectLinker.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eObjectLinker interface
    // <kao2.00519B82> (constructor)
    // <kao2.00519C10> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_OBJECTLINKER_TYPEINFO
    (
        E_OBJECTLINKER_ID,
        "eObjectLinker",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eObjectLinker;
        }
    );

    const TypeInfo* eObjectLinker::getType() const
    {
        return &E_OBJECTLINKER_TYPEINFO;
    }

    eObjectLinker::eObjectLinker()
    : Gadget()
    {}

    eObjectLinker::~eObjectLinker()
    {}


    ////////////////////////////////////////////////////////////////
    // eObjectLinker: cloning the object
    ////////////////////////////////////////////////////////////////

    void eObjectLinker::createFromOtherObject(const eObjectLinker &other)
    {}

    eObjectLinker::eObjectLinker(const eObjectLinker &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eObjectLinker& eObjectLinker::operator = (const eObjectLinker &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eObjectLinker::cloneFromMe() const
    {
        return new eObjectLinker(*this);
    }

}
