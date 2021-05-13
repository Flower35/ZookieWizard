#include <ElephantEngine/eMorpherTarget.h>
#include <ElephantBase/Archive.h>

#include <ElephantEngine/e3fXArray.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eMorpherTarget interface
    // <kao2.0049EF79> (constructor)
    // <kao2.0049F020> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_MORPHERTARGET_TYPEINFO
    (
        E_MORPHERTARGET_ID,
        "eMorpherTarget",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return new eMorpherTarget;
        }
    );

    TypeInfo* eMorpherTarget::getType() const
    {
        return &E_MORPHERTARGET_TYPEINFO;
    }

    eMorpherTarget::eMorpherTarget()
    : eRefCounter()
    {
        /*[0x08]*/ unknown_08 = nullptr;
        /*[0x0C]*/ unknown_0C = nullptr;
    }

    eMorpherTarget::~eMorpherTarget()
    {
        /*[0x0C]*/ unknown_0C->decRef();
        /*[0x08]*/ unknown_08->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // eMorpherTarget: cloning the object
    ////////////////////////////////////////////////////////////////

    void eMorpherTarget::createFromOtherObject(const eMorpherTarget &other)
    {
        unknown_08 = nullptr;
        unknown_0C = nullptr;

        throw ErrorMessage
        (
            "CRITICAL ERROR while cloning the \"eMorpherTarget\" object:\n" \
            "cloning << morpher targets >> without context is not supported!!!"
        );
    }

    eMorpherTarget::eMorpherTarget(const eMorpherTarget &other)
    : eRefCounter(other)
    {
        createFromOtherObject(other);
    }

    eMorpherTarget& eMorpherTarget::operator = (const eMorpherTarget &other)
    {
        if ((&other) != this)
        {
            eRefCounter::operator = (other);

            /****************/

            unknown_08->decRef();
            unknown_0C->decRef();

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eMorpherTarget::cloneFromMe() const
    {
        return new eMorpherTarget(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eMorpherTarget: serialization
    // <kao2.0049ECC0>
    ////////////////////////////////////////////////////////////////
    void eMorpherTarget::serialize(Archive &ar)
    {
        /* [0x08] unknown */
        ArFunctions::serialize_e3fXArray(ar, &unknown_08);

        /* [0x0C] unknown */
        ArFunctions::serialize_e3fXArray(ar, &unknown_0C);
    }

}
