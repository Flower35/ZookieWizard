#include <kao2engine/eGoUpAndDown.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eGoUpAndDown interface
    // <kao_tw.0056E6F1> (constructor)
    // <kao_tw.0056E760> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_GOUPANDDOWN_TYPEINFO
    (
        E_GOUPANDDOWN_ID,
        "eGoUpAndDown",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eGoUpAndDown;
        }
    );

    TypeInfo* eGoUpAndDown::getType() const
    {
        return &E_GOUPANDDOWN_TYPEINFO;
    }

    eGoUpAndDown::eGoUpAndDown()
    : Gadget()
    {}

    eGoUpAndDown::~eGoUpAndDown()
    {}


    ////////////////////////////////////////////////////////////////
    // eGoUpAndDown: cloning the object
    ////////////////////////////////////////////////////////////////

    void eGoUpAndDown::createFromOtherObject(const eGoUpAndDown &other)
    {}

    eGoUpAndDown::eGoUpAndDown(const eGoUpAndDown &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eGoUpAndDown& eGoUpAndDown::operator = (const eGoUpAndDown &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eGoUpAndDown::cloneFromMe() const
    {
        return new eGoUpAndDown(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eGoUpAndDown: serialization
    ////////////////////////////////////////////////////////////////
    void eGoUpAndDown::serialize(Archive &ar)
    {
        if (ar.getVersion() < 0x89)
        {
            throw ErrorMessage
            (
                "eGoUpAndDown::serialize():\n" \
                "ar.version() 137 required!"
            );
        }

        Gadget::serialize(ar);
    }

}
