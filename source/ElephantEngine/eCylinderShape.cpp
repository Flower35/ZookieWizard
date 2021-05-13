#include <ElephantEngine/eCylinderShape.h>
#include <ElephantBase/Archive.h>

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
            return new eCylinderShape(0, 0);
        }
    );

    TypeInfo* eCylinderShape::getType() const
    {
        return &E_CYLINDERSHAPE_TYPEINFO;
    }

    eCylinderShape::eCylinderShape(float x, float y)
    : ePrimitive()
    {
        unknown_08 = y;
        unknown_0C = x;

        unknown_10 = ePoint4(0, 0, 0, 1.0f);

        unknown_20 = 0;
        unknown_24 = 0;
        unknown_28 = 0;
    }

    eCylinderShape::~eCylinderShape()
    {}


    ////////////////////////////////////////////////////////////////
    // eCylinderShape: cloning the object
    ////////////////////////////////////////////////////////////////

    void eCylinderShape::createFromOtherObject(const eCylinderShape &other)
    {
        unknown_08 = other.unknown_08;
        unknown_0C = other.unknown_0C;

        unknown_10 = other.unknown_10;

        unknown_20 = other.unknown_20;
        unknown_24 = other.unknown_24;
        unknown_28 = other.unknown_28;
    }

    eCylinderShape::eCylinderShape(const eCylinderShape &other)
    : ePrimitive(other)
    {
        createFromOtherObject(other);
    }

    eCylinderShape& eCylinderShape::operator = (const eCylinderShape &other)
    {
        if ((&other) != this)
        {
            ePrimitive::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eCylinderShape::cloneFromMe() const
    {
        return new eCylinderShape(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eCylinderShape: serialization
    // <kao2.004B9960>
    ////////////////////////////////////////////////////////////////
    void eCylinderShape::serialize(Archive &ar)
    {
        ar.readOrWrite(&unknown_20, 0x04);
        ar.readOrWrite(&unknown_24, 0x04);
        ar.readOrWrite(&unknown_28, 0x04);

        unknown_10.serialize(ar);

        ar.readOrWrite(&unknown_0C, 0x04);
        ar.readOrWrite(&unknown_08, 0x04);
    }

}
