#include <kao2engine/eGeoEdge.h>
#include <kao2ar/Archive.h>
#include <kao2ar/eDrawContext.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eGeoEdge interface
    // <kao2.005ADE30> (constructor)
    // <kao2.005ADF10> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_GEOEDGE_TYPEINFO
    (
        E_GEOEDGE_ID,
        "eGeoEdge",
        &E_GEOMETRY_TYPEINFO,
        []() -> eObject*
        {
            return new eGeoEdge;
        }
    );

    TypeInfo* eGeoEdge::getType() const
    {
        return &E_GEOEDGE_TYPEINFO;
    }

    eGeoEdge::eGeoEdge()
    : eGeometry()
    {
        unknown_58 = nullptr;

        flags |= 0x40000000;
    }

    eGeoEdge::~eGeoEdge()
    {
        unknown_58->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // eGeoEdge serialization
    // <kao2.005AE000>
    ////////////////////////////////////////////////////////////////
    void eGeoEdge::serialize(Archive &ar)
    {
        eGeometry::serialize(ar);

        if (ar.getVersion() < 0x6A)
        {
            throw ErrorMessage
            (
                "eGeoEdge::serialize():\n" \
                "ar.version() 106 required!"
            );
        }

        /* [0x58] unknown */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&unknown_58, &E_GEOARRAY_EPOINT4_TYPEINFO);
    }


    ////////////////////////////////////////////////////////////////
    // eGeoEdge: render this node
    ////////////////////////////////////////////////////////////////
    void eGeoEdge::renderNode(eDrawContext &draw_context) const
    {
        if (GUI::drawFlags::DRAW_FLAG_COLLISION & draw_context.getDrawFlags())
        {
            if (nullptr != unknown_58)
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
                glLineWidth(2.0f);
                glBegin(GL_LINES);

                ePoint4* vertices = unknown_58->getData();
                int32_t vertex_pairs = unknown_58->getLength() - 1;

                if (nullptr != vertices)
                {
                    int32_t a = 0;

                    while (a < vertex_pairs)
                    {
                        glVertex3f(vertices[a].x, vertices[a].y, vertices[a].z);
                        a++;
                        glVertex3f(vertices[a].x, vertices[a].y, vertices[a].z);
                    }
                }

                glEnd();
                glLineWidth(1.0f);
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

}
