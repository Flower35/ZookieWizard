#ifndef H_ELEPHANT_STATICPOOL
#define H_ELEPHANT_STATICPOOL

#include <ElephantBase/eString.h>

namespace ZookieWizard
{
    class Gadget;
    struct TypeInfo;
    class Archive;
    class eShaderDesc;

    ////////////////////////////////////////////////////////////////
    // ELEPHANT ENGINE: STATIC POOL
    ////////////////////////////////////////////////////////////////

    static const int MAX_GADGET_INSTANCES =  8;
    static const int MAX_SHADER_INSTANCES = 16;

    struct ElephantStaticPool
    {
        /*** Properties ***/

        private:

            int gadgetsCount;
            const Gadget* gadgetsList[MAX_GADGET_INSTANCES];

            int shadersCount;
            eShaderDesc* shadersList[MAX_SHADER_INSTANCES];

        /*** Methods ***/

        public:

            ~ElephantStaticPool();

        private:

            bool registerGadget(const Gadget* gadget);
            int findGadget(const TypeInfo* info) const;

            bool registerShader(eString name, int params_count);

        public:

            bool registerStaticElements();

            void serializeGadget(Archive &ar, const Gadget** gadget) const;

            eShaderDesc* getShaderDescription(eString &name) const;

            eShaderDesc* getDefaultShaderDescription() const;
    };

    extern ElephantStaticPool theElephantStaticPool;
}

#endif
