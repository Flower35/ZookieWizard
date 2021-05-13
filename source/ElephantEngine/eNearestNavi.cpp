#include <ElephantEngine/eNearestNavi.h>
#include <ElephantBase/Archive.h>

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

    eNearestNavi::~eNearestNavi()
    {}


    ////////////////////////////////////////////////////////////////
    // eNearestNavi: cloning the object
    ////////////////////////////////////////////////////////////////

    void eNearestNavi::createFromOtherObject(const eNearestNavi &other)
    {}

    eNearestNavi::eNearestNavi(const eNearestNavi &other)
    : eNaviCtrl(other)
    {
        createFromOtherObject(other);
    }

    eNearestNavi& eNearestNavi::operator = (const eNearestNavi &other)
    {
        if ((&other) != this)
        {
            eNaviCtrl::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eNearestNavi::cloneFromMe() const
    {
        return new eNearestNavi(*this);
    }

}
