#include <kao2engine/eBezierSplineNode.h>
#include <kao2ar/Archive.h>
#include <kao2ar/eDrawContext.h>

#include <kao2engine/eSpline3D.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eBezierSplineNode interface
    // <kao2.004A7EB0> (constructor)
    // <kao2.004A7F10> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_BEZIERSPLINENODE_TYPEINFO
    (
        E_BEZIERSPLINENODE_ID,
        "eBezierSplineNode",
        &E_NODE_TYPEINFO,
        []() -> eObject*
        {
            return new eBezierSplineNode;
        }
    );

    TypeInfo* eBezierSplineNode::getType() const
    {
        return &E_BEZIERSPLINENODE_TYPEINFO;
    }

    eBezierSplineNode::eBezierSplineNode()
    : eNode()
    {
        spline = nullptr;

        /*[0x1C]*/ flags |= 0x40000000;
    }

    eBezierSplineNode::~eBezierSplineNode()
    {
        spline->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // eBezierSplineNode: cloning the object
    ////////////////////////////////////////////////////////////////

    void eBezierSplineNode::createFromOtherObject(const eBezierSplineNode &other)
    {
        if (nullptr != other.spline)
        {
            spline = new eSpline3D(*(other.spline));
            spline->incRef();
        }
        else
        {
            spline = nullptr;
        }
    }

    eBezierSplineNode::eBezierSplineNode(const eBezierSplineNode &other)
    : eNode(other)
    {
        createFromOtherObject(other);
    }

    eBezierSplineNode& eBezierSplineNode::operator = (const eBezierSplineNode &other)
    {
        if ((&other) != this)
        {
            eNode::operator = (other);

            /****************/

            spline->decRef();

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eBezierSplineNode::cloneFromMe() const
    {
        return new eBezierSplineNode(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eBezierSplineNode: serialization
    // <kao2.004A86C0>
    ////////////////////////////////////////////////////////////////
    void eBezierSplineNode::serialize(Archive &ar)
    {
        int32_t a, b;
        eSpline3D* dummy_spline;

        /********************************/

        eNode::serialize(ar);

        /********************************/

        b = (nullptr != spline) ? 0x01 : 0x00;
        ar.readOrWrite(&b, 0x04);

        for (a = 0; a < b; a++)
        {
            if (0 == a)
            {
                ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&spline, &E_SPLINE3D_TYPEINFO);
            }
            else
            {
                ar.serialize((eObject**)&dummy_spline, &E_SPLINE3D_TYPEINFO);

                if ((nullptr != spline) && (nullptr != dummy_spline))
                {
                    spline->appendVerticesFromSpline(*dummy_spline);

                    delete (dummy_spline);
                }
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eBezierSplineNode: render this node
    ////////////////////////////////////////////////////////////////
    void eBezierSplineNode::renderNode(eDrawContext &draw_context) const
    {
        if (GUI::drawFlags::DRAW_FLAG_SPECIAL & draw_context.getDrawFlags())
        {
            if (nullptr != spline)
            {
                bool is_selected_or_marked = draw_context.isNodeSelectedOrMarked();

                draw_context.useMaterial(nullptr, 0);

                if (is_selected_or_marked)
                {
                    glPushMatrix();
                    GUI::multiplyBySelectedObjectTransform(false);
                }

                spline->renderSpline(draw_context.isNodeOutlined());

                if (is_selected_or_marked)
                {
                    glPopMatrix();
                }
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eBezierSplineNode: (editor option) find object in 3D space
    ////////////////////////////////////////////////////////////////
    ePoint3 eBezierSplineNode::editingGetCenterPoint() const
    {
        if (nullptr != spline)
        {
            return spline->getVertexPosition(0, 0);
        }

        return {0};
    }


    ////////////////////////////////////////////////////////////////
    // eBezierSplineNode: (editor option) apply new transformation
    ////////////////////////////////////////////////////////////////
    void eBezierSplineNode::editingApplyNewTransform(eSRP &new_transform, int32_t marked_id)
    {
        int32_t a, b, length;
        ePoint4 dummy_vertex;
        eMatrix4x4 matrix = new_transform.getMatrix();

        if (nullptr != spline)
        {
            length = spline->getVerticesCount();

            for (b = 0; b < 3; b++)
            {
                for (a = 0; a < length; a++)
                {
                    dummy_vertex = spline->getVertexPosition(a, b);
                    dummy_vertex.w = 1.0f;

                    spline->setVertexPosition(a, b, (matrix * dummy_vertex));
                }
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eBezierSplineNode: custom TXT parser
    ////////////////////////////////////////////////////////////////
    int32_t eBezierSplineNode::parsingCustomMessage(char* result_msg, const eString &message, int32_t params_count, const TxtParsingNodeProp* params)
    {
        int32_t test;
        float dummy_floats[3];
        ePoint3 dummy_pos[3];
        eString dummy_str;

        if (1 != (test = eNode::parsingCustomMessage(result_msg, message, params_count, params)))
        {
            return test;
        }

        if (message.compareExact("clearVertices", true))
        {
            if (0 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "clearVertices", 0);
                return 2;
            }

            /********************************/

            if (nullptr != spline)
            {
                spline->clearVertices();
            }

            return 0;
        }
        else if (message.compareExact("addVertex", true))
        {
            if (4 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "addVertex", 4);
                return 2;
            }

            /********************************/

            for (test = 0; test < 3; test++)
            {
                if (!params[test].checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT3))
                {
                    TxtParsingNode_ErrorArgType(result_msg, "addVertex", (1 + test), TXT_PARSING_NODE_PROPTYPE_FLOAT3);
                    return 2;
                }

                params[test].getValue(dummy_floats);

                dummy_pos[test].x = dummy_floats[0];
                dummy_pos[test].y = dummy_floats[1];
                dummy_pos[test].z = dummy_floats[2];
            }

            /********************************/

            if (!params[3].checkType(TXT_PARSING_NODE_PROPTYPE_STRING))
            {
                TxtParsingNode_ErrorArgType(result_msg, "addVertex", 4, TXT_PARSING_NODE_PROPTYPE_STRING);
                return 2;
            }

            params[3].getValue(&dummy_str);

            /********************************/

            if (nullptr == spline)
            {
                spline = new eSpline3D();
            }

            spline->addVertex(dummy_pos[0], dummy_pos[1], dummy_pos[2], dummy_str);

            return 0;
        }

        return 1;
    }


    ////////////////////////////////////////////////////////////////
    // eBezierSplineNode: get point from the spline
    // without rendering (used with "ePathConstrainCtrl")
    // <kao2.004A7630>
    ////////////////////////////////////////////////////////////////
    void eBezierSplineNode::bezierSplineGetSegment(ePoint3 &result, float time) const
    {
        if (nullptr != spline)
        {
            spline->splineGetSegment(result, time);
            return;
        }

        result = {0};
    }

}
