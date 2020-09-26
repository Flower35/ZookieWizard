#include <kao2engine/eNaviCtrl.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eNaviCtrl interface
    // <kao2.00428310> (constructor)
    // <kao2.004283F0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_NAVICTRL_TYPEINFO
    (
        E_NAVICTRL_ID,
        "eNaviCtrl",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return nullptr;
        }
    );

    TypeInfo* eNaviCtrl::getType() const
    {
        return &E_NAVICTRL_TYPEINFO;
    }

    eNaviCtrl::eNaviCtrl()
    : Gadget()
    {}

    eNaviCtrl::~eNaviCtrl()
    {}


    ////////////////////////////////////////////////////////////////
    // eNaviCtrl: cloning the object
    ////////////////////////////////////////////////////////////////

    void eNaviCtrl::createFromOtherObject(const eNaviCtrl &other)
    {}

    eNaviCtrl::eNaviCtrl(const eNaviCtrl &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eNaviCtrl& eNaviCtrl::operator = (const eNaviCtrl &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eNaviCtrl::cloneFromMe() const
    {
        return nullptr;
    }


    ////////////////////////////////////////////////////////////////
    // eNaviCtrl: get default name (scripting shenanigans)
    ////////////////////////////////////////////////////////////////
    eString eNaviCtrl::getDefaultGadgetName() const
    {
        return "navi";
    }

}
