#include <kao2engine/eAnimBillboardTarget.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eAnimBillboardTarget interface
    // <kao_tw.00476F20> (constructor)
    // <kao_tw.00476FE0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_ANIMBILLBOARDTARGET_TYPEINFO
    (
        E_ANIMBILLBOARDTARGET_ID,
        "eAnimBillboardTarget",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return new eAnimBillboardTarget;
        }
    );

    TypeInfo* eAnimBillboardTarget::getType() const
    {
        return &E_ANIMBILLBOARDTARGET_TYPEINFO;
    }

    eAnimBillboardTarget::eAnimBillboardTarget()
    : eRefCounter()
    {
        unknown_08 = 0;
        unknown_0C = 0;

        unknown_34 = 0x01;
    }

    eAnimBillboardTarget::~eAnimBillboardTarget()
    {}


    ////////////////////////////////////////////////////////////////
    // eAnimBillboardTarget: cloning the object
    ////////////////////////////////////////////////////////////////

    void eAnimBillboardTarget::createFromOtherObject(const eAnimBillboardTarget &other)
    {
        unknown_08 = other.unknown_08;
        unknown_0C = other.unknown_0C;

        unknown_10 = other.unknown_10;

        framesListFilename = other.framesListFilename;

        unknown_34 = other.unknown_34;
    }

    eAnimBillboardTarget::eAnimBillboardTarget(const eAnimBillboardTarget &other)
    : eRefCounter(other)
    {
        createFromOtherObject(other);
    }

    eAnimBillboardTarget& eAnimBillboardTarget::operator = (const eAnimBillboardTarget &other)
    {
        if ((&other) != this)
        {
            eRefCounter::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eAnimBillboardTarget::cloneFromMe() const
    {
        return new eAnimBillboardTarget(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eAnimBillboardTarget: serialization
    // <kao_tw.004775F0>
    ////////////////////////////////////////////////////////////////
    void eAnimBillboardTarget::serialize(Archive &ar)
    {
        if (ar.getVersion() < 0x8B)
        {
            throw ErrorMessage
            (
                "eAnimBillboardTarget::serialize():\n" \
                "ar.version() 139 required!"
            );
        }

        ar.readOrWrite(&unknown_34, 0x01);

        ar.serializeString(framesListFilename);

        unknown_10.serialize(ar);

        ar.readOrWrite(&unknown_08, 0x04);

        ar.readOrWrite(&unknown_0C, 0x04);
    }

}
