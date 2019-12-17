#include <kao2engine/eBezierSplineNode.h>
#include <kao2ar/Archive.h>

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

    TypeInfo* eBezierSplineNode::getType()
    {
        return &E_BEZIERSPLINENODE_TYPEINFO;
    }

    eBezierSplineNode::eBezierSplineNode()
    : eNode()
    {}

    eBezierSplineNode::~eBezierSplineNode() {}


    ////////////////////////////////////////////////////////////////
    // eBezierSplineNode serialization
    // <kao2.004A86C0>
    ////////////////////////////////////////////////////////////////
    void eBezierSplineNode::serialize(Archive &ar)
    {
        eNode::serialize(ar);

        /* Splines group */
        splines.serialize(ar, &E_SPLINE3D_TYPEINFO);
    }

}
