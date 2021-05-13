#include <ElephantEngine/eGroupMsgForward.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eGroupMsgForward interface
    // <kao2.005282B2> (constructor)
    // <kao2.00528430> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_GROUPMSGFORWARD_TYPEINFO
    (
        E_GROUPMSGFORWARD_ID,
        "eGroupMsgForward",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eGroupMsgForward;
        }
    );

    const TypeInfo* eGroupMsgForward::getType() const
    {
        return &E_GROUPMSGFORWARD_TYPEINFO;
    }

    eGroupMsgForward::eGroupMsgForward()
    : Gadget()
    {}

    eGroupMsgForward::~eGroupMsgForward()
    {}


    ////////////////////////////////////////////////////////////////
    // eGroupMsgForward: cloning the object
    ////////////////////////////////////////////////////////////////

    void eGroupMsgForward::createFromOtherObject(const eGroupMsgForward &other)
    {}

    eGroupMsgForward::eGroupMsgForward(const eGroupMsgForward &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eGroupMsgForward& eGroupMsgForward::operator = (const eGroupMsgForward &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eGroupMsgForward::cloneFromMe() const
    {
        return new eGroupMsgForward(*this);
    }

}
