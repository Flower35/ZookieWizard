#include <kao2engine/eParentListener.h>
#include <kao2ar/Archive.h>

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

    TypeInfo* eParentListener::getType() const
    {
        return &E_PARENTLISTENER_TYPEINFO;
    }

    eParentListener::eParentListener()
    : Gadget()
    {}

    eParentListener::~eParentListener() {}

}
