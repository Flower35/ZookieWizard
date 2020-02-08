#include <kao2engine/eEnumNavi.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eEnumNavi interface
    // <kao2.004295A0> (constructor)
    // <kao2.00429620> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_ENUMNAVI_TYPEINFO
    (
        E_ENUMNAVI_ID,
        "eEnumNavi",
        &E_NAVICTRL_TYPEINFO,
        []() -> eObject*
        {
            return new eEnumNavi;
        }
    );

    TypeInfo* eEnumNavi::getType() const
    {
        return &E_ENUMNAVI_TYPEINFO;
    }

    eEnumNavi::eEnumNavi()
    : eNaviCtrl()
    {}

    eEnumNavi::~eEnumNavi() {}

}
