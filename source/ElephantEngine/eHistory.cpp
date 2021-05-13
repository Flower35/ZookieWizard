#include <ElephantEngine/eHistory.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eHistory interface
    // <kao2.004D2190> (constructor)
    // <kao2.004D22E0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_HISTORY_TYPEINFO
    (
        E_HISTORY_ID,
        "eHistory",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eHistory;
        }
    );

    TypeInfo* eHistory::getType() const
    {
        return &E_HISTORY_TYPEINFO;
    }

    eHistory::eHistory()
    : Gadget()
    {}

    eHistory::~eHistory()
    {}


    ////////////////////////////////////////////////////////////////
    // eHistory: cloning the object
    ////////////////////////////////////////////////////////////////

    void eHistory::createFromOtherObject(const eHistory &other)
    {}

    eHistory::eHistory(const eHistory &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eHistory& eHistory::operator = (const eHistory &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eHistory::cloneFromMe() const
    {
        return new eHistory(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eHistory: get default name (scripting shenanigans)
    ////////////////////////////////////////////////////////////////
    eString eHistory::getDefaultGadgetName() const
    {
        return "history";
    }

}
