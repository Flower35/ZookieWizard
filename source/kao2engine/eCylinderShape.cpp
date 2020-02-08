#include <kao2engine/eCylinderShape.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCylinderShape interface
    // <kao2.004B9813> (constructor)
    // <kao2.004B9950> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_CYLINDERSHAPE_TYPEINFO
    (
        E_CYLINDERSHAPE_ID,
        "eCylinderShape",
        &E_PRIMITIVE_TYPEINFO,
        []() -> eObject*
        {
            return new eCylinderShape;
        }
    );

    TypeInfo* eCylinderShape::getType() const
    {
        return &E_CYLINDERSHAPE_TYPEINFO;
    }

    eCylinderShape::eCylinderShape()
    : ePrimitive()
    {
        /* (...) */
    }

    eCylinderShape::~eCylinderShape() {}


    ////////////////////////////////////////////////////////////////
    // eCylinderShape serialization
    // <kao2.004B9960>
    ////////////////////////////////////////////////////////////////
    void eCylinderShape::serialize(Archive &ar)
    {
        throw ErrorMessage
        (
            "eCylinderShape::serialize():\n" \
            "This object is not supported yet !!!"
        );

        /* read [0x20] [0x24] [0x28] */

        /* read [0x10] [0x14] [0x18] [0x1C] */

        /* read [0x0C] */

        /* read [0x08] */
    }

}
