#include <kao2engine/eCylNode.h>
#include <kao2ar/Archive.h>

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

    TypeInfo* eCylNode::getType()
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

}
