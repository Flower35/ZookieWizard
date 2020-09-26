#ifndef H_KAO2AR_XREFMANAGER
#define H_KAO2AR_XREFMANAGER

#include <kao2engine/eNode.h>

#include <kao2ar/Collection.h>

namespace ZookieWizard
{
    class eXRefProxy;

    ////////////////////////////////////////////////////////////////
    // eXRefManager interface
    // <kao2.005D1FC0> (vptr)
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

        private:

            void createFromOtherObject(const eXRefManager &other);

        public:

            eXRefManager(const eXRefManager &other);
            eXRefManager& operator = (const eXRefManager &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            /* << eNode >> */

            void destroyNode() override;

            void renderNode(eDrawContext &draw_context) const override;

            void exportXRef(const eString &media_dir, int32_t engine_version) const override;

    };


    ////////////////////////////////////////////////////////////////
    // eXRefManager TypeInfo
    // <kao2.004AE760> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_XREFMANAGER_ID = 0x87EF0003;

    extern TypeInfo E_XREFMANAGER_TYPEINFO;

}

#endif
