#include <ElephantEngine/eSpeaking.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSpeaking interface
    // <kao2.004578D0> (constructor)
    // <kao2.00457960> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SPEAKING_TYPEINFO
    (
        E_SPEAKING_ID,
        "eSpeaking",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eSpeaking;
        }
    );

    const TypeInfo* eSpeaking::getType() const
    {
        return &E_SPEAKING_TYPEINFO;
    }

    eSpeaking::eSpeaking()
    : Gadget()
    {}

    eSpeaking::~eSpeaking()
    {}


    ////////////////////////////////////////////////////////////////
    // eSpeaking: cloning the object
    ////////////////////////////////////////////////////////////////

    void eSpeaking::createFromOtherObject(const eSpeaking &other)
    {}

    eSpeaking::eSpeaking(const eSpeaking &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eSpeaking& eSpeaking::operator = (const eSpeaking &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eSpeaking::cloneFromMe() const
    {
        return new eSpeaking(*this);
    }

}
