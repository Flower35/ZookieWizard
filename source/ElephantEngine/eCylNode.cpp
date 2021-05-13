#include <ElephantEngine/eCylNode.h>
#include <ElephantBase/Archive.h>
#include <ElephantBase/eDrawContext.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCylNode interface
    // <kao2.004ABB50> (constructor)
    // <kao2.004ABC30> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_CYLNODE_TYPEINFO
    (
        E_CYLNODE_ID,
        "eCylNode",
        &E_GEOMETRY_TYPEINFO,
        []() -> eObject*
        {
            return new eCylNode;
        }
    );

    TypeInfo* eCylNode::getType() const
    {
        return &E_CYLNODE_TYPEINFO;
    }

    eCylNode::eCylNode()
    : eGeometry()
    {
        /*[0x58]*/ radius = 0;
        /*[0x5C]*/ height = 0;

        /*[0x14]*/ flags |= 0x40000000;
    }

    eCylNode::~eCylNode()
    {}


    ////////////////////////////////////////////////////////////////
    // eCylNode: cloning the object
    ////////////////////////////////////////////////////////////////

    void eCylNode::createFromOtherObject(const eCylNode &other)
    {
        radius = other.radius;
        height = other.height;
    }

    eCylNode::eCylNode(const eCylNode &other)
    : eGeometry(other)
    {
        createFromOtherObject(other);
    }

    eCylNode& eCylNode::operator = (const eCylNode &other)
    {
        if ((&other) != this)
        {
            eGeometry::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eCylNode::cloneFromMe() const
    {
        return new eCylNode(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eCylNode: serialization
    // <kao2.004ABE00>
    ////////////////////////////////////////////////////////////////
    void eCylNode::serialize(Archive &ar)
    {
        eGeometry::serialize(ar);

        /* [0x58] radius */
        ar.readOrWrite(&radius, 0x04);

        /* [0x5C] height */
        ar.readOrWrite(&height, 0x04);
    }


    ////////////////////////////////////////////////////////////////
    // eCylNode: render this node
    ////////////////////////////////////////////////////////////////
    void eCylNode::renderNode(eDrawContext &draw_context) const
    {
        if (GUI::drawFlags::DRAW_FLAG_COLLISION & draw_context.getDrawFlags())
        {
            /* Inactive color (orange) */
            float color[3] = {1.0f, 0.5f, 0};

            bool is_selected_or_marked = draw_context.isNodeSelectedOrMarked();

            if (is_selected_or_marked)
            {
                glPushMatrix();
                GUI::multiplyBySelectedObjectTransform(false);
            }

            if (draw_context.isNodeOutlined())
            {
                GUI::colorOfMarkedObject(color[0], color[1], color[2]);
            }

            /********************************/

            draw_context.useMaterial(nullptr, 0);

            glColor3f(color[0], color[1], color[2]);

            GLUquadric* quadric = gluNewQuadric();

            if (nullptr != quadric)
            {
                gluQuadricDrawStyle(quadric, GLU_LINE);
                gluCylinder(quadric, radius, radius, height, 18, 15);
                gluDeleteQuadric(quadric);
            }

            glColor3f(1.0f, 1.0f, 1.0f);

            /********************************/

            if (is_selected_or_marked)
            {
                glPopMatrix();
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eCylNode: (editor option) rebuild collision
    ////////////////////////////////////////////////////////////////
    void eCylNode::editingRebuildCollision()
    {
        eGeometry::editingRebuildCollision();

        flagsCollisionResponse = 0;
    }


    ////////////////////////////////////////////////////////////////
    // eCylNode: custom TXT parser methods
    ////////////////////////////////////////////////////////////////

    int32_t eCylNode::parsingSetProperty(char* result_msg, const TxtParsingNodeProp &property)
    {
        int32_t test;
        eString prop_name;

        if (1 != (test = eGeometry::parsingSetProperty(result_msg, property)))
        {
            return test;
        }

        prop_name = property.getName();

        if (prop_name.compareExact("radius", true))
        {
            if (property.checkType(TXT_PARSING_NODE_PROPTYPE_INTEGER))
            {
                property.getValue(&test);
                radius = (float)test;
            }
            else if (property.checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT1))
            {
                property.getValue(&radius);
            }
            else
            {
                TxtParsingNode_ErrorPropType(result_msg, "radius", TXT_PARSING_NODE_PROPTYPE_FLOAT1);
                return 2;
            }

            /********************************/

            if (radius < 0)
            {
                radius = 0;
            }

            boxBoundMin.x = (-radius);
            boxBoundMin.y = (-radius);
            boxBoundMax.x = radius;
            boxBoundMax.y = radius;

            return 0;
        }
        else if (prop_name.compareExact("height", true))
        {
            if (property.checkType(TXT_PARSING_NODE_PROPTYPE_INTEGER))
            {
                property.getValue(&test);
                height = (float)test;
            }
            else if (property.checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT1))
            {
                property.getValue(&height);
            }
            else
            {
                TxtParsingNode_ErrorPropType(result_msg, "height", TXT_PARSING_NODE_PROPTYPE_FLOAT1);
                return 2;
            }

            /********************************/

            if (height < 0)
            {
                height = 0;
            }

            boxBoundMin.z = (-height);
            boxBoundMax.z = height;

            return 0;
        }

        return 1;
    }

    int32_t eCylNode::parsingCustomMessage(char* result_msg, const eString &message, int32_t params_count, const TxtParsingNodeProp* params)
    {
        int32_t test;

        if (1 != (test = eGeometry::parsingCustomMessage(result_msg, message, params_count, params)))
        {
            return test;
        }

        if (message.compareExact("setRadius", true))
        {
            if (1 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "setRadius", 1);
                return 2;
            }

            /********************************/

            if (params[0].checkType(TXT_PARSING_NODE_PROPTYPE_INTEGER))
            {
                params[0].getValue(&test);
                radius = (float)test;
            }
            else if (params[0].checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT1))
            {
                params[0].getValue(&radius);
            }
            else
            {
                TxtParsingNode_ErrorArgType(result_msg, "setRadius", 0, TXT_PARSING_NODE_PROPTYPE_FLOAT1);
                return 2;
            }

            /********************************/

            if (radius < 0)
            {
                radius = 0;
            }

            boxBoundMin.x = (-radius);
            boxBoundMin.y = (-radius);
            boxBoundMax.x = radius;
            boxBoundMax.y = radius;

            if (nullptr != axisListBox)
            {
                editingRebuildCollision();
            }

            return 0;
        }
        else if (message.compareExact("setHeight", true))
        {
            if (1 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "setHeight", 1);
                return 2;
            }

            /********************************/

            if (params[0].checkType(TXT_PARSING_NODE_PROPTYPE_INTEGER))
            {
                params[0].getValue(&test);
                height = (float)test;
            }
            else if (params[0].checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT1))
            {
                params[0].getValue(&height);
            }
            else
            {
                TxtParsingNode_ErrorArgType(result_msg, "setHeight", 0, TXT_PARSING_NODE_PROPTYPE_FLOAT1);
                return 2;
            }

            /********************************/

            if (height < 0)
            {
                height = 0;
            }

            boxBoundMin.z = (-height);
            boxBoundMax.z = height;

            if (nullptr != axisListBox)
            {
                editingRebuildCollision();
            }

            return 0;
        }

        return 1;
    }

}
