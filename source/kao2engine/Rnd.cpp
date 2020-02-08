#include <kao2engine/Rnd.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Rnd interface
    // <kao2.0059B0D0> (constructor)
    // <kao2.0059B1B0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_RND_TYPEINFO
    (
        E_RND_ID,
        "Rnd",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new Rnd;
        }
    );

    TypeInfo* Rnd::getType() const
    {
        return &E_RND_TYPEINFO;
    }

    Rnd::Rnd()
    : Gadget()
    {
        name = "rnd";
    }

    Rnd::~Rnd() {}


    ////////////////////////////////////////////////////////////////
    // Static Gadget
    ////////////////////////////////////////////////////////////////

    Rnd theRnd;


    ////////////////////////////////////////////////////////////////
    // Rnd: get default name (scripting shenanigans)
    ////////////////////////////////////////////////////////////////
    eString Rnd::getDefaultGadgetName() const
    {
        return "rnd";
    }

}
