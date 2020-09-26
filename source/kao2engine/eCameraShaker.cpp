#include <kao2engine/eCameraShaker.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCameraShaker interface
    // <kao2.004D59E1> (constructor)
    // <kao2.004D5B10> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_CAMERASHAKER_TYPEINFO
    (
        E_CAMERASHAKER_ID,
        "eCameraShaker",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eCameraShaker;
        }
    );

    TypeInfo* eCameraShaker::getType() const
    {
        return &E_CAMERASHAKER_TYPEINFO;
    }

    eCameraShaker::eCameraShaker()
    : Gadget()
    {}

    eCameraShaker::~eCameraShaker()
    {}


    ////////////////////////////////////////////////////////////////
    // eCameraShaker: cloning the object
    ////////////////////////////////////////////////////////////////

    void eCameraShaker::createFromOtherObject(const eCameraShaker &other)
    {}

    eCameraShaker::eCameraShaker(const eCameraShaker &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eCameraShaker& eCameraShaker::operator = (const eCameraShaker &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eCameraShaker::cloneFromMe() const
    {
        return new eCameraShaker(*this);
    }

}
