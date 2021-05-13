#include <ElephantEngine/Anim.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Anim interface
    // <kao2.0059BA40> (constructor)
    // <kao2.0059BB70> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_ANIM_TYPEINFO
    (
        E_ANIM_ID,
        "Anim",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new Anim;
        }
    );

    const TypeInfo* Anim::getType() const
    {
        return &E_ANIM_TYPEINFO;
    }

    Anim::Anim()
    : Gadget()
    {
        /*[0x0C]*/ name = "anim";

        /*[0x10]*/ unknown_10 = 0;
        /*[0x14]*/ unknown_14 = 0;
        /*[0x18]*/ unknown_18 = 1.0f;
    }

    Anim::~Anim()
    {}


    ////////////////////////////////////////////////////////////////
    // Anim: cloning the object
    ////////////////////////////////////////////////////////////////

    void Anim::createFromOtherObject(const Anim &other)
    {
        unknown_10 = other.unknown_10;
        unknown_14 = other.unknown_14;
        unknown_18 = other.unknown_18;
    }

    Anim::Anim(const Anim &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    Anim& Anim::operator = (const Anim &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* Anim::cloneFromMe() const
    {
        return new Anim(*this);
    }


    ////////////////////////////////////////////////////////////////
    // Anim: serialization
    // <kao2.0059C660>
    ////////////////////////////////////////////////////////////////
    void Anim::serialize(Archive &ar)
    {
        Gadget::serialize(ar);

        /* [0x14] unknown */
        ar.readOrWrite(&unknown_14, 0x04);

        /* [0x10] unknown */
        ar.readOrWrite(&unknown_10, 0x01);

        /* [0x18] unknown */
        ar.readOrWrite(&unknown_18, 0x04);
    }


    ////////////////////////////////////////////////////////////////
    // Anim: get default name (scripting shenanigans)
    ////////////////////////////////////////////////////////////////
    eString Anim::getDefaultGadgetName() const
    {
        return "anim";
    }

}
