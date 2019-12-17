#include <kao2engine/eBasePhysics.h>
#include <kao2ar/Archive.h>

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

    TypeInfo* eBasePhysics::getType()
    {
        return &E_BASEPHYSICS_TYPEINFO;
    }

    eBasePhysics::eBasePhysics()
    : Gadget()
    {}

    eBasePhysics::~eBasePhysics() {}


    ////////////////////////////////////////////////////////////////
    // eBasePhysics: get default name (scripting shenanigans)
    ////////////////////////////////////////////////////////////////
    eString eBasePhysics::getDefaultGadgetName()
    {
        return "ctrl";
    }

}
