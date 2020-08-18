#include <kao2engine/eCylNode.h>
#include <kao2ar/Archive.h>
#include <kao2ar/eDrawContext.h>

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

    eCylNode::~eCylNode() {}


    ////////////////////////////////////////////////////////////////
    // eCylNode serialization
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

            bool was_texturing_enabled = glIsEnabled(GL_TEXTURE_2D);
            glDisable(GL_TEXTURE_2D);
            bool was_blending_enabled = glIsEnabled(GL_BLEND);
            glDisable(GL_BLEND);

            glColor3f(color[0], color[1], color[2]);

            GLUquadric* quadric = gluNewQuadric();

            if (nullptr != quadric)
            {
                gluQuadricDrawStyle(quadric, GLU_LINE);
                gluCylinder(quadric, radius, radius, height, 18, 15);
                gluDeleteQuadric(quadric);
            }

            glColor3f(1.0f, 1.0f, 1.0f);

            if (was_texturing_enabled)
            {
                glEnable(GL_TEXTURE_2D);
            }

            if (was_blending_enabled)
            {
                glEnable(GL_BLEND);
            }

            /********************************/

            if (is_selected_or_marked)
            {
                glPopMatrix();
            }
        }
    }

}
