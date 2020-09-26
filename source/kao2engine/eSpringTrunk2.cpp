#include <kao2engine/eSpringTrunk2.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSpringTrunk2 interface
    // <kao2.004F2C90> (constructor)
    // <kao2.004F2D00> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SPRINGTRUNK2_TYPEINFO
    (
        E_SPRINGTRUNK2_ID,
        "eSpringTrunk2",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eSpringTrunk2;
        }
    );

    TypeInfo* eSpringTrunk2::getType() const
    {
        return &E_SPRINGTRUNK2_TYPEINFO;
    }

    eSpringTrunk2::eSpringTrunk2()
    : Gadget()
    {}

    eSpringTrunk2::~eSpringTrunk2()
    {}


    ////////////////////////////////////////////////////////////////
    // eSpringTrunk2: cloning the object
    ////////////////////////////////////////////////////////////////

    void eSpringTrunk2::createFromOtherObject(const eSpringTrunk2 &other)
    {}

    eSpringTrunk2::eSpringTrunk2(const eSpringTrunk2 &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eSpringTrunk2& eSpringTrunk2::operator = (const eSpringTrunk2 &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eSpringTrunk2::cloneFromMe() const
    {
        return new eSpringTrunk2(*this);
    }

}
