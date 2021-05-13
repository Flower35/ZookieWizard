#include <ElephantEngine/eFSSprite.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFSSprite interface
    // <kao2.00553AF0> (constructor)
    // <kao2.00553C00> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_FSSPRITE_TYPEINFO
    (
        E_FSSPRITE_ID,
        "eFSSprite",
        &E_FSOP_TYPEINFO,
        []() -> eObject*
        {
            return new eFSSprite;
        }
    );

    const TypeInfo* eFSSprite::getType() const
    {
        return &E_FSSPRITE_TYPEINFO;
    }

    eFSSprite::eFSSprite()
    : eFSOp()
    {
        name = "fsSprite";
    }

    eFSSprite::~eFSSprite()
    {}


    ////////////////////////////////////////////////////////////////
    // eFSSprite: cloning the object
    ////////////////////////////////////////////////////////////////

    void eFSSprite::createFromOtherObject(const eFSSprite &other)
    {}

    eFSSprite::eFSSprite(const eFSSprite &other)
    : eFSOp(other)
    {
        createFromOtherObject(other);
    }

    eFSSprite& eFSSprite::operator = (const eFSSprite &other)
    {
        if ((&other) != this)
        {
            eFSOp::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eFSSprite::cloneFromMe() const
    {
        return new eFSSprite(*this);
    }


    ////////////////////////////////////////////////////////////////
    // Static Gadget
    ////////////////////////////////////////////////////////////////

    eFSSprite theFSSprite;

}
