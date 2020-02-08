#ifndef H_KAO2AR_BEZIERSPLINENODE
#define H_KAO2AR_BEZIERSPLINENODE

#include <kao2engine/eNode.h>

#include <kao2ar/Collection.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eBezierSplineNode interface
    ////////////////////////////////////////////////////////////////

    class eBezierSplineNode : public eNode
    {

        /*** Properties ***/

        protected:

            /*[0x08-0x10]*/ Collection<ArFunctions::serialize_eRefCounter> splines;

        /*** Methods ***/

        public:

            eBezierSplineNode();
            ~eBezierSplineNode();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eBezierSplineNode TypeInfo
    // <kao2.004A8820> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_BEZIERSPLINENODE_ID = 0x00398884;

    extern TypeInfo E_BEZIERSPLINENODE_TYPEINFO;

}

#endif
