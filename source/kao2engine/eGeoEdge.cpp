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
        edges = nullptr;

        flags |= 0x40000000;
    }

    eGeoEdge::~eGeoEdge()
    {
        edges->decRef();
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
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&edges, &E_GEOARRAY_EPOINT4_TYPEINFO);
    }


    ////////////////////////////////////////////////////////////////
    // eGeoEdge: render this node
    ////////////////////////////////////////////////////////////////
    void eGeoEdge::renderNode(eDrawContext &draw_context) const
    {
        if (GUI::drawFlags::DRAW_FLAG_COLLISION & draw_context.getDrawFlags())
        {
            if (nullptr != edges)
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

                ePoint4* vertices = edges->getData();
                int32_t vertex_pairs = edges->getLength() - 1;

                if (nullptr != vertices)
                {
                    int32_t a = 0;

                    while (a < vertex_pairs)
                    {
                        for (int32_t b = 0; b < 2; b++)
                        {
                            glVertex3f(vertices[a].x, vertices[a].y, vertices[a].z);
                            a++;
                        }
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


    ////////////////////////////////////////////////////////////////
    // eGeoEdge: (editor option) find object in 3D space
    ////////////////////////////////////////////////////////////////
    ePoint3 eGeoEdge::editingGetCenterPoint() const
    {
        if (nullptr != edges)
        {
            if (edges->getLength() >= 1)
            {
                return edges->getData()[0];
            }
        }

        return {0, 0, 0};
    }


    ////////////////////////////////////////////////////////////////
    // eGeoEdge: (editor option) rebuild collision
    ////////////////////////////////////////////////////////////////
    void eGeoEdge::editingRebuildCollision()
    {
        eGeometry::editingRebuildCollision();

        flagsCollisionResponse = 0;
    }


    ////////////////////////////////////////////////////////////////
    // eGeoEdge: (editor option) apply new transformation
    ////////////////////////////////////////////////////////////////
    void eGeoEdge::editingApplyNewTransform(eSRP &new_transform, int32_t marked_id)
    {
        int32_t a, edges_length;
        ePoint4* edges_data;
        eMatrix4x4 matrix = new_transform.getMatrix();

        if ((nullptr != edges) && (nullptr != (edges_data = edges->getData())))
        {
            edges_length = edges->getLength();

            for (a = 0; a < edges_length; a++)
            {
                edges_data[a] = matrix * edges_data[a];
            }

            calculateBoundaryBox(boxBoundMin, boxBoundMax, edges_length, edges_data, 0, nullptr);
        }
    }


    ////////////////////////////////////////////////////////////////
    // eGeoEdge: custom TXT parser
    ////////////////////////////////////////////////////////////////
    int32_t eGeoEdge::parsingCustomMessage(char* result_msg, const eString &message, int32_t params_count, const TxtParsingNodeProp* params)
    {
        int32_t test, edges_length;
        ePoint4* edges_data[2];
        float dummy_floats[2][3];

        if (1 != (test = eGeometry::parsingCustomMessage(result_msg, message, params_count, params)))
        {
            return test;
        }

        if (message.compareExact("clearEdges", true))
        {
            if (0 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "clearEdges", 0);
                return 2;
            }

            /********************************/

            if (nullptr != edges)
            {
                edges->setup(0, nullptr);
            }
            else
            {
                edges = new eGeoArray<ePoint4>();
            }

            editingClearCollision();

            return 0;
        }
        if (message.compareExact("addEdge", true))
        {
            if (2 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "addEdge", 2);
                return 2;
            }

            /********************************/

            if (!params[0].checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT3))
            {
                TxtParsingNode_ErrorArgType(result_msg, "addEdge", 1, TXT_PARSING_NODE_PROPTYPE_FLOAT3);
                return 2;
            }

            params[0].getValue(&(dummy_floats[0][0]));

            /********************************/

            if (!params[1].checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT3))
            {
                TxtParsingNode_ErrorArgType(result_msg, "addEdge", 2, TXT_PARSING_NODE_PROPTYPE_FLOAT3);
                return 2;
            }

            params[1].getValue(&(dummy_floats[1][0]));

            /********************************/

            if (nullptr != edges)
            {
                edges_length = edges->getLength();
                edges_data[0] = edges->getData();

                edges_data[1] = new ePoint4 [2 + edges_length];

                for (test = 0; test < edges_length; test++)
                {
                    edges_data[1][test] = edges_data[0][test];
                }
            }
            else
            {
                edges = new eGeoArray<ePoint4>();
                edges->incRef();

                edges_length = 0;
                edges_data[1] = new ePoint4 [2];
            }

            for (test = 0; test < 2; test++)
            {
                edges_data[1][edges_length].x = dummy_floats[test][0];
                edges_data[1][edges_length].y = dummy_floats[test][1];
                edges_data[1][edges_length].z = dummy_floats[test][2];
                edges_data[1][edges_length].w = 1.0f;
                edges_length++;
            }

            edges->setup(edges_length, edges_data[1]);

            /********************************/

            calculateBoundaryBox(boxBoundMin, boxBoundMax, edges_length, edges_data[1], 0, nullptr);

            if (nullptr != axisListBox)
            {
                editingRebuildCollision();
            }

            return 0;
        }

        return 1;
    }

}
