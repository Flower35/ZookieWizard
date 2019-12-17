#include <kao2engine/eDemoPlayer.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eDemoPlayer interface
    // <kao2.00458B80> (constructor)
    // <kao2.00458BF0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_DEMOPLAYER_TYPEINFO
    (
        E_DEMOPLAYER_ID,
        "eDemoPlayer",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eDemoPlayer;
        }
    );

    TypeInfo* eDemoPlayer::getType()
    {
        return &E_DEMOPLAYER_TYPEINFO;
    }

    eDemoPlayer::eDemoPlayer()
    : Gadget()
    {}

    eDemoPlayer::~eDemoPlayer() {}

}
