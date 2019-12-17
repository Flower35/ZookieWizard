#include <kao2engine/eEggsFactory.h>
#include <kao2ar/Archive.h>

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

    TypeInfo* eEggsFactory::getType()
    {
        return &E_EGGSFACTORY_TYPEINFO;
    }

    eEggsFactory::eEggsFactory()
    : Gadget()
    {}

    eEggsFactory::~eEggsFactory() {}

}
