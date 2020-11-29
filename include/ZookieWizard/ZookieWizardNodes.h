#ifndef H_ZOOKIEWIZARD_NODESMANAGER
#define H_ZOOKIEWIZARD_NODESMANAGER

namespace ZookieWizard
{
    ////////////////////////////////////////////////////////////////
    // Zookie Wizard: Nodes Manager
    ////////////////////////////////////////////////////////////////

    bool prepareNodesManager();
    void clearNodesManager();

    void* nodesManager_GetProxyTarget(void* full_path);
    bool nodesManager_InsertProxyTarget(void* full_path, void* new_target);
    void nodesManager_ClearProxies();

    bool nodesManager_InsertNodeWithMissingAxisListBox(void* node);
    void nodesManager_ClearALBoxesRefs();

    bool nodesManager_CloneChild(void* parent_node, int32_t child_id);
    bool nodesManager_PasteLastClone(void* parent_node);

    void* nodesManager_RemoveChild(void* parent_node, int32_t child_id, void* active_node);
}

#endif
