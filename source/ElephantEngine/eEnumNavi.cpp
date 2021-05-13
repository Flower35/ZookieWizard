#include <ElephantEngine/eEnumNavi.h>
#include <ElephantBase/Archive.h>

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

    eEnumNavi::~eEnumNavi()
    {}


    ////////////////////////////////////////////////////////////////
    // eEnumNavi: cloning the object
    ////////////////////////////////////////////////////////////////

    void eEnumNavi::createFromOtherObject(const eEnumNavi &other)
    {}

    eEnumNavi::eEnumNavi(const eEnumNavi &other)
    : eNaviCtrl(other)
    {
        createFromOtherObject(other);
    }

    eEnumNavi& eEnumNavi::operator = (const eEnumNavi &other)
    {
        if ((&other) != this)
        {
            eNaviCtrl::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eEnumNavi::cloneFromMe() const
    {
        return new eEnumNavi(*this);
    }

}
