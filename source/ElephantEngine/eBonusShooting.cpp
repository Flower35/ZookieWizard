#include <ElephantEngine/eBonusShooting.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eBonusShooting interface
    // <kao_tw.006500D0> (constructor)
    // <kao_tw.006501A0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_BONUSSHOOTING_TYPEINFO
    (
        E_BONUSSHOOTING_ID,
        "eBonusShooting",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eBonusShooting;
        }
    );

    TypeInfo* eBonusShooting::getType() const
    {
        return &E_BONUSSHOOTING_TYPEINFO;
    }

    eBonusShooting::eBonusShooting()
    : Gadget()
    {}

    eBonusShooting::~eBonusShooting()
    {}


    ////////////////////////////////////////////////////////////////
    // eBonusShooting: cloning the object
    ////////////////////////////////////////////////////////////////

    void eBonusShooting::createFromOtherObject(const eBonusShooting &other)
    {}

    eBonusShooting::eBonusShooting(const eBonusShooting &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eBonusShooting& eBonusShooting::operator = (const eBonusShooting &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eBonusShooting::cloneFromMe() const
    {
        return new eBonusShooting(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eBonusShooting: serialization
    ////////////////////////////////////////////////////////////////
    void eBonusShooting::serialize(Archive &ar)
    {
        if (ar.getVersion() < 0x89)
        {
            throw ErrorMessage
            (
                "eBonusShooting::serialize():\n" \
                "ar.version() 137 required!"
            );
        }

        Gadget::serialize(ar);
    }

}
