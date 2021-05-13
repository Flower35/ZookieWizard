#include <ElephantEngine/eFSMB.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFSMB interface
    // <kao2.0055F9B0> (constructor)
    // <kao2.0055FA90> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_FSMB_TYPEINFO
    (
        E_FSMB_ID,
        "eFSMB",
        &E_FSOP_TYPEINFO,
        []() -> eObject*
        {
            return new eFSMB;
        }
    );

    TypeInfo* eFSMB::getType() const
    {
        return &E_FSMB_TYPEINFO;
    }

    eFSMB::eFSMB()
    : eFSOp()
    {
        name = "fsmb";
    }

    eFSMB::~eFSMB()
    {}


    ////////////////////////////////////////////////////////////////
    // eFSMB: cloning the object
    ////////////////////////////////////////////////////////////////

    void eFSMB::createFromOtherObject(const eFSMB &other)
    {}

    eFSMB::eFSMB(const eFSMB &other)
    : eFSOp(other)
    {
        createFromOtherObject(other);
    }

    eFSMB& eFSMB::operator = (const eFSMB &other)
    {
        if ((&other) != this)
        {
            eFSOp::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eFSMB::cloneFromMe() const
    {
        return new eFSMB(*this);
    }


    ////////////////////////////////////////////////////////////////
    // Static Gadget
    ////////////////////////////////////////////////////////////////

    eFSMB theFSMB;

}
