#ifndef H_KAO2AR_XREFMANAGER
#define H_KAO2AR_XREFMANAGER

#include <kao2engine/eNode.h>

#include <kao2ar/Collection.h>

namespace ZookieWizard
{
    class eXRefProxy;

    ////////////////////////////////////////////////////////////////
    // eXRefManager interface
    ////////////////////////////////////////////////////////////////

    class eXRefManager : public eNode
    {

        /*** Properties ***/

        protected:

            /*[0x3C-0x48]*/ Collection<ArFunctions::serialize_eRefCounter> xrefs;

        /*** Methods ***/

        public:

            eXRefManager();
            ~eXRefManager();

            void serialize(Archive &ar) override;
            TypeInfo* getType() override;

            void renderObject(eAnimate* anim, int32_t draw_flags, eSRP &parent_srp) override;
    };


    ////////////////////////////////////////////////////////////////
    // eXRefManager TypeInfo
    // <kao2.004AE790> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_XREFMANAGER_ID = 0x87EF0003;

    extern TypeInfo E_XREFMANAGER_TYPEINFO;

}

#endif
