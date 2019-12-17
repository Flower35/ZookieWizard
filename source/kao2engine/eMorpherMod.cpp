#include <kao2engine/eMorpherMod.h>
#include <kao2ar/Archive.h>

#include <kao2engine/eMultiBlockIndexCtrl.h>
#include <kao2engine/eMorpherTarget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eMorpherMod interface
    // <kao2.0049F0F0> (constructor)
    // <kao2.0049F340> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_MORPHERMOD_TYPEINFO
    (
        E_MORPHERMOD_ID,
        "eMorpherMod",
        &E_MODIFIER_TYPEINFO,
        []() -> eObject*
        {
            return new eMorpherMod;
        }
    );

    TypeInfo* eMorpherMod::getType()
    {
        return &E_MORPHERMOD_TYPEINFO;
    }

    eMorpherMod::eMorpherMod()
    : eModifier()
    {
        /*[0x14]*/ controller = nullptr;
    }

    eMorpherMod::~eMorpherMod()
    {
        /*[0x14]*/ controller->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // eMorpherMod serialization
    // <kao2.0049F410>
    ////////////////////////////////////////////////////////////////
    void eMorpherMod::serialize(Archive &ar)
    {
        /* targets group */
        targets.serialize(ar, &E_MORPHERTARGET_TYPEINFO);

        /* multi block index ctrl */
        ArFunctions::serialize_eMultiBlockIndexCtrl(ar, (eRefCounter**)&controller, nullptr);
    }

}
