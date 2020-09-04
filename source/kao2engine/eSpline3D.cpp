#include <kao2engine/eSpline3D.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSpline3D interface
    // <kao2.004A6A00> (constructor)
    // <kao2.004A6AA0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SPLINE3D_TYPEINFO
    (
        E_SPLINE3D_ID,
        "eSpline3D",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return new eSpline3D;
        }
    );

    TypeInfo* eSpline3D::getType() const
    {
        return &E_SPLINE3D_TYPEINFO;
    }

    eSpline3D::eSpline3D()
    : eRefCounter()
    {
        /*[0x08]*/ verticesCount = 0;
        /*[0x0C]*/ verticesMaxLength = 0;
        /*[0x10]*/ vertices = nullptr;
        /*[0x14]*/ unknown_14 = 0;
    }

    eSpline3D::~eSpline3D()
    {
        if (nullptr != vertices)
        {
            delete[](vertices);
        }
    }


    ////////////////////////////////////////////////////////////////
    // Spline Vertex structure
    // <kao2.09724B48> (serialization)
    ////////////////////////////////////////////////////////////////

    eSplineVertexBase::eSplineVertexBase()
    {}

    void eSplineVertexBase::serializeSplineJoint(Archive &ar)
    {
        /*[0x00-0x20]*/
        position[0].serialize(ar);
        position[1].serialize(ar);
        position[2].serialize(ar);

        /* [0x24] Joint name */
        ar.serializeString(name);
    }


    ////////////////////////////////////////////////////////////////
    // eSpline3D serialization
    // <kao2.004A70B0>
    ////////////////////////////////////////////////////////////////
    void eSpline3D::serialize(Archive &ar)
    {
        int32_t i;

        if (ar.isInReadMode())
        {
            ar.readOrWrite(&verticesMaxLength, 0x04);

            if (nullptr != vertices)
            {
                delete[](vertices);
            }

            vertices = new eSplineVertexBase [verticesMaxLength];

            for (i = 0; i < verticesMaxLength; i++)
            {
                vertices[i].serializeSplineJoint(ar);

                verticesCount = (i+1);
            }
        }
        else
        {
            ar.readOrWrite(&verticesCount, 0x04);

            for (i = 0; i < verticesCount; i++)
            {
                vertices[i].serializeSplineJoint(ar);
            }
        }

        /* [0x14] unknown */
        ar.readOrWrite(&unknown_14, 0x04);
    }


    ////////////////////////////////////////////////////////////////
    // eSpline3D: render spline
    // <kao2.004A7250>
    ////////////////////////////////////////////////////////////////
    void eSpline3D::renderSpline(bool use_outline) const
    {
        ePoint3 vertex;
        float color[3];
        float time_param;

        /********************************/

        glLineWidth(5.0f);
        glBegin(GL_LINE_STRIP);

        if (use_outline)
        {
            GUI::colorOfMarkedObject(color[0], color[1], color[2]);
        }
        else
        {
            color[0] = 1.0f;
            color[1] = 1.0f;
            color[2] = 1.0f;
        }

        /********************************/

        time_param = 0;

        while (time_param <= 1.0f)
        {
            splineGetSegment(vertex, time_param);

            glVertex3f(vertex.x, vertex.y, vertex.z);

            /* 100 steps */
            time_param += 0.01f;
        }

        /********************************/

        glColor3f(1.0f, 1.0f, 1.0f);
        glLineWidth(1.0f);
        glEnd();
    }


    ////////////////////////////////////////////////////////////////
    // eSpline3D: get best matching point
    // <kao2.004A6F00>
    ////////////////////////////////////////////////////////////////
    void eSpline3D::splineGetPoint(ePoint3 &result, float time) const
    {
        result = {0};
        return;
    }


    ////////////////////////////////////////////////////////////////
    // eSpline3D: get exact point from the spline
    // <kao2.004A6C30>
    ////////////////////////////////////////////////////////////////
    void eSpline3D::splineGetSegment(ePoint3 &result, float time) const
    {
        result = {0};
        return;
    }


    ////////////////////////////////////////////////////////////////
    // eSpline3D: clear all vertices
    ////////////////////////////////////////////////////////////////
    void eSpline3D::clearVertices()
    {
        if (nullptr != vertices)
        {
            delete[](vertices);
        }

        verticesCount = 0;
        verticesMaxLength = 0;
    }


    ////////////////////////////////////////////////////////////////
    // eSpline3D: add a new vertex
    ////////////////////////////////////////////////////////////////
    void eSpline3D::addVertex(ePoint3 new_pos_a, ePoint3 new_pos_b, ePoint3 new_pos_c, eString new_name)
    {
        eSplineVertexBase* temp;
        int32_t a;

        if ((verticesCount + 1) > verticesMaxLength)
        {
            verticesMaxLength++;
            temp = new eSplineVertexBase [verticesMaxLength];

            if (nullptr != vertices)
            {
                for (a = 0; a < verticesCount; a++)
                {
                    temp[a] = vertices[a];
                }

                delete[](vertices);
            }

            vertices = temp;
        }

        vertices[verticesCount].position[0] = new_pos_a;
        vertices[verticesCount].position[1] = new_pos_b;
        vertices[verticesCount].position[2] = new_pos_c;
        vertices[verticesCount].name = new_name;

        verticesCount++;
    }


    ////////////////////////////////////////////////////////////////
    // eSpline3D get vertices count
    ////////////////////////////////////////////////////////////////
    int32_t eSpline3D::getVerticesCount() const
    {
        return verticesCount;
    }


    ////////////////////////////////////////////////////////////////
    // eSpline3D: get default position of some vertex
    ////////////////////////////////////////////////////////////////
    ePoint3 eSpline3D::getVertexPosition(int32_t vertex_id, int32_t param_id) const
    {
        if ((nullptr != vertices) && (vertex_id >= 0) && (vertex_id < verticesCount) && (param_id >= 0) && (param_id < 3))
        {
            return vertices[vertex_id].position[param_id];
        }

        return {0};
    }


    ////////////////////////////////////////////////////////////////
    // eSpline3D: set default position of some vertex
    ////////////////////////////////////////////////////////////////
    void eSpline3D::setVertexPosition(int32_t vertex_id, int32_t param_id, ePoint3 new_position)
    {
        if ((nullptr != vertices) && (vertex_id >= 0) && (vertex_id < verticesCount) && (param_id >= 0) && (param_id < 3))
        {
            vertices[vertex_id].position[param_id] = new_position;
        }
    }

}
