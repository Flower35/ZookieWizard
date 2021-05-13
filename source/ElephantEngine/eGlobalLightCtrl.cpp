#include <ElephantEngine/eGlobalLightCtrl.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eGlobalLightCtrl interface
    // <kao_tw.0052FAB1> (constructor)
    // <kao_tw.0052FB20> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_GLOBALLIGHTCTRL_TYPEINFO
    (
        E_GLOBALLIGHTCTRL_ID,
        "eGlobalLightCtrl",
        &E_GROUP_TYPEINFO,
        []() -> eObject*
        {
            return new eGlobalLightCtrl;
        }
    );

    const TypeInfo* eGlobalLightCtrl::getType() const
    {
        return &E_GLOBALLIGHTCTRL_TYPEINFO;
    }

    eGlobalLightCtrl::eGlobalLightCtrl()
    : eGroup()
    {}

    eGlobalLightCtrl::~eGlobalLightCtrl()
    {}


    ////////////////////////////////////////////////////////////////
    // eGlobalLightCtrl: cloning the object
    ////////////////////////////////////////////////////////////////

    void eGlobalLightCtrl::createFromOtherObject(const eGlobalLightCtrl &other)
    {}

    eGlobalLightCtrl::eGlobalLightCtrl(const eGlobalLightCtrl &other)
    : eGroup(other)
    {
        createFromOtherObject(other);
    }

    eGlobalLightCtrl& eGlobalLightCtrl::operator = (const eGlobalLightCtrl &other)
    {
        if ((&other) != this)
        {
            eGroup::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eGlobalLightCtrl::cloneFromMe() const
    {
        return new eGlobalLightCtrl(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eGlobalLightCtrl: serialization
    ////////////////////////////////////////////////////////////////
    void eGlobalLightCtrl::serialize(Archive &ar)
    {
        if (ar.getVersion() < 0x90)
        {
            throw ErrorMessage
            (
                "eGlobalLightCtrl::serialize():\n" \
                "ar.version() 144 required!"
            );
        }

        eGroup::serialize(ar);
    }

}
