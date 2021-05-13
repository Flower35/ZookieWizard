#include <ElephantEngine/eSetCollisionFlags.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSetCollisionFlags interface
    // <kao2.0059A301> (constructor)
    // <kao2.0059A4C0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SETCOLLISIONFLAGS_TYPEINFO
    (
        E_SETCOLLISIONFLAGS_ID,
        "eSetCollisionFlags",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eSetCollisionFlags;
        }
    );

    const TypeInfo* eSetCollisionFlags::getType() const
    {
        return &E_SETCOLLISIONFLAGS_TYPEINFO;
    }

    eSetCollisionFlags::eSetCollisionFlags()
    : Gadget()
    {}

    eSetCollisionFlags::~eSetCollisionFlags()
    {}


    ////////////////////////////////////////////////////////////////
    // eSetCollisionFlags: cloning the object
    ////////////////////////////////////////////////////////////////

    void eSetCollisionFlags::createFromOtherObject(const eSetCollisionFlags &other)
    {}

    eSetCollisionFlags::eSetCollisionFlags(const eSetCollisionFlags &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eSetCollisionFlags& eSetCollisionFlags::operator = (const eSetCollisionFlags &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eSetCollisionFlags::cloneFromMe() const
    {
        return new eSetCollisionFlags(*this);
    }

}
