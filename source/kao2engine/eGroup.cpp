#include <kao2engine/eGroup.h>
#include <kao2ar/Archive.h>
#include <kao2ar/eDrawContext.h>

#include <kao2engine/eTransform.h>

#include <utilities/ColladaExporter.h>

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

    TypeInfo* eGroup::getType() const
    {
        return &E_GROUP_TYPEINFO;
    }

    eGroup::eGroup(eString s, eNode* x)
    : eNode(s, x)
    {}

    eGroup::eGroup()
    : eNode()
    {}

    eGroup::~eGroup()
    {
        int32_t i;
        eNode* child_node;

        deleteNodesWithMultiRefs(true);

        /* Failsafe (marks children as "invalid", as they no longer have a parent node link) */

        for (i = 0; i < nodes.getSize(); i++)
        {
            if (nullptr != (child_node = (eNode*)nodes.getIthChild(i)))
            {
                child_node->setParentNode(nullptr);
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eGroup: cloning the object
    ////////////////////////////////////////////////////////////////

    void eGroup::createFromOtherObject(const eGroup &other)
    {
        int32_t a, b;
        eNode* dummy_node;

        /* All new nodes are "deep clones" with the Reference Counter of 1 */
        nodes.deepCopy(other.nodes);
        b = nodes.getSize();

        for (a = 0; a < b; a++)
        {
            if (nullptr != (dummy_node = (eNode*)nodes.getIthChild(a)))
            {
                dummy_node->setParentNode(this);
            }
        }
    }

    eGroup::eGroup(const eGroup &other)
    : eNode(other)
    {
        createFromOtherObject(other);
    }

    eGroup& eGroup::operator = (const eGroup &other)
    {
        if ((&other) != this)
        {
            eNode::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eGroup::cloneFromMe() const
    {
        return new eGroup(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eGroup: serialization
    // <kao2.004835F0>
    ////////////////////////////////////////////////////////////////
    void eGroup::serialize(Archive &ar)
    {
        eNode::serialize(ar);

        nodes.serialize(ar, &E_NODE_TYPEINFO);
    }


    ////////////////////////////////////////////////////////////////
    // eGroup: export readable structure
    ////////////////////////////////////////////////////////////////
    void eGroup::writeStructureToTextFile(FileOperator &file, int32_t indentation, bool group_written) const
    {
        eNode* child_node;

        eNode::writeStructureToTextFile(file, indentation, true);

        if (!group_written)
        {
            for (int32_t a = 0; a < nodes.getSize(); a++)
            {
                if (nullptr != (child_node = (eNode*)nodes.getIthChild(a)))
                {
                    child_node->writeStructureToTextFile(file, (indentation + 1), false);
                }
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eGroup: COLLADA exporting
    ////////////////////////////////////////////////////////////////
    void eGroup::writeNodeToXmlFile(ColladaExporter &exporter) const
    {
        int32_t i;
        char bufor[64];
        eNode* child_node;

        switch (exporter.getState())
        {
            case COLLADA_EXPORTER_STATE_LIGHTS:
            case COLLADA_EXPORTER_STATE_CAMERAS:
            case COLLADA_EXPORTER_STATE_EFFECTS:
            case COLLADA_EXPORTER_STATE_IMAGES:
            case COLLADA_EXPORTER_STATE_MATERIALS:
            case COLLADA_EXPORTER_STATE_GEOMETRIES:
            case COLLADA_EXPORTER_STATE_CONTROLLERS:
            case COLLADA_EXPORTER_STATE_ANIMATIONS:
            {
                /* Collecting objects for COLLADA libraries... */

                for (i = 0; i < nodes.getSize(); i++)
                {
                    if (nullptr != (child_node = (eNode*)nodes.getIthChild(i)))
                    {
                        child_node->writeNodeToXmlFile(exporter);
                    }
                }

                break;
            }

            case COLLADA_EXPORTER_STATE_VISUAL_SCENES:
            {
                /* "eGroup" could exist as independent node (without parent "eTransform") */

                exporter.openTag("node");

                i = exporter.getObjectRefId(COLLADA_EXPORTER_OBJ_NODE, this, true);
                sprintf_s(bufor, 64, "Node%d", i);
                exporter.insertTagAttrib("id", bufor);
                exporter.insertTagAttrib("name", name);

                /* Iterate child nodes as usual */

                for (i = 0; i < nodes.getSize(); i++)
                {
                    if (nullptr != (child_node = (eNode*)nodes.getIthChild(i)))
                    {
                        child_node->writeNodeToXmlFile(exporter);
                    }
                }

                exporter.closeTag(); // "node"

                break;
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eGroup: destroy children nodes
    ////////////////////////////////////////////////////////////////
    void eGroup::destroyNode()
    {
        eNode* child_node;

        for (int32_t a = 0; a < nodes.getSize(); a++)
        {
            if (nullptr != (child_node = (eNode*)nodes.getIthChild(a)))
            {
                child_node->destroyNode();
            }
        }

        eNode::destroyNode();
    }


    ////////////////////////////////////////////////////////////////
    // eGroup: find reference to some node when deleting it
    ////////////////////////////////////////////////////////////////
    void eGroup::findAndDereference(eNode* target)
    {
        eNode* child_node;

        if (referenceCount <= 0)
        {
            /* This group is invalid (for instance, it is being deleted) */
            return;
        }

        for (int32_t a = 0; a < nodes.getSize(); a++)
        {
            if (nullptr != (child_node = (eNode*)nodes.getIthChild(a)))
            {
                child_node->findAndDereference(target);
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eGroup: find node by name
    // <kao2.00483900>
    ////////////////////////////////////////////////////////////////
    eNode* eGroup::findNode(eString &searched_name) const
    {
        eNode* test_node;

        test_node = eNode::findNode(searched_name);

        if (nullptr != test_node)
        {
            return test_node;
        }

        for (int32_t a = 0; a < nodes.getSize(); a++)
        {
            if (nullptr != (test_node = (eNode*)nodes.getIthChild(a)))
            {
                test_node = test_node->findNode(searched_name);

                if (nullptr != test_node)
                {
                    return test_node;
                }
            }
        }

        return nullptr;
    }


    ////////////////////////////////////////////////////////////////
    // eNode: set `previousTransform` gradually
    ////////////////////////////////////////////////////////////////
    void eGroup::setPreviousTransformGradually(eTransform* last_xform)
    {
        eNode* child_node;

        for (int32_t a = 0; a < nodes.getSize(); a++)
        {
            if (nullptr != (child_node = (eNode*)nodes.getIthChild(a)))
            {
                child_node->setPreviousTransformGradually(last_xform);
            }
        }

        previousTransform = last_xform;
    }


    ////////////////////////////////////////////////////////////////
    // eGroup: update DrawPass flags from children nodes
    ////////////////////////////////////////////////////////////////
    void eGroup::updateDrawPassFlags(uint32_t* parent_flags)
    {
        flags &= (~ 0x70000000);

        for (int32_t a = 0; a < nodes.getSize(); a++)
        {
            eNode* child_node = (eNode*)nodes.getIthChild(a);

            if (nullptr != child_node)
            {
                child_node->updateDrawPassFlags(&flags);
            }
        }

        eNode::updateDrawPassFlags(parent_flags);
    }


    ////////////////////////////////////////////////////////////////
    // eGroup: update before rendering [[vptr]+0x38]
    // <kao2.00482E50>
    ////////////////////////////////////////////////////////////////
    void eGroup::updateBeforeRendering(eDrawContext &draw_context)
    {
        eNode::updateBeforeRendering(draw_context);

        bool is_marked;
        int32_t a, previous_marked_id;
        eNode* child_node;

        previous_marked_id = draw_context.getMarekedId();
        is_marked = draw_context.setMarkedForGroupNode();

        for (a = 0; a < nodes.getSize(); a++)
        {
            if (nullptr != (child_node = (eNode*)nodes.getIthChild(a)))
            {
                if (0x0408 == (child_node->getFlags() & 0x0408))
                {
                    if (!is_marked)
                    {
                        draw_context.setMarkedForChildNode(previous_marked_id == a);
                    }

                    child_node->updateBeforeRendering(draw_context);
                }
            }
        }

        draw_context.setMarkedId(previous_marked_id);
    }


    ////////////////////////////////////////////////////////////////
    // eGroup: render this node
    ////////////////////////////////////////////////////////////////
    void eGroup::renderNode(eDrawContext &draw_context) const
    {
        eNode* child_node;

        int32_t previous_marked_id = draw_context.getMarekedId();
        bool is_marked = draw_context.setMarkedForGroupNode();

        for (int32_t a = 0; a < nodes.getSize(); a++)
        {
            if (nullptr != (child_node = (eNode*)nodes.getIthChild(a)))
            {
                if (draw_context.checkNodeFlags(child_node->getFlags(), child_node->getType()->checkHierarchy(&E_GROUP_TYPEINFO)))
                {
                    if (!is_marked)
                    {
                        draw_context.setMarkedForChildNode(previous_marked_id == a);
                    }

                    child_node->renderNode(draw_context);
                }
            }
        }

        draw_context.setMarkedId(previous_marked_id);
    }


    ////////////////////////////////////////////////////////////////
    // eGroup: (editor option) rebuild collision
    ////////////////////////////////////////////////////////////////
    void eGroup::editingRebuildCollision()
    {
        int32_t i;
        eNode* child_node;

        for (i = 0; i < nodes.getSize(); i++)
        {
            child_node = (eNode*)nodes.getIthChild(i);

            if (nullptr != child_node)
            {
                child_node->editingRebuildCollision();
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eGroup: (editor option) clear collision
    ////////////////////////////////////////////////////////////////
    void eGroup::editingClearCollision()
    {
        int32_t i;
        eNode* child_node;

        for (i = 0; i < nodes.getSize(); i++)
        {
            child_node = (eNode*)nodes.getIthChild(i);

            if (nullptr != child_node)
            {
                child_node->editingClearCollision();
            }
        }

        eNode::editingClearCollision();
    }


    ////////////////////////////////////////////////////////////////
    // eGroup: (editor option) apply new transformation
    ////////////////////////////////////////////////////////////////
    void eGroup::editingApplyNewTransform(eSRP &new_transform, int32_t marked_id)
    {
        eNode* child_node;

        child_node = (eNode*)nodes.getIthChild(marked_id);

        if (nullptr != child_node)
        {
            child_node->editingApplyNewTransform(new_transform, (-1));
        }
    }


    ////////////////////////////////////////////////////////////////
    // eGroup: custom TXT parser
    ////////////////////////////////////////////////////////////////

    int32_t eGroup::parsingCustomMessage(char* result_msg, const eString &message, int32_t params_count, const TxtParsingNodeProp* params)
    {
        int32_t test;
        eNode* root_node;
        eNode* child_node;

        if (1 != (test = eNode::parsingCustomMessage(result_msg, message, params_count, params)))
        {
            return test;
        }

        if (message.compareExact("clearNodes", true))
        {
            if (0 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "clearNodes", 0);
                return 2;
            }

            /********************************/

            root_node = getRootNode();

            while (nodes.getSize() > 0)
            {
                if (nullptr != (child_node = (eNode*)nodes.getIthChild(0)))
                {
                    if (child_node->getReferenceCount() >= 2)
                    {
                        if (nullptr != root_node)
                        {
                            root_node->findAndDereference(child_node);
                        }
                    }

                }

                deleteIthChild(0);
            }

            return 0;
        }

        return 1;
    }


    ////////////////////////////////////////////////////////////////
    // eGroup: exporting script files
    ////////////////////////////////////////////////////////////////
    void eGroup::exportScripts(const eString &media_dir) const
    {
        eNode* child_node;

        for (int32_t a = 0; a < nodes.getSize(); a++)
        {
            if (nullptr != (child_node = (eNode*)nodes.getIthChild(a)))
            {
                child_node->exportScripts(media_dir);
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eGroup: loading or exporting Proxies
    ////////////////////////////////////////////////////////////////

    void eGroup::reloadXRef(const eString &media_dir, int32_t engine_version)
    {
        eNode* child_node;

        for (int32_t a = 0; a < nodes.getSize(); a++)
        {
            if (nullptr != (child_node = (eNode*)nodes.getIthChild(a)))
            {
                child_node->reloadXRef(media_dir, engine_version);
            }
        }
    }

    void eGroup::exportXRef(const eString &media_dir, int32_t engine_version) const
    {
        eNode* child_node;

        for (int32_t a = 0; a < nodes.getSize(); a++)
        {
            if (nullptr != (child_node = (eNode*)nodes.getIthChild(a)))
            {
                child_node->exportXRef(media_dir, engine_version);
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eGroup: add empty animation track (if the node uses "eMultiCtrl")
    ////////////////////////////////////////////////////////////////
    void eGroup::ctrlExpandAnimTracks(int32_t new_size)
    {
        eNode* child_node;

        for (int32_t a = 0; a < nodes.getSize(); a++)
        {
            if (nullptr != (child_node = (eNode*)nodes.getIthChild(a)))
            {
                child_node->ctrlExpandAnimTracks(new_size);
            }
        }

        /* Checking the `visTrack` */
        eNode::ctrlExpandAnimTracks(new_size);
    }


    ////////////////////////////////////////////////////////////////
    // eGroup: remove specific animation track (if the node uses "eMultiCtrl")
    ////////////////////////////////////////////////////////////////
    void eGroup::ctrlRemoveAnimTrack(int32_t deleted_id)
    {
        eNode* child_node;

        for (int32_t a = 0; a < nodes.getSize(); a++)
        {
            if (nullptr != (child_node = (eNode*)nodes.getIthChild(a)))
            {
                child_node->ctrlRemoveAnimTrack(deleted_id);
            }
        }

        /* Checking the `visTrack` */
        eNode::ctrlRemoveAnimTrack(deleted_id);
    }


    ////////////////////////////////////////////////////////////////
    // eGroup: get nodes count
    ////////////////////////////////////////////////////////////////
    int32_t eGroup::getNodesCount() const
    {
        return nodes.getSize();
    }


    ////////////////////////////////////////////////////////////////
    // eGroup: get i-th node
    ////////////////////////////////////////////////////////////////
    eNode* eGroup::getIthChild(int32_t i) const
    {
        return (eNode*)nodes.getIthChild(i);
    }


    ////////////////////////////////////////////////////////////////
    // eGroup: append new node
    ////////////////////////////////////////////////////////////////
    void eGroup::appendChild(eNode* o)
    {
        eGroup* previous_parent;
        eTransform* previous_xform;

        if (nullptr != o)
        {
            if (this == (previous_parent = o->getParentNode()))
            {
                return;
            }

            /* This is in case the child node already has parent, */
            /* but is referenced only once (so it doesn't get deleted) */
            o->incRef();

            if (nullptr != previous_parent)
            {
                if (previous_parent->getType()->checkHierarchy(&E_GROUP_TYPEINFO))
                {
                    previous_parent->findAndDetachChild(o);
                }
            }

            nodes.appendChild(o);
            o->setParentNode(this);

            o->decRef();

            /****************/

            previous_xform = nullptr;

            previous_parent = parent;

            while ((nullptr == previous_xform) && (nullptr != previous_parent))
            {
                if (previous_parent->getType()->checkHierarchy(&E_TRANSFORM_TYPEINFO))
                {
                    previous_xform = (eTransform*)previous_parent;
                }
                else
                {
                    previous_parent = previous_parent->getParentNode();
                }
            }

            o->setPreviousTransformGradually(previous_xform);
        }
    }


    ////////////////////////////////////////////////////////////////
    // eGroup: delete i-th node
    ////////////////////////////////////////////////////////////////
    void eGroup::deleteIthChild(int32_t i)
    {
        eNode* child_node = (eNode*)nodes.getIthChild(i);

        if (nullptr != child_node)
        {
            child_node->destroyNode();
        }

        nodes.deleteIthChild(i);
    }


    ////////////////////////////////////////////////////////////////
    // eGroup: delete specific node
    ////////////////////////////////////////////////////////////////
    void eGroup::findAndDeleteChild(eNode* o)
    {
        int32_t i;

        for (i = 0; i < nodes.getSize(); i++)
        {
            if (nodes.getIthChild(i) == o)
            {
                deleteIthChild(i);
                return;
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eGroup: detach specific node without deleting it
    ////////////////////////////////////////////////////////////////
    void eGroup::findAndDetachChild(eNode* o)
    {
        nodes.findAndDeleteChild(o);
    }


    ////////////////////////////////////////////////////////////////
    // eGroup: swap nodes by one place backwards of forwards
    ////////////////////////////////////////////////////////////////

    void eGroup::swapForward(int32_t i)
    {
        nodes.swapForward(i);
    }

    void eGroup::swapBackward(int32_t i)
    {
        nodes.swapBackward(i);
    }


    ////////////////////////////////////////////////////////////////
    // eGroup: remove nodes with multiple references
    ////////////////////////////////////////////////////////////////
    void eGroup::deleteNodesWithMultiRefs(bool canBeInvalid)
    {
        int32_t a;
        eNode *root, *child_node;
        eGroup* test_group;

        if ((referenceCount <= 0) && (false == canBeInvalid))
        {
            return;
        }

        for (a = 0; a < nodes.getSize(); a++)
        {
            if (nullptr != (child_node = (eNode*)nodes.getIthChild(a)))
            {
                /* Search recursively */

                if (child_node->getType()->checkHierarchy(&E_GROUP_TYPEINFO))
                {
                    test_group = (eGroup*)child_node;
                    test_group->deleteNodesWithMultiRefs(false);
                }
            }
        }

        for (a = 0; a < nodes.getSize(); a++)
        {
            if (nullptr != (child_node = (eNode*)nodes.getIthChild(a)))
            {
                /* Look for other objects referencing this child node */

                if (child_node->getReferenceCount() >= 2)
                {
                    root = child_node->getRootNode();

                    if (nullptr == root)
                    {
                        root = getRootNode();
                    }

                    if (nullptr != root)
                    {
                        root->findAndDereference(child_node);
                        /* (--dsp--) delete from scripts as well! */
                    }
                }
            }
        }
    }

}
