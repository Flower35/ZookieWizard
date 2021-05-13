#include <ElephantEngine/NodeRef.h>
#include <ElephantBase/Archive.h>

#include <ElephantEngine/eNode.h>

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

    const TypeInfo* NodeRef::getType() const
    {
        return &E_NODEREF_TYPEINFO;
    }

    NodeRef::NodeRef()
    : eRefCounter()
    {
        nodeType = nullptr;
        node = nullptr;
    }

    NodeRef::~NodeRef()
    {
        node->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // NodeRef: cloning the object
    ////////////////////////////////////////////////////////////////

    void NodeRef::createFromOtherObject(const NodeRef &other)
    {
        name = other.name;
        nodeName = other.nodeName;
        nodeType = other.nodeType;

        node = other.node;
        if (nullptr != node)
        {
            node->incRef();
        }

        unknown_new_id = other.unknown_new_id;
    }

    NodeRef::NodeRef(const NodeRef &other)
    : eRefCounter(other)
    {
        createFromOtherObject(other);
    }

    NodeRef& NodeRef::operator = (const NodeRef &other)
    {
        if ((&other) != this)
        {
            eRefCounter::operator = (other);

            /****************/

            node->decRef();

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* NodeRef::cloneFromMe() const
    {
        return new NodeRef(*this);
    }


    ////////////////////////////////////////////////////////////////
    // NodeRef: serialization
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

        /* ASSERTION */
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
            ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&node, nodeType);
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
    eString NodeRef::getStringRepresentation() const
    {
        return name;
    }


    ////////////////////////////////////////////////////////////////
    // NodeRef: get script representation
    ////////////////////////////////////////////////////////////////
    eString NodeRef::generateScriptText() const
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


    ////////////////////////////////////////////////////////////////
    // NodeRef: get linked node
    ////////////////////////////////////////////////////////////////
    eNode* NodeRef::getLinkedNode() const
    {
        return node;
    }

}
