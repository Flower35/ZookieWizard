#ifndef H_KAO2AR_NODE
#define H_KAO2AR_NODE

#include <kao2engine/ePrimitive.h>

namespace ZookieWizard
{
    class eALBox;
    class eScene;

    ////////////////////////////////////////////////////////////////
    // eNode interface
    ////////////////////////////////////////////////////////////////

    class eNode : public ePrimitive
    {

        /*** Properties ***/

        protected:

            /*[0x08]*/ eScene* scene;
            /*[0x0C]*/ int32_t unknown_0C;
            /*[0x10]*/ eNode* parent;
            /*[0x14]*/ eString name;
            /*[0x18]*/ eALBox* unknown_18;
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
            TypeInfo* getType() override;

            eString getStringRepresentation() override;
            eString getLogPrintMessage() override;
    };


    ////////////////////////////////////////////////////////////////
    // eNode TypeInfo
    // <kao2.047A490> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_NODE_ID = 0x8000;

    extern TypeInfo E_NODE_TYPEINFO;

}

#endif
