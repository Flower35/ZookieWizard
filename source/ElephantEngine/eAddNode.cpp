#include <ElephantEngine/eAddNode.h>
#include <ElephantBase/Archive.h>

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

    const TypeInfo* eAddNode::getType() const
    {
        return &E_ADDNODE_TYPEINFO;
    }

    eAddNode::eAddNode()
    : Gadget()
    {}

    eAddNode::~eAddNode()
    {}


    ////////////////////////////////////////////////////////////////
    // eAddNode: cloning the object
    ////////////////////////////////////////////////////////////////

    void eAddNode::createFromOtherObject(const eAddNode &other)
    {}

    eAddNode::eAddNode(const eAddNode &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eAddNode& eAddNode::operator = (const eAddNode &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eAddNode::cloneFromMe() const
    {
        return new eAddNode(*this);
    }

}
