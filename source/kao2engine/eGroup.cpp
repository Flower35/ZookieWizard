#include <kao2engine/eGroup.h>
#include <kao2ar/Archive.h>

#include <kao2engine/eTriMesh.h>

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
            child_node = (eNode*)nodes.getIthChild(i);

            if (nullptr != child_node)
            {
                child_node->setParentNode(nullptr);
            }
        }
    }


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
    // eGroup: destroy children nodes
    ////////////////////////////////////////////////////////////////
    void eGroup::destroyNode()
    {
        int32_t i;
        eNode* child_node;

        for (i = 0; i < nodes.getSize(); i++)
        {
            child_node = (eNode*)nodes.getIthChild(i);

            if (nullptr != child_node)
            {
                child_node->destroyNode();
            }
        }

        eNode::destroyNode();
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

        if (nullptr != o)
        {
            /* This is in case the child node already has parent, */
            /* but is referenced only once (so it doesn't get deleted) */
            o->incRef();

            previous_parent = (eGroup*)o->getParentNode();

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
    // eGroup: find reference to some node when deleting it
    ////////////////////////////////////////////////////////////////
    void eGroup::findAndDereference(eNode* target)
    {
        int32_t i;
        eNode* child_node;

        if (referenceCount <= 0)
        {
            /* This group is invalid (for instance, it is being deleted) */
            return;
        }

        for (i = 0; i < nodes.getSize(); i++)
        {
            child_node = (eNode*)nodes.getIthChild(i);

            if (nullptr != child_node)
            {
                child_node->findAndDereference(target);
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eGroup: add empty animation track (if the node uses "eMultiCtrl")
    ////////////////////////////////////////////////////////////////
    void eGroup::ctrlExpandAnimTracks(int32_t new_size)
    {
        int32_t i;
        eNode* child_node;

        for (i = 0; i < nodes.getSize(); i++)
        {
            child_node = (eNode*)nodes.getIthChild(i);

            if (nullptr != child_node)
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
        int32_t i;
        eNode* child_node;

        for (i = 0; i < nodes.getSize(); i++)
        {
            child_node = (eNode*)nodes.getIthChild(i);

            if (nullptr != child_node)
            {
                child_node->ctrlRemoveAnimTrack(deleted_id);
            }
        }

        /* Checking the `visTrack` */
        eNode::ctrlRemoveAnimTrack(deleted_id);
    }


    ////////////////////////////////////////////////////////////////
    // eGroup: remove nodes with multiple references
    ////////////////////////////////////////////////////////////////
    void eGroup::deleteNodesWithMultiRefs(bool canBeInvalid)
    {
        int32_t i;
        eNode *root, *child_node;
        eGroup* test_group;

        if ((referenceCount <= 0) && (false == canBeInvalid))
        {
            return;
        }

        for (i = 0; i < nodes.getSize(); i++)
        {
            child_node = (eNode*)nodes.getIthChild(i);

            if (nullptr != child_node)
            {
                /* Search recursively */

                if (child_node->getType()->checkHierarchy(&E_GROUP_TYPEINFO))
                {
                    test_group = (eGroup*)child_node;
                    test_group->deleteNodesWithMultiRefs(false);
                }
            }
        }

        for (i = 0; i < nodes.getSize(); i++)
        {
            child_node = (eNode*)nodes.getIthChild(i);

            if (nullptr != child_node)
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


    ////////////////////////////////////////////////////////////////
    // eGroup: render each child node
    ////////////////////////////////////////////////////////////////
    bool eGroup::renderObject(int32_t draw_flags, eAnimate* anim, eSRP &parent_srp, eMatrix4x4 &parent_matrix, int32_t marked_id)
    {
        int32_t a, b;
        eNode* child_node;

        if (false == eNode::renderObject(draw_flags, anim, parent_srp, parent_matrix, marked_id))
        {
            return false;
        }

        for (a = 0; a < nodes.getSize(); a++)
        {
            child_node = (eNode*)nodes.getIthChild(a);

            if (nullptr != child_node)
            {
                /* `0x01 & (child_node->getFlags() >> 0x0A)` */

                /* Current object from Archive will have "ID >= (-1)" */
                /* Object marked on list will receive "ID = (-2)" */
                /* Object that is a child of marked group will receive "ID = (-3)" */
                /* Any object that is not selected or marked will receive "ID = (-4)" */
                if (((-2) == marked_id) || ((-3) == marked_id))
                {
                    b = (-3);
                }
                else
                {
                    b = (marked_id == a) ? (-2) : (-4);
                }

                child_node->renderObject(draw_flags, anim, parent_srp, parent_matrix, b);
            }
        }

        return true;
    }


    ////////////////////////////////////////////////////////////////
    // eGroup: find node by name
    // <kao2.00483900>
    ////////////////////////////////////////////////////////////////
    eNode* eGroup::findNode(eString &searched_name) const
    {
        int32_t i;
        eNode* test_node;

        test_node = eNode::findNode(searched_name);

        if (nullptr != test_node)
        {
            return test_node;
        }

        for (i = 0; i < nodes.getSize(); i++)
        {
            test_node = (eNode*)nodes.getIthChild(i);

            if (nullptr != test_node)
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
    // eGroup: find material by path
    ////////////////////////////////////////////////////////////////
    eMaterial* eGroup::findMaterial(eString &searched_path) const
    {
        int32_t i;
        eNode* child_node;
        eMaterial* test_material;

        for (i = 0; i < nodes.getSize(); i++)
        {
            child_node = (eNode*)nodes.getIthChild(i);

            if (nullptr != child_node)
            {
                test_material = child_node->findMaterial(searched_path);

                if (nullptr != test_material)
                {
                    return test_material;
                }
            }
        }

        return nullptr;
    }


    ////////////////////////////////////////////////////////////////
    // eGroup: export readable structure
    ////////////////////////////////////////////////////////////////
    void eGroup::writeStructureToTextFile(FileOperator &file, int32_t indentation) const
    {
        int32_t i;
        eNode* child_node;

        eNode::writeStructureToTextFile(file, indentation);

        for (i = 0; i < nodes.getSize(); i++)
        {
            child_node = (eNode*)nodes.getIthChild(i);

            if (nullptr != child_node)
            {
                child_node->writeStructureToTextFile(file, (indentation + 1));
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
                    child_node = (eNode*)nodes.getIthChild(i);

                    if (nullptr != child_node)
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
                    child_node = (eNode*)nodes.getIthChild(i);

                    if (nullptr != child_node)
                    {
                        child_node->writeNodeToXmlFile(exporter);
                    }
                }

                exporter.closeTag(); // "node"

                break;
            }
        }


    }

}
