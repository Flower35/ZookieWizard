#include <kao2engine/AnimDumper.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // AnimDumper interface
    // <kao2.005AF7C2> (constructor)
    // <kao2.005AFE70> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_ANIMDUMPER_TYPEINFO
    (
        E_ANIMDUMPER_ID,
        "AnimDumper",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new AnimDumper;
        }
    );

    TypeInfo* AnimDumper::getType()
    {
        return &E_ANIMDUMPER_TYPEINFO;
    }

    AnimDumper::AnimDumper()
    : Gadget()
    {}

    AnimDumper::~AnimDumper() {}

}
