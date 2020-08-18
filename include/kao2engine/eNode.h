#ifndef H_KAO2AR_NODE
#define H_KAO2AR_NODE

#include <kao2engine/ePrimitive.h>

namespace ZookieWizard
{
    class eALBox;
    class eTransform;
    template <typename> class eCtrl;

    extern const char* theNodeFlagNames[32];

    #define TXT_PARSING_NODE_PARAMTYPE_NUM 0
    #define TXT_PARSING_NODE_PARAMTYPE_STR 1
    #define TXT_PARSING_NODE_PARAMTYPE_REF 2


    ////////////////////////////////////////////////////////////////
    // eNode interface
    ////////////////////////////////////////////////////////////////

    class eNode : public ePrimitive
    {

        /*** Properties ***/

        protected:

            /*[0x08]*/ eTransform* previousTransform;
            /*[0x0C]*/ int32_t unknown_0C;
            /*[0x10]*/ eNode* parent;
            /*[0x14]*/ eString name;
            /*[0x18]*/ eALBox* axisListBox;
            /*[0x1C]*/ uint32_t flags;
            /*[0x20-0x2C]*/ float sphBound[4];
            /*[0x30]*/ uint16_t flagsCollisionResponse;
            /*[0x34]*/ eCtrl<float>* visCtrl;
            /*[0x38]*/ float visRate;
            /*[(kao3)0x34]*/ int32_t visGroup;

        /*** Methods ***/

        public:

            eNode(eString s, eNode* x);
            eNode();
            ~eNode();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            eString getStringRepresentation() const override;
            eString getLogPrintMessage() const override;
            void writeStructureToTextFile(FileOperator &file, int32_t indentation) const override;

            virtual void updateDrawPassFlags(uint32_t* parent_flags);
            virtual void updateBeforeRendering(eDrawContext &draw_context);
            virtual void renderNode(eDrawContext &draw_context) const;

            virtual ePoint3 editingGetCenterPoint() const;
            virtual void editingRebuildCollision();
            virtual void editingClearCollision();
            virtual void editingApplyNewTransform(eSRP &new_transform, int32_t marked_id);

            virtual void destroyNode();
            virtual void findAndDereference(eNode* target);

            virtual void ctrlExpandAnimTracks(int32_t new_size);
            virtual void ctrlRemoveAnimTrack(int32_t deleted_id);

            void setName(eString new_name);

            eNode* getRootNode() const;
            eNode* getParentNode() const;
            void setParentNode(eNode* new_parent);

            virtual eNode* findNode(eString &searched_name) const;

            eTransform* getPreviousTransform() const;
            void setPreviousTransform();

            uint32_t getFlags() const;
            void setFlags(uint32_t bits_to_apply);
            void unsetFlags(uint32_t bits_to_erase);

            eALBox* getAxisListBox() const;
            void setAxisListBox(eALBox* box);

            eCtrl<float>* getVisCtrl() const;
            void setVisCtrl(eCtrl<float>* new_visctrl);
            void visCtrlClear(int32_t anim_id);
            void visCtrlSetStatic(float opacity);
            void visCtrlSetLoopType(int32_t anim_id, int32_t loop_type);
            void visCtrlAddKeyframe(int32_t anim_id, float time, float opacity);
    };


    ////////////////////////////////////////////////////////////////
    // eNode TypeInfo
    // <kao2.047A490> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_NODE_ID = 0x8000;

    extern TypeInfo E_NODE_TYPEINFO;


    ////////////////////////////////////////////////////////////////
    // Global Nodes counter
    ////////////////////////////////////////////////////////////////

    extern int32_t theNodesCounter;

}

#endif
