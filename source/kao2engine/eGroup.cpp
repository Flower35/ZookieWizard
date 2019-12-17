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

}
