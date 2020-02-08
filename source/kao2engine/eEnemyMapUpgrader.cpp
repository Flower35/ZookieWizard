#include <kao2engine/eEnemyMapUpgrader.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eEnemyMapUpgrader interface
    // <kao2.0045C040> (constructor)
    // <kao2.0045C0E0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_ENEMYMAPUPGRADER_TYPEINFO
    (
        E_ENEMYMAPUPGRADER_ID,
        "eEnemyMapUpgrader",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eEnemyMapUpgrader;
        }
    );

    TypeInfo* eEnemyMapUpgrader::getType() const
    {
        return &E_ENEMYMAPUPGRADER_TYPEINFO;
    }

    eEnemyMapUpgrader::eEnemyMapUpgrader()
    : Gadget()
    {}

    eEnemyMapUpgrader::~eEnemyMapUpgrader() {}

}
