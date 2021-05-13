#include <ElephantEngine/eOMB.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eOMB interface
    // <kao2.005684E4> (constructor)
    // <kao2.00568F60> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_OMB_TYPEINFO
    (
        E_OMB_ID,
        "eOMB",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eOMB;
        }
    );

    const TypeInfo* eOMB::getType() const
    {
        return &E_OMB_TYPEINFO;
    }

    eOMB::eOMB()
    : Gadget()
    {}

    eOMB::~eOMB()
    {}


    ////////////////////////////////////////////////////////////////
    // eOMB: cloning the object
    ////////////////////////////////////////////////////////////////

    void eOMB::createFromOtherObject(const eOMB &other)
    {}

    eOMB::eOMB(const eOMB &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eOMB& eOMB::operator = (const eOMB &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eOMB::cloneFromMe() const
    {
        return new eOMB(*this);
    }

}
