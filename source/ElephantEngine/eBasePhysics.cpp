#include <ElephantEngine/eBasePhysics.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eBasePhysics interface
    // <kao2.004DC940> (constructor)
    // <kao2.004DCA10> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_BASEPHYSICS_TYPEINFO
    (
        E_BASEPHYSICS_ID,
        "eBasePhysics",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return nullptr;
        }
    );

    TypeInfo* eBasePhysics::getType() const
    {
        return &E_BASEPHYSICS_TYPEINFO;
    }

    eBasePhysics::eBasePhysics()
    : Gadget()
    {}

    eBasePhysics::~eBasePhysics()
    {}


    ////////////////////////////////////////////////////////////////
    // eBasePhysics: cloning the object
    ////////////////////////////////////////////////////////////////

    void eBasePhysics::createFromOtherObject(const eBasePhysics &other)
    {}

    eBasePhysics::eBasePhysics(const eBasePhysics &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eBasePhysics& eBasePhysics::operator = (const eBasePhysics &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eBasePhysics::cloneFromMe() const
    {
        return nullptr;
    }


    ////////////////////////////////////////////////////////////////
    // eBasePhysics: get default name (scripting shenanigans)
    ////////////////////////////////////////////////////////////////
    eString eBasePhysics::getDefaultGadgetName() const
    {
        return "ctrl";
    }

}
