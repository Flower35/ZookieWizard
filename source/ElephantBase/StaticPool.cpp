#include <ElephantBase/StaticPool.h>

namespace ZookieWizard
{
    ElephantStaticPool theElephantStaticPool;
}

#include <ElephantBase/TypeInfo.h>
#include <ElephantEngine/Gadget.h>
#include <ElephantBase/Archive.h>


////////////////////////////////////////////////////////////////
// "Kao the Kangaroo: Round 2" Static Gadgets
////////////////////////////////////////////////////////////////

#include <ElephantEngine/Log.h>
#include <ElephantEngine/Key.h>
#include <ElephantEngine/Rnd.h>
#include <ElephantEngine/eMusicManager.h>
#include <ElephantEngine/eFSSprite.h>
#include <ElephantEngine/eFSMB.h>


////////////////////////////////////////////////////////////////
// "The Saddle Club" Shader Factory
////////////////////////////////////////////////////////////////

#include <ElephantEngine/eShaderDesc.h>


namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Elephant Static Pool: Destructor
    ////////////////////////////////////////////////////////////////
    ElephantStaticPool::~ElephantStaticPool()
    {
        for (int a = 0; a < shadersCount; a++)
        {
            shadersList[a]->decRef();
        }
    }


    ////////////////////////////////////////////////////////////////
    // Elephant Static Pool: Begin
    ////////////////////////////////////////////////////////////////
    bool ElephantStaticPool::registerStaticElements()
    {
        gadgetsCount = 0;
        shadersCount = 0;

        registerGadget(&theLog);
        registerGadget(&theKey);
        registerGadget(&theRnd);
        registerGadget(&theMusicManager);
        registerGadget(&theFSSprite);
        registerGadget(&theFSMB);

        registerShader("Base1",              0);
        registerShader("Composite2",         0);
        registerShader("Composite3",         0);
        registerShader("AdditiveComposite2", 0);
        registerShader("Lightmap2",          2);
        registerShader("Lightmap2+s",        2);
        registerShader("SeparateOpacity1",   0);
        registerShader("GrayColor1",         0);
        registerShader("Terrain2",           0);
        registerShader("Terrain3+s_RGB",     4);
        registerShader("Grass1+s",           0);
        registerShader("Lacznik1+s_RGB",     4);
        registerShader("HueShift",           2);
        registerShader("EnvRimLighting",     5);

        return true;
    }


    ////////////////////////////////////////////////////////////////
    // Elephant Static Pool: Register a new static Gadget
    // <kao2.0058A800>
    ////////////////////////////////////////////////////////////////
    bool ElephantStaticPool::registerGadget(const Gadget* gadget)
    {
        int i;
        char* name = gadget->getStringRepresentation().getText();
        const TypeInfo* info = gadget->getType();

        if (gadgetsCount >= MAX_GADGET_INSTANCES)
        {
           throw ErrorMessage
           (
               "ElephantStaticPool: too many gadgets in pool!\n" \
               "Increase MAX_GADGET_INSTANCES(%i).",
               MAX_GADGET_INSTANCES
           );

           return false;
        }

        for (i = 0 ; i < gadgetsCount; i++)
        {
            if (gadgetsList[i] == gadget)
            {
                throw ErrorMessage
                (
                    "ElephantStaticPool: gadget %s [%s] already registered (object duplication).",
                    name,
                    info->name
                );

                return false;
            }
        }

        for (i = 0 ; i < gadgetsCount; i++)
        {
            if (0 == std::strcmp(gadgetsList[i]->getStringRepresentation().getText(), name))
            {
                throw ErrorMessage
                (
                    "ElephantStaticPool: gadget %s [%s] already registered (name duplication).",
                    name,
                    info->name
                );

                return false;
            }
        }

        for (i = 0 ; i < gadgetsCount; i++)
        {
            if (gadgetsList[i]->getType() == info)
            {
                throw ErrorMessage
                (
                    "ElephantStaticPool: gadget %s [%s] already registered (type duplication).",
                    name,
                    info->name
                );

                return false;
            }
        }

        gadgetsList[gadgetsCount] = gadget;
        gadgetsCount++;

        return true;
    }


    ////////////////////////////////////////////////////////////////
    // Elephant Static Pool: Find Gadget's list index by TypeInfo
    // <kao2.0058A9B0>
    ////////////////////////////////////////////////////////////////
    int ElephantStaticPool::findGadget(const TypeInfo* info) const
    {
        for (int i = 0; i < gadgetsCount; i++)
        {
            if (gadgetsList[i]->getType() == info)
            {
                return i;
            }
        }

        return (-1);
    }


    ////////////////////////////////////////////////////////////////
    // Elephant Static Pool: Register a new static Shader
    ////////////////////////////////////////////////////////////////
    bool ElephantStaticPool::registerShader(eString name, int params_count)
    {
        int i;

        if (shadersCount >= MAX_SHADER_INSTANCES)
        {
            throw ErrorMessage
            (
                "ElephantStaticPool: too many shaders in pool!\n" \
                "Increase MAX_SHADER_INSTANCES(%i).",
                MAX_SHADER_INSTANCES
            );

            return false;
        }

        for (i = 0 ; i < shadersCount; i++)
        {
            if (shadersList[i]->getStringRepresentation().compareExact(name))
            {
                throw ErrorMessage
                (
                    "ElephantStaticPool: shader '%s' already registered.",
                    name.getText()
                );

                return false;
            }
        }

        shadersList[shadersCount] = new eShaderDesc(name, params_count);
        shadersList[shadersCount]->incRef();
        shadersCount++;

        return true;
    }



    ////////////////////////////////////////////////////////////////
    // Elephant Static Pool: (...)
    // <kao2.0058A760>
    ////////////////////////////////////////////////////////////////
    void ElephantStaticPool::serializeGadget(Archive &ar, const Gadget** gadget) const
    {
        int i;
        const TypeInfo* type_info = nullptr;

        if (ar.isInReadMode())
        {
            ar.checkTypeInfo(&type_info);

            i = findGadget(type_info);

            if (i < 0)
            {
                throw ErrorMessage
                (
                    "ElephantStaticPoolStaticPool: static gadget \"%s\" not found.",
                    type_info->name
                );
            }
            else
            {
                (*gadget) = gadgetsList[i];
            }
        }
        else
        {
            if (nullptr != (*gadget))
            {
                type_info = (*gadget)->getType();
            }

            ar.checkTypeInfo(&type_info);
        }
    }


    ////////////////////////////////////////////////////////////////
    // Elephant Static Pool: (...)
    ////////////////////////////////////////////////////////////////
    eShaderDesc* ElephantStaticPool::getShaderDescription(eString &name) const
    {
        for (int i = 0; i < shadersCount; i++)
        {
            if (shadersList[i]->getStringRepresentation().compareExact(name))
            {
                return shadersList[i];
            }
        }

        return getDefaultShaderDescription();
    }


    ////////////////////////////////////////////////////////////////
    // Elephant Static Pool: (...)
    ////////////////////////////////////////////////////////////////
    eShaderDesc* ElephantStaticPool::getDefaultShaderDescription() const
    {
        if (shadersCount < 1)
        {
            throw ErrorMessage
            (
                "ElephantStaticPool::getDefaultShaderDescription():\n" \
                "No Shader Descriptions defined in the factory!"
            );
        }

        return shadersList[0];
    }

}
