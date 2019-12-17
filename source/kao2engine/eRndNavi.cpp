#include <kao2engine/eRndNavi.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eRndNavi interface
    // <kao2.00428B00> (constructor)
    // <kao2.00428B70> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_RNDNAVI_TYPEINFO
    (
        E_RNDNAVI_ID,
        "eRndNavi",
        &E_NAVICTRL_TYPEINFO,
        []() -> eObject*
        {
            return new eRndNavi;
        }
    );

    TypeInfo* eRndNavi::getType()
    {
        return &E_RNDNAVI_TYPEINFO;
    }

    eRndNavi::eRndNavi()
    : eNaviCtrl()
    {}

    eRndNavi::~eRndNavi() {}

}
