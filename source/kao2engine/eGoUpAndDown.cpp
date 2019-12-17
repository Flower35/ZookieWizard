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

    TypeInfo* eGoUpAndDown::getType()
    {
        return &E_GOUPANDDOWN_TYPEINFO;
    }

    eGoUpAndDown::eGoUpAndDown()
    : Gadget()
    {}

    eGoUpAndDown::~eGoUpAndDown() {}


    ////////////////////////////////////////////////////////////////
    // eGoUpAndDown serialization
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
