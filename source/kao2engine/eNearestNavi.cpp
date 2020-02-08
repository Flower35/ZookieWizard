#include <kao2engine/eNearestNavi.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eNearestNavi interface
    // <kao2.00429780> (constructor)
    // <kao2.004297F0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_NEARESTNAVI_TYPEINFO
    (
        E_NEARESTNAVI_ID,
        "eNearestNavi",
        &E_NAVICTRL_TYPEINFO,
        []() -> eObject*
        {
            return new eNearestNavi;
        }
    );

    TypeInfo* eNearestNavi::getType() const
    {
        return &E_NEARESTNAVI_TYPEINFO;
    }

    eNearestNavi::eNearestNavi()
    : eNaviCtrl()
    {}

    eNearestNavi::~eNearestNavi() {}

}
