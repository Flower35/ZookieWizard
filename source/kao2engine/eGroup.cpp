#include <kao2engine/eGroup.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eGroup interface
    // <kao2.00482C80> (overloaded constructor)
    // <kao2.00482BE0> (constructor)
    // <kao2.00482D80> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_GROUP_TYPEINFO
    (
        E_GROUP_ID,
        "eGroup",
        &E_NODE_TYPEINFO,
        []() -> eObject*
        {
            return new eGroup;
        }
    );

    TypeInfo* eGroup::getType()
    {
        return &E_GROUP_TYPEINFO;
    }

    eGroup::eGroup(eString s, eNode* x)
    : eNode(s, x)
    {}

    eGroup::eGroup()
    : eNode()
    {}

    eGroup::~eGroup() {}


    ////////////////////////////////////////////////////////////////
    // eGroup serialization
    // <kao2.004835F0>
    ////////////////////////////////////////////////////////////////
    void eGroup::serialize(Archive &ar)
    {
        eNode::serialize(ar);

        nodes.serialize(ar, &E_NODE_TYPEINFO);
    }


    ////////////////////////////////////////////////////////////////
    // eGroup: get i-th node
    ////////////////////////////////////////////////////////////////
    eNode* eGroup::getIthChild(int32_t i)
    {
        return (eNode*)nodes.getIthChild(i);
    }


    ////////////////////////////////////////////////////////////////
    // eGroup: append new node
    ////////////////////////////////////////////////////////////////
    void eGroup::appendChild(eNode* o)
    {
        eGroup* previous_parent;

        if (nullptr != o)
        {
            previous_parent = (eGroup*)o->getParentNode();

            if (nullptr != previous_parent)
            {
                if (previous_parent->getType()->checkHierarchy(&E_GROUP_TYPEINFO))
                {
                    previous_parent->findAndDeleteChild(o);
                }
            }

            nodes.appendChild(o);

            o->setParentNode(this);
        }
    }


    ////////////////////////////////////////////////////////////////
    // eGroup: delete i-th node
    ////////////////////////////////////////////////////////////////
    void eGroup::deleteIthChild(int32_t i)
    {
        nodes.deleteIthChild(i);
    }


    ////////////////////////////////////////////////////////////////
    // eGroup: delete specific node
    ////////////////////////////////////////////////////////////////
    void eGroup::findAndDeleteChild(eNode* o)
    {
        nodes.findAndDeleteChild(o);
    }


    ////////////////////////////////////////////////////////////////
    // eGroup: render each child node
    ////////////////////////////////////////////////////////////////
    void eGroup::renderObject(float time, int32_t draw_flags)
    {
        int32_t i;
        eNode* test_node;

        for (i = 0; i < nodes.getSize(); i++)
        {
            test_node = (eNode*)nodes.getIthChild(i);

            if (nullptr != test_node)
            {
                test_node->renderObject(time, draw_flags);
            }
        }
    }
    

    ////////////////////////////////////////////////////////////////
    // eGroup: export readable structure
    ////////////////////////////////////////////////////////////////
    void eGroup::writeStructureToTextFile(FileOperator &file, int32_t indentation)
    {
        int32_t i;
        eNode* test_node;

        eNode::writeStructureToTextFile(file, indentation);

        for (i = 0; i < nodes.getSize(); i++)
        {
            test_node = (eNode*)nodes.getIthChild(i);

            if (nullptr != test_node)
            {
                test_node->writeStructureToTextFile(file, (indentation + 1));
            }
        }
    }

}
