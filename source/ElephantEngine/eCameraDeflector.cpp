#include <ElephantEngine/eCameraDeflector.h>
#include <ElephantBase/Archive.h>

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

    eCameraDeflector::~eCameraDeflector()
    {}


    ////////////////////////////////////////////////////////////////
    // eCameraDeflector: cloning the object
    ////////////////////////////////////////////////////////////////

    void eCameraDeflector::createFromOtherObject(const eCameraDeflector &other)
    {}

    eCameraDeflector::eCameraDeflector(const eCameraDeflector &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eCameraDeflector& eCameraDeflector::operator = (const eCameraDeflector &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eCameraDeflector::cloneFromMe() const
    {
        return new eCameraDeflector(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eCameraDeflector: serialization
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
