#include <kao2engine/eAddNode.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eAddNode interface
    // <kao2.005192E0> (constructor)
    // <kao2.00519350> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_ADDNODE_TYPEINFO
    (
        E_ADDNODE_ID,
        "eAddNode",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eAddNode;
        }
    );

    TypeInfo* eAddNode::getType() const
    {
        return &E_ADDNODE_TYPEINFO;
    }

    eAddNode::eAddNode()
    : Gadget()
    {}

    eAddNode::~eAddNode() {}

}
