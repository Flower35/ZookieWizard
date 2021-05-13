#include <ElephantEngine/eTargeting.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eTargeting interface
    // <kao2.0042E701> (constructor)
    // <kao2.0042E770> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_TARGETING_TYPEINFO
    (
        E_TARGETING_ID,
        "eTargeting",
        &E_EMPTYCTRL_TYPEINFO,
        []() -> eObject*
        {
            return new eTargeting;
        }
    );

    TypeInfo* eTargeting::getType() const
    {
        return &E_TARGETING_TYPEINFO;
    }

    eTargeting::eTargeting()
    : eEmptyCtrl()
    {}

    eTargeting::~eTargeting()
    {}


    ////////////////////////////////////////////////////////////////
    // eTargeting: cloning the object
    ////////////////////////////////////////////////////////////////

    void eTargeting::createFromOtherObject(const eTargeting &other)
    {}

    eTargeting::eTargeting(const eTargeting &other)
    : eEmptyCtrl(other)
    {
        createFromOtherObject(other);
    }

    eTargeting& eTargeting::operator = (const eTargeting &other)
    {
        if ((&other) != this)
        {
            eEmptyCtrl::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eTargeting::cloneFromMe() const
    {
        return new eTargeting(*this);
    }

}
