#include <kao2engine/eObjectLinker.h>
#include <kao2ar/Archive.h>

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

    TypeInfo* eObjectLinker::getType() const
    {
        return &E_OBJECTLINKER_TYPEINFO;
    }

    eObjectLinker::eObjectLinker()
    : Gadget()
    {}

    eObjectLinker::~eObjectLinker() {}

}
