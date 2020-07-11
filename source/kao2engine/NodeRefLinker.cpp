#include <kao2engine/NodeRefLinker.h>
#include <kao2ar/Archive.h>

#include <kao2engine/eNode.h>
#include <kao2engine/eGroup.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // NodeRefLinker interface
    // <kao2.005A0211> (constructor)
    // <kao2.005A0380> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_NODEREFLINKER_TYPEINFO
    (
        E_NODEREFLINKER_ID,
        "NodeRefLinker",
        &E_OBJECT_TYPEINFO,
        []() -> eObject*
        {
            return new NodeRefLinker;
        }
    );

    TypeInfo* NodeRefLinker::getType() const
    {
        return &E_NODEREFLINKER_TYPEINFO;
    }

    NodeRefLinker::NodeRefLinker()
    : eObject()
    {
        linkType = nullptr;
    }

    NodeRefLinker::~NodeRefLinker() {}


    ////////////////////////////////////////////////////////////////
    // NodeRefLinker: error message
    // <kao2.0059FF10>
    ////////////////////////////////////////////////////////////////
    void NodeRefLinker::throwErrorMessage(const char* reason) const
    {
        char bufor[512];
        eString type_name = (nullptr != linkType) ? linkType->name : "???";

        reason = (nullptr == reason) ? "node not found" : reason;

        sprintf_s
        (
            bufor, 512,
            "NodeRefLinker:\nFailed to link: %s %s(\"%s\").\n\nreason: %s.",
            type_name.getText(),
            passedName.getText(),
            passedMask.getText(),
            reason
        );

        throw ErrorMessage(bufor);
    }


    ////////////////////////////////////////////////////////////////
    // NodeRefLinker: find node by comparing a specific format string
    // <kao2.0059F900> <kao2.0059F970>
    ////////////////////////////////////////////////////////////////
    eNode* NodeRefLinker::findLinkByFormat(eNode* node, eString mask) const
    {
        bool has_slash;
        int slash_position, length;
        char* test_txt;

        eNode* test_node[2];
        eGroup* test_group;

        eString node_name;
        eString test_names[2];

        TypeInfo* test_typeinfo;

        if (nullptr == node)
        {
            return nullptr;
        }

        while (1)
        {
            if (mask.compareExact(".", true))
            {
                if (node->getType()->checkHierarchy(linkType))
                {
                    return node;
                }

                throwErrorMessage((eString("node is not a ") + linkType->name).getText());

                return nullptr;
            }
            else if (mask.compareExact("..", true) || mask.compareExact("../", true))
            {
                node = node->getParentNode();

                if (nullptr == node)
                {
                    throwErrorMessage("no parent found");

                    return nullptr;
                }

                if (node->getType()->checkHierarchy(linkType))
                {
                    return node;
                }

                throwErrorMessage((eString("parent is not a ") + linkType->name).getText());

                return nullptr;
            }
            else if (mask.compareExact("..*"))
            {
                throwErrorMessage("confused with '..*'");

                return nullptr;
            }
            else if (mask.compare("../", 0, 3, true))
            {
                mask =  mask.getSubstring(3);

                node = node->getParentNode();

                if (nullptr == node)
                {
                    throwErrorMessage("no parent found");

                    return nullptr;
                }

                /* Continue with this parent node */
            }
            else if (mask.compare("/", 0, 1, true))
            {
                throwErrorMessage("confused with '/'");

                return nullptr;
            }
            else if (mask.compare("*/*/", 0, 4, true))
            {
                throwErrorMessage("confused with '*/*/'");

                return nullptr;
            }
            else if (mask.compare("*/", 0, 2, true))
            {
                test_names[0] = mask.getSubstring(2);

                test_node[0] = findLinkByFormat(node, test_names[0]);

                if (nullptr != test_node[0])
                {
                    return test_node[0];
                }

                if (node->getType()->checkHierarchy(&E_GROUP_TYPEINFO))
                {
                    test_group = (eGroup*)node;

                    for (int i = 0; i < test_group->getNodesCount(); i++)
                    {
                        test_node[0] = test_group->getIthChild(i);

                        test_node[0] = findLinkByFormat(test_node[0], mask);

                        if (nullptr != test_node[0])
                        {
                            return test_node[0];
                        }
                    }

                    return nullptr;
                }

                return nullptr;
            }
            else
            {
                slash_position = (-1);
                test_txt = mask.getText();
                length = mask.getLength();

                for (int a = 0; (slash_position < 0) && (a < length); a++)
                {
                    if ('/' == test_txt[a])
                    {
                        slash_position = a;
                    }
                }

                has_slash = (slash_position >= 0);

                if (has_slash)
                {
                    test_names[0] = mask.getSubstring(0, slash_position);
                    test_names[1] = mask.getSubstring(slash_position + 1);

                    test_typeinfo = &E_GROUP_TYPEINFO;
                }
                else
                {
                    test_names[0] = mask;

                    test_typeinfo = linkType;
                }

                if (node->getType()->checkHierarchy(&E_GROUP_TYPEINFO))
                {
                    test_txt = test_names[0].getText();

                    test_group = (eGroup*)node;

                    for (int a = 0; a < test_group->getNodesCount(); a++)
                    {
                        if (nullptr != (test_node[0] = test_group->getIthChild(a)))
                        {
                            node_name = test_node[0]->getStringRepresentation();

                            if (test_node[0]->getType()->checkHierarchy(test_typeinfo))
                            {
                                if (ArFunctions::compareNameWithWildcards(node_name.getText(), test_txt))
                                {
                                    if (false == has_slash)
                                    {
                                        return test_node[0];
                                    }

                                    test_node[1] = findLinkByFormat(test_node[0], test_names[1]);

                                    if (nullptr != test_node[1])
                                    {
                                        return test_node[1];
                                    }
                                }
                            }

                            if (node_name.compare("#", 0, 1, true) && test_node[0]->getType()->checkHierarchy(&E_GROUP_TYPEINFO))
                            {
                                test_node[1] = findLinkByFormat(test_node[0], mask);

                                if (nullptr != test_node[1])
                                {
                                    return test_node[1];
                                }
                            }
                        }
                    }
                }

                return nullptr;
            }
        }

        return nullptr;
    }


    ////////////////////////////////////////////////////////////////
    // NodeRefLinker: find link
    // <kao2.0059F7D0>
    ////////////////////////////////////////////////////////////////
    eNode* NodeRefLinker::findLink(eNode* root, eNode* current_node, eString link_name, eString mask, TypeInfo* type_info)
    {
        passedName = link_name;
        passedMask = mask;

        if (nullptr == type_info)
        {
            throwErrorMessage("invalid TypeInfo");

            return nullptr;
        }

        linkType = type_info;

        if (nullptr == current_node)
        {
            throwErrorMessage(nullptr);

            return nullptr;
        }

        if (mask.compare("/", 0, 1, true))
        {
            mask = mask.getSubstring(1);

            if (nullptr == root)
            {
                current_node = current_node->getRootNode();
            }
            else
            {
                current_node = root;
            }
        }

        current_node = findLinkByFormat(current_node, mask);

        if (nullptr == current_node)
        {
            throwErrorMessage(nullptr);
        }

        return current_node;
    }

}
