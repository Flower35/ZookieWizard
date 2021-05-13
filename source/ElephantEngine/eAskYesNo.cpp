#include <ElephantEngine/eAskYesNo.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eAskYesNo interface
    // <kao2.0045EF90> (constructor)
    // <kao2.0045F080> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_ASKYESNO_TYPEINFO
    (
        E_ASKYESNO_ID,
        "eAskYesNo",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eAskYesNo;
        }
    );

    const TypeInfo* eAskYesNo::getType() const
    {
        return &E_ASKYESNO_TYPEINFO;
    }

    eAskYesNo::eAskYesNo()
    : Gadget()
    {}

    eAskYesNo::~eAskYesNo()
    {}


    ////////////////////////////////////////////////////////////////
    // eAskYesNo: cloning the object
    ////////////////////////////////////////////////////////////////

    void eAskYesNo::createFromOtherObject(const eAskYesNo &other)
    {}

    eAskYesNo::eAskYesNo(const eAskYesNo &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eAskYesNo& eAskYesNo::operator = (const eAskYesNo &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eAskYesNo::cloneFromMe() const
    {
        return new eAskYesNo(*this);
    }

}
