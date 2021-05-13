#include <ElephantEngine/Rnd.h>
#include <ElephantBase/Archive.h>

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

    Rnd::~Rnd()
    {}


    ////////////////////////////////////////////////////////////////
    // Rnd: cloning the object
    ////////////////////////////////////////////////////////////////

    void Rnd::createFromOtherObject(const Rnd &other)
    {}

    Rnd::Rnd(const Rnd &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    Rnd& Rnd::operator = (const Rnd &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* Rnd::cloneFromMe() const
    {
        return new Rnd(*this);
    }


    ////////////////////////////////////////////////////////////////
    // Rnd: get default name (scripting shenanigans)
    ////////////////////////////////////////////////////////////////
    eString Rnd::getDefaultGadgetName() const
    {
        return "rnd";
    }


    ////////////////////////////////////////////////////////////////
    // Static Gadget
    ////////////////////////////////////////////////////////////////

    Rnd theRnd;

}
