#include <kao2engine/eSpeaking.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSpeaking interface
    // <kao2.004578D0> (constructor)
    // <kao2.00457960> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SPEAKING_TYPEINFO
    (
        E_SPEAKING_ID,
        "eSpeaking",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eSpeaking;
        }
    );

    TypeInfo* eSpeaking::getType()
    {
        return &E_SPEAKING_TYPEINFO;
    }

    eSpeaking::eSpeaking()
    : Gadget()
    {}

    eSpeaking::~eSpeaking() {}

}
