#ifndef H_KAO2AR_NODE
#define H_KAO2AR_NODE

#include <kao2engine/ePrimitive.h>

namespace ZookieWizard
{
    class eALBox;
    class eTransform;

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

            virtual void updateSRP(eAnimate* anim, eSRP &parent_srp);

            void setName(eString new_name);

            eNode* getParentNode() const;
            void setParentNode(eNode* new_parent);

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

}

#endif
