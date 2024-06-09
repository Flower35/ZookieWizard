#include <ElephantEngine/eMultiTransformNode.h>
#include <ElephantBase/Archive.h>
#include <ElephantBase/eDrawContext.h>
#include <ElephantEngine/eMultiTransform.h>

//#include <ElephantEngine/eTrack.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eMultiTransformNode interface
    ////////////////////////////////////////////////////////////////

    extern TypeInfo E_MULTITRANSFORMNODE_TYPEINFO
    (
        E_MULTITRANSFORMNODE_ID,
        "eMultiTransformNode",
        &E_TRANSFORM_TYPEINFO,
        []() -> eObject*
        {
            return new eMultiTransformNode;
        }
    );

    const TypeInfo* eMultiTransformNode::getType() const
    {
        return &E_MULTITRANSFORMNODE_TYPEINFO;
    }

    eMultiTransformNode::eMultiTransformNode()
    : eTransform()
    {
        flags |= 0x00071000;
    }

    eMultiTransformNode::~eMultiTransformNode()
    {}


    ////////////////////////////////////////////////////////////////
    // eMultiTransformNode: cloning the object
    ////////////////////////////////////////////////////////////////

    void eMultiTransformNode::createFromOtherObject(const eMultiTransformNode &other)
    {
        dummy_rotationA[0] = other.dummy_rotationA[0];
        dummy_rotationA[1] = other.dummy_rotationA[1];
        dummy_rotationA[2] = other.dummy_rotationA[2];

        dummy_rotationB[0] = other.dummy_rotationB[0];
        dummy_rotationB[1] = other.dummy_rotationB[1];
        dummy_rotationB[2] = other.dummy_rotationB[2];

        color[0] = other.color[0];
        color[1] = other.color[1];
        color[2] = other.color[2];
        color[3] = other.color[3];
        
        unknown_1C = other.unknown_1C;
        unknown_2C = other.unknown_2C;
    }

    eMultiTransformNode::eMultiTransformNode(const eMultiTransformNode &other)
    : eTransform(other)
    {
        createFromOtherObject(other);
    }

    eMultiTransformNode& eMultiTransformNode::operator = (const eMultiTransformNode&other)
    {
        if ((&other) != this)
        {
            eTransform::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eMultiTransformNode::cloneFromMe() const
    {
        return new eMultiTransformNode(*this);
    }

    void eMultiTransformNode::setupInstance(eMultiTransformBase& transform_base)
    {
        defaultTransform.pos.x = transform_base.position[0];
        defaultTransform.pos.y = transform_base.position[1];
        defaultTransform.pos.z = transform_base.position[2];

        defaultTransform.scale = transform_base.scale;

        defaultTransform.rot.fromEulerAngles(true, transform_base.rotation[0], transform_base.rotation[1], transform_base.rotation[2]);

        color[0] = transform_base.color[0];
        color[1] = transform_base.color[1];
        color[2] = transform_base.color[2];
        color[3] = transform_base.color[3];

        dummy_rotationA[0] = transform_base.dummy_rotationA[0];
        dummy_rotationA[1] = transform_base.dummy_rotationA[1];
        dummy_rotationA[2] = transform_base.dummy_rotationA[2];

        dummy_rotationB[0] = transform_base.dummy_rotationB[0];
        dummy_rotationB[1] = transform_base.dummy_rotationB[1];
        dummy_rotationB[2] = transform_base.dummy_rotationB[2];

        unknown_1C = transform_base.unknown_1C;
        unknown_2C = transform_base.unknown_2C;

        name = "instance";
    }

    void eMultiTransformNode::setupBase(eMultiTransformBase& transform_base)
    {
        transform_base.position[0] = defaultTransform.pos.x;
        transform_base.position[1] = defaultTransform.pos.y;
        transform_base.position[2] = defaultTransform.pos.z;

        transform_base.scale = defaultTransform.scale;

        defaultTransform.rot.toEulerAngles(true, transform_base.rotation[0], transform_base.rotation[1], transform_base.rotation[2]);

        transform_base.color[0] = color[0];
        transform_base.color[1] = color[1];
        transform_base.color[2] = color[2];
        transform_base.color[3] = color[3];

        transform_base.dummy_rotationA[0] = dummy_rotationA[0];
        transform_base.dummy_rotationA[1] = dummy_rotationA[1];
        transform_base.dummy_rotationA[2] = dummy_rotationA[2];

        transform_base.dummy_rotationB[0] = dummy_rotationB[0];
        transform_base.dummy_rotationB[1] = dummy_rotationB[1];
        transform_base.dummy_rotationB[2] = dummy_rotationB[2];

        transform_base.unknown_1C = unknown_1C;
        transform_base.unknown_2C = unknown_2C;
    }


    ////////////////////////////////////////////////////////////////
    // eMultiTransformNode: serialization
    ////////////////////////////////////////////////////////////////
    void eMultiTransformNode::serialize(Archive &ar)
    {
    }


    ////////////////////////////////////////////////////////////////
    // eMultiTransformNode: dump object tree as a JSON value
    ////////////////////////////////////////////////////////////////
    void eMultiTransformNode::dumpTreeAsJsonValue(JsonValue& output, bool dumpChildNodes) const
    {
        /* "eTransform": parent class */

        eTransform::dumpTreeAsJsonValue(output, false);

        JsonObject* jsonObjectRef = (JsonObject *) output.getValue();
    }
}
