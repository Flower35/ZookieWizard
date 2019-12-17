#include <kao2engine/GadgetRef.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // GadgetRef interface
    // <kao_tw.00627180> (constructor)
    // <kao_tw.00627200> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_GADGETREF_TYPEINFO
    (
        E_GADGETREF_ID,
        "GadgetRef",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return new GadgetRef(-1);
        }
    );

    TypeInfo* GadgetRef::getType()
    {
        return &E_GADGETREF_TYPEINFO;
    }

    GadgetRef::GadgetRef(int32_t new_id)
    : eRefCounter()
    {
        /*[0x08]*/ unknown_id = new_id;
    }

    GadgetRef::~GadgetRef() {}


    ////////////////////////////////////////////////////////////////
    // GadgetRef serialization
    // <kao2.00627230>
    ////////////////////////////////////////////////////////////////
    void GadgetRef::serialize(Archive &ar)
    {
        if (ar.getVersion() <= 0x88)
        {
            throw ErrorMessage
            (
                "GadgetRef::serialize():\n" \
                "ar.version() 137 required!"
            );
        }

        /* [0x08] unknown */
        ar.readOrWrite(&unknown_id, 0x04);
    }


    ////////////////////////////////////////////////////////////////
    // GadgetRef: get textual representation
    ////////////////////////////////////////////////////////////////
    eString GadgetRef::getStringRepresentation()
    {
        /* (--dsp--) Find current Actor and his Gadgets Table */

        return "< EMPTY_GADGET >";
    }


}
