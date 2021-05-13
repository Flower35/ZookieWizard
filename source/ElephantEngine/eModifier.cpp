#include <ElephantEngine/eModifier.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eModifier interface
    ////////////////////////////////////////////////////////////////

    TypeInfo E_MODIFIER_TYPEINFO
    (
        E_MODIFIER_ID,
        "eModifier",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return nullptr;
        }
    );

    TypeInfo* eModifier::getType() const
    {
        return &E_MODIFIER_TYPEINFO;
    }

    eModifier::eModifier()
    : eRefCounter()
    {}

    eModifier::~eModifier()
    {}


    ////////////////////////////////////////////////////////////////
    // eModifier: cloning the object
    ////////////////////////////////////////////////////////////////

    void eModifier::createFromOtherObject(const eModifier &other)
    {}

    eModifier::eModifier(const eModifier &other)
    : eRefCounter(other)
    {
        createFromOtherObject(other);
    }

    eModifier& eModifier::operator = (const eModifier &other)
    {
        if ((&other) != this)
        {
            eRefCounter::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eModifier::cloneFromMe() const
    {
        return nullptr;
    }

}
