#include <kao2engine/eFSSprite.h>
#include <kao2ar/Archive.h>

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

    TypeInfo* eFSSprite::getType() const
    {
        return &E_FSSPRITE_TYPEINFO;
    }

    eFSSprite::eFSSprite()
    : eFSOp()
    {
        name = "fsSprite";
    }

    eFSSprite::~eFSSprite() {}


    ////////////////////////////////////////////////////////////////
    // Static Gadget
    ////////////////////////////////////////////////////////////////

    eFSSprite theFSSprite;

}
