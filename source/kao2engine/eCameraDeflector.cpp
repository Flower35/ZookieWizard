#include <kao2engine/eCameraDeflector.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCameraDeflector interface
    // <kao_tw.005DDCA1> (constructor)
    // <kao_tw.005DDD10> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_CAMERADEFLECTOR_TYPEINFO
    (
        E_CAMERADEFLECTOR_ID,
        "eCameraDeflector",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eCameraDeflector;
        }
    );

    TypeInfo* eCameraDeflector::getType() const
    {
        return &E_CAMERADEFLECTOR_TYPEINFO;
    }

    eCameraDeflector::eCameraDeflector()
    : Gadget()
    {}

    eCameraDeflector::~eCameraDeflector() {}


    ////////////////////////////////////////////////////////////////
    // eCameraDeflector serialization
    ////////////////////////////////////////////////////////////////
    void eCameraDeflector::serialize(Archive &ar)
    {
        if (ar.getVersion() < 0x89)
        {
            throw ErrorMessage
            (
                "eCameraDeflector::serialize():\n" \
                "ar.version() 137 required!"
            );
        }

        Gadget::serialize(ar);
    }

}
