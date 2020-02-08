#include <kao2engine/Key.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Key interface
    // <kao2.0059AE00> (constructor)
    // <kao2.0059AEE0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_KEY_TYPEINFO
    (
        E_KEY_ID,
        "Key",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new Key;
        }
    );

    TypeInfo* Key::getType() const
    {
        return &E_KEY_TYPEINFO;
    }

    Key::Key()
    : Gadget()
    {
        name = "key";
    }

    Key::~Key() {}


    ////////////////////////////////////////////////////////////////
    // Static Gadget
    ////////////////////////////////////////////////////////////////

    Key theKey;


    ////////////////////////////////////////////////////////////////
    // Key: get default name (scripting shenanigans)
    ////////////////////////////////////////////////////////////////
    eString Key::getDefaultGadgetName() const
    {
        return "key";
    }

}
