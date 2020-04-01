#ifndef H_KAO2AR_NODE
#define H_KAO2AR_NODE

#include <kao2engine/ePrimitive.h>

namespace ZookieWizard
{
    class eALBox;
    class eTransform;
    class eMaterial;

    extern const char* theNodeFlagNames[32];

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
            /*[0x30]*/ uint16_t flags02;
            /*[0x34]*/ eRefCounter* unknown_34; // "animated vis ctrl", "static vis ctrl".
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

            bool renderObject(int32_t draw_flags, eAnimate* anim, eSRP &parent_srp, int32_t marked_id) override;

            virtual ePoint3 editingGetCenterPoint() const;
            virtual void editingRebuildCollision();
            virtual void editingClearCollision();
            virtual void editingApplyNewTransform(eSRP &new_transform, int32_t marked_id);

            virtual void destroyNode();
            virtual void updateSRP(bool update, eAnimate* anim, eSRP &parent_srp);
            virtual void findAndDereference(eNode* target);
            virtual bool deleteXRefTargets();

            void setName(eString new_name);

            eNode* getRootNode() const;
            eNode* getParentNode() const;
            void setParentNode(eNode* new_parent);

            virtual eNode* findNode(eString &searched_name) const;
            virtual eMaterial* findMaterial(eString &searched_path) const;

            eTransform* getPreviousTransform() const;
            void setPreviousTransform();

            int32_t getFlags() const;
            void setFlags(int32_t bits_to_apply);
            void unsetFlags(int32_t bits_to_erase);

            eALBox* getAxisListBox() const;
            void setAxisListBox(eALBox* box);

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
