#include <ElephantEngine/eBillboard.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eBillboard interface
    // <kao2.004AC9F6> (constructor)
    // <kao2.004ACAF0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_BILLBOARD_TYPEINFO
    (
        E_BILLBOARD_ID,
        "eBillboard",
        &E_TRANSFORM_TYPEINFO,
        []() -> eObject*
        {
            return new eBillboard;
        }
    );

    TypeInfo* eBillboard::getType() const
    {
        return &E_BILLBOARD_TYPEINFO;
    }

    eBillboard::eBillboard()
    : eTransform()
    {
        /*[0xAC]*/ billboarded = true;
    }

    eBillboard::~eBillboard()
    {}


    ////////////////////////////////////////////////////////////////
    // eBillboard: cloning the object
    ////////////////////////////////////////////////////////////////

    void eBillboard::createFromOtherObject(const eBillboard &other)
    {
        billboarded = other.billboarded;
    }

    eBillboard::eBillboard(const eBillboard &other)
    : eTransform(other)
    {
        createFromOtherObject(other);
    }

    eBillboard& eBillboard::operator = (const eBillboard &other)
    {
        if ((&other) != this)
        {
            eTransform::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eBillboard::cloneFromMe() const
    {
        return new eBillboard(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eBillboard: serialization
    // <kao2.004AC7A0>
    ////////////////////////////////////////////////////////////////
    void eBillboard::serialize(Archive &ar)
    {
        eTransform::serialize(ar);

        ar.readOrWrite(&billboarded, 0x01);
    }

}
