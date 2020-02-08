#include <kao2engine/eSphNode.h>
#include <kao2ar/Archive.h>

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

    TypeInfo* eSphNode::getType() const
    {
        return &E_SPHNODE_TYPEINFO;
    }

    eSphNode::eSphNode()
    : eGeometry()
    {
        /*[0x58]*/ radius = 0;

        /*[0x14]*/ flags |= 0x40000000;
    }

    eSphNode::~eSphNode() {}


    ////////////////////////////////////////////////////////////////
    // eSphNode serialization
    // <kao2.004AC320>
    ////////////////////////////////////////////////////////////////
    void eSphNode::serialize(Archive &ar)
    {
        eGeometry::serialize(ar);

        /* [0x58] radius */
        ar.readOrWrite(&radius, 0x04);
    }

}
