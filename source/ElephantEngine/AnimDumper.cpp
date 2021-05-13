#include <ElephantEngine/AnimDumper.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // AnimDumper interface
    // <kao2.005AF7C2> (constructor)
    // <kao2.005AFE70> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_ANIMDUMPER_TYPEINFO
    (
        E_ANIMDUMPER_ID,
        "AnimDumper",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new AnimDumper;
        }
    );

    const TypeInfo* AnimDumper::getType() const
    {
        return &E_ANIMDUMPER_TYPEINFO;
    }

    AnimDumper::AnimDumper()
    : Gadget()
    {}

    AnimDumper::~AnimDumper()
    {}


    ////////////////////////////////////////////////////////////////
    // AnimDumper: cloning the object
    ////////////////////////////////////////////////////////////////

    void AnimDumper::createFromOtherObject(const AnimDumper &other)
    {}

    AnimDumper::AnimDumper(const AnimDumper &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    AnimDumper& AnimDumper::operator = (const AnimDumper &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* AnimDumper::cloneFromMe() const
    {
        return new AnimDumper(*this);
    }

}
