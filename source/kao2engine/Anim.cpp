#include <kao2engine/Anim.h>
#include <kao2ar/Archive.h>

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

    TypeInfo* Anim::getType() const
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

    Anim::~Anim() {}


    ////////////////////////////////////////////////////////////////
    // Anim serialization
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
