#include <ElephantEngine/eMorpherMod.h>
#include <ElephantBase/Archive.h>

#include <ElephantEngine/eMultiBlockIndexCtrl.h>
#include <ElephantEngine/eMorpherTarget.h>

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

    TypeInfo* eMorpherMod::getType() const
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
    // eMorpherMod: cloning the object
    ////////////////////////////////////////////////////////////////

    void eMorpherMod::createFromOtherObject(const eMorpherMod &other)
    {
        controller = nullptr;

        throw ErrorMessage
        (
            "CRITICAL ERROR while cloning the \"eMorpherMod\" object:\n" \
            "cloning << morpher modifiers >> without context is not supported!!!"
        );
    }

    eMorpherMod::eMorpherMod(const eMorpherMod &other)
    : eModifier(other)
    {
        createFromOtherObject(other);
    }

    eMorpherMod& eMorpherMod::operator = (const eMorpherMod &other)
    {
        if ((&other) != this)
        {
            eModifier::operator = (other);

            /****************/

            targets.clear();
            controller->decRef();

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eMorpherMod::cloneFromMe() const
    {
        return new eMorpherMod(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eMorpherMod: serialization
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
