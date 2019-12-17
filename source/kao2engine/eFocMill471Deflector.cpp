#include <kao2engine/eFocMill471Deflector.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFocMill471Deflector interface
    // <kao_tw.005B5D41> (constructor)
    // <kao_tw.005B61B0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_FOCMILL471DEFLECTOR_TYPEINFO
    (
        E_FOCMILL471DEFLECTOR_ID,
        "eFocMill471Deflector",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eFocMill471Deflector;
        }
    );

    TypeInfo* eFocMill471Deflector::getType()
    {
        return &E_FOCMILL471DEFLECTOR_TYPEINFO;
    }

    eFocMill471Deflector::eFocMill471Deflector()
    : Gadget()
    {}

    eFocMill471Deflector::~eFocMill471Deflector() {}


    ////////////////////////////////////////////////////////////////
    // eFocMill471Deflector serialization
    ////////////////////////////////////////////////////////////////
    void eFocMill471Deflector::serialize(Archive &ar)
    {
        if (ar.getVersion() < 0x89)
        {
            throw ErrorMessage
            (
                "eFocMill471Deflector::serialize():\n" \
                "ar.version() 137 required!"
            );
        }

        Gadget::serialize(ar);
    }

}
