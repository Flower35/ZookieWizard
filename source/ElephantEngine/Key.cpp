#include <ElephantEngine/Key.h>
#include <ElephantBase/Archive.h>

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

    Key::~Key()
    {}


    ////////////////////////////////////////////////////////////////
    // Key: cloning the object
    ////////////////////////////////////////////////////////////////

    void Key::createFromOtherObject(const Key &other)
    {}

    Key::Key(const Key &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    Key& Key::operator = (const Key &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* Key::cloneFromMe() const
    {
        return new Key(*this);
    }


    ////////////////////////////////////////////////////////////////
    // Key: get default name (scripting shenanigans)
    ////////////////////////////////////////////////////////////////
    eString Key::getDefaultGadgetName() const
    {
        return "key";
    }


    ////////////////////////////////////////////////////////////////
    // Static Gadget
    ////////////////////////////////////////////////////////////////

    Key theKey;


}
