#include <kao2engine/NodeRef.h>
#include <kao2ar/Archive.h>

#include <kao2engine/eNode.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // NodeRef interface
    // <kao2.005A0290> (constructor)
    // <kao2.005A0380> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_NODEREF_TYPEINFO
    (
        E_NODEREF_ID,
        "NodeRef",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return new NodeRef;
        }
    );

    TypeInfo* NodeRef::getType()
    {
        return &E_NODEREF_TYPEINFO;
    }

    NodeRef::NodeRef()
    : eRefCounter()
    {
        nodeType = nullptr;
        node = nullptr;
    }

    NodeRef::~NodeRef() {}


    ////////////////////////////////////////////////////////////////
    // NodeRef serialization
    // <kao2.005A0750>
    ////////////////////////////////////////////////////////////////
    void NodeRef::serialize(Archive &ar)
    {
        /* [0x08] reference name */
        ar.serializeString(name);

        if (ar.getVersion() <= 0x88)
        {
            /* [0x0C] node name in scene */
            ar.serializeString(nodeName);
        }
        
        /* [0x10/0x0C] object type */
        ar.checkTypeInfo(&nodeType);

        /* Sanity check */
        if (nullptr != nodeType)
        {
            if (false == nodeType->checkHierarchy(&E_NODE_TYPEINFO))
            {
                throw ErrorMessage
                (
                    "NodeRef::serialize():\n" \
                    "Class %s is not eNode or its child.",
                    nodeType->name
                );
            }
        }

        if (ar.getVersion() <= 0x88)
        {
            /* [0x14] actual object link */
            ar.serialize((eObject**)&node, nodeType);
        }
        else if (ar.getVersion() >= 0x89)
        {
            /* unknown id */
            ar.readOrWrite(&unknown_new_id, 0x04);
        }
    }


    ////////////////////////////////////////////////////////////////
    // NodeRef: get textual representation
    ////////////////////////////////////////////////////////////////
    eString NodeRef::getStringRepresentation()
    {
        return name;
    }


    ////////////////////////////////////////////////////////////////
    // NodeRef: get script representation
    ////////////////////////////////////////////////////////////////
    eString NodeRef::generateScriptText()
    {
        eString result;

        result += "node ";

        if (nullptr != nodeType)
        {
            result += nodeType->name;
        }
        else
        {
            result += "< UNKNOWN_TYPE >";
        }

        result += " ";
        result += name;
        result += " (\"";
        result += nodeName;
        result += "\")";

        return result;
    }

}
