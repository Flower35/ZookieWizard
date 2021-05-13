#include <ElephantEngine/eKaoKiller.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eKaoKiller interface
    // <kao2.0050BD00> (constructor)
    // <kao2.0050BD70> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_KAOKILLER_TYPEINFO
    (
        E_KAOKILLER_ID,
        "eKaoKiller",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eKaoKiller;
        }
    );

    TypeInfo* eKaoKiller::getType() const
    {
        return &E_KAOKILLER_TYPEINFO;
    }

    eKaoKiller::eKaoKiller()
    : Gadget()
    {}

    eKaoKiller::~eKaoKiller()
    {}


    ////////////////////////////////////////////////////////////////
    // eKaoKiller: cloning the object
    ////////////////////////////////////////////////////////////////

    void eKaoKiller::createFromOtherObject(const eKaoKiller &other)
    {}

    eKaoKiller::eKaoKiller(const eKaoKiller &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eKaoKiller& eKaoKiller::operator = (const eKaoKiller &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eKaoKiller::cloneFromMe() const
    {
        return new eKaoKiller(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eKaoKiller: get default name (scripting shenanigans)
    ////////////////////////////////////////////////////////////////
    eString eKaoKiller::getDefaultGadgetName() const
    {
        return "hero";
    }

}
