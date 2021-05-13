#include <ElephantEngine/eRndNavi.h>
#include <ElephantBase/Archive.h>

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

    TypeInfo* eRndNavi::getType() const
    {
        return &E_RNDNAVI_TYPEINFO;
    }

    eRndNavi::eRndNavi()
    : eNaviCtrl()
    {}

    eRndNavi::~eRndNavi()
    {}


    ////////////////////////////////////////////////////////////////
    // eRndNavi: cloning the object
    ////////////////////////////////////////////////////////////////

    void eRndNavi::createFromOtherObject(const eRndNavi &other)
    {}

    eRndNavi::eRndNavi(const eRndNavi &other)
    : eNaviCtrl(other)
    {
        createFromOtherObject(other);
    }

    eRndNavi& eRndNavi::operator = (const eRndNavi &other)
    {
        if ((&other) != this)
        {
            eNaviCtrl::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eRndNavi::cloneFromMe() const
    {
        return new eRndNavi(*this);
    }

}
