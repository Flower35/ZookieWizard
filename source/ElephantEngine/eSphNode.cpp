#include <ElephantEngine/eSphNode.h>
#include <ElephantBase/Archive.h>
#include <ElephantBase/eDrawContext.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSphNode interface
    // <kao2.004AC0C0> (constructor)
    // <kao2.004AC1A0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SPHNODE_TYPEINFO
    (
        E_SPHNODE_ID,
        "eSphNode",
        &E_GEOMETRY_TYPEINFO,
        []() -> eObject*
        {
            return new eSphNode;
        }
    );

    const TypeInfo* eSphNode::getType() const
    {
        return &E_SPHNODE_TYPEINFO;
    }

    eSphNode::eSphNode()
    : eGeometry()
    {
        /*[0x58]*/ radius = 0;

        /*[0x14]*/ flags |= 0x40000000;
    }

    eSphNode::~eSphNode()
    {}


    ////////////////////////////////////////////////////////////////
    // eSphNode: cloning the object
    ////////////////////////////////////////////////////////////////

    void eSphNode::createFromOtherObject(const eSphNode &other)
    {
        radius = other.radius;
    }

    eSphNode::eSphNode(const eSphNode &other)
    : eGeometry(other)
    {
        createFromOtherObject(other);
    }

    eSphNode& eSphNode::operator = (const eSphNode &other)
    {
        if ((&other) != this)
        {
            eGeometry::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eSphNode::cloneFromMe() const
    {
        return new eSphNode(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eSphNode: serialization
    // <kao2.004AC320>
    ////////////////////////////////////////////////////////////////
    void eSphNode::serialize(Archive &ar)
    {
        eGeometry::serialize(ar);

        /* [0x58] radius */
        ar.readOrWrite(&radius, 0x04);
    }


    ////////////////////////////////////////////////////////////////
    // eSphNode: render this node
    ////////////////////////////////////////////////////////////////
    void eSphNode::renderNode(eDrawContext &draw_context) const
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
                gluSphere(quadric, radius, 36, 36);
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
    // eSphNode: (editor option) rebuild collision
    ////////////////////////////////////////////////////////////////
    void eSphNode::editingRebuildCollision()
    {
        eGeometry::editingRebuildCollision();

        flagsCollisionResponse = 0;
    }


    ////////////////////////////////////////////////////////////////
    // eSphNode: custom TXT parser methods
    ////////////////////////////////////////////////////////////////

    int32_t eSphNode::parsingSetProperty(char* result_msg, const TxtParsingNodeProp &property)
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
            boxBoundMin.z = (-radius);
            boxBoundMax.x = radius;
            boxBoundMax.y = radius;
            boxBoundMax.z = radius;

            return 0;
        }

        return 1;
    }

    int32_t eSphNode::parsingCustomMessage(char* result_msg, const eString &message, int32_t params_count, const TxtParsingNodeProp* params)
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
            boxBoundMin.z = (-radius);
            boxBoundMax.x = radius;
            boxBoundMax.y = radius;
            boxBoundMax.z = radius;

            if (nullptr != axisListBox)
            {
                editingRebuildCollision();
            }

            return 0;
        }

        return 1;
    }

}
