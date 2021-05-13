#include <ElephantEngine/eTorpedoMode.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eTorpedoMode interface
    // <kao2.004CD106> (constructor)
    // <kao2.004CD8C0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_TORPEDOMODE_TYPEINFO
    (
        E_TORPEDOMODE_ID,
        "eTorpedoMode",
        &E_FSOP_TYPEINFO,
        []() -> eObject*
        {
            return new eTorpedoMode;
        }
    );

    TypeInfo* eTorpedoMode::getType() const
    {
        return &E_TORPEDOMODE_TYPEINFO;
    }

    eTorpedoMode::eTorpedoMode()
    : eFSOp()
    {}

    eTorpedoMode::~eTorpedoMode()
    {}


    ////////////////////////////////////////////////////////////////
    // eTorpedoMode: cloning the object
    ////////////////////////////////////////////////////////////////

    void eTorpedoMode::createFromOtherObject(const eTorpedoMode &other)
    {}

    eTorpedoMode::eTorpedoMode(const eTorpedoMode &other)
    : eFSOp(other)
    {
        createFromOtherObject(other);
    }

    eTorpedoMode& eTorpedoMode::operator = (const eTorpedoMode &other)
    {
        if ((&other) != this)
        {
            eFSOp::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eTorpedoMode::cloneFromMe() const
    {
        return new eTorpedoMode(*this);
    }

}
