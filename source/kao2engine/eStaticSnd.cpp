#include <kao2engine/eStaticSnd.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eStaticSnd interface
    // <kao2.00439C40> (constructor)
    // <kao2.00439CC0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_STATICSND_TYPEINFO
    (
        E_STATICSND_ID,
        "eStaticSnd",
        &E_SND_TYPEINFO,
        []() -> eObject*
        {
            return new eStaticSnd;
        }
    );

    TypeInfo* eStaticSnd::getType() const
    {
        return &E_STATICSND_TYPEINFO;
    }

    eStaticSnd::eStaticSnd()
    : eSnd()
    {}

    eStaticSnd::~eStaticSnd() {}

}
