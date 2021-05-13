#include <ElephantBase/StaticPool.h>

namespace ZookieWizard
{
    Kao2StaticPool StaticPool;
}

#include <ElephantBase/TypeInfo.h>
#include <ElephantEngine/Gadget.h>
#include <ElephantBase/Archive.h>

////////////////////////////////////////////////////////////////
// Kao2 Static Gadgets
////////////////////////////////////////////////////////////////

#include <ElephantEngine/Log.h>
#include <ElephantEngine/Key.h>
#include <ElephantEngine/Rnd.h>
#include <ElephantEngine/eMusicManager.h>
#include <ElephantEngine/eFSSprite.h>
#include <ElephantEngine/eFSMB.h>


namespace ZookieWizard
{
    ////////////////////////////////////////////////////////////////
    //
    ////////////////////////////////////////////////////////////////

    bool Kao2StaticPool::registerStaticGadgets()
    {
        gadgetsCount = 0;

        registerGadget(&theLog);
        registerGadget(&theKey);
        registerGadget(&theRnd);
        registerGadget(&theMusicManager);
        registerGadget(&theFSSprite);
        registerGadget(&theFSMB);

        return true;
    }

    ////////////////////////////////////////////////////////////////
    //
    // <kao2.0058A800>
    ////////////////////////////////////////////////////////////////

    bool Kao2StaticPool::registerGadget(Gadget* gadget)
    {
        int i;
        char* name = gadget->getStringRepresentation().getText();
        TypeInfo* info = gadget->getType();

        if (gadgetsCount >= MAX_INSTANCES)
        {
           throw ErrorMessage
           (
               "StaticPool: too many gadgets in pool [increase MAX_INSTANCES(%i)]; ",
               MAX_INSTANCES
           );

           return false;
        }

        for (i = 0 ; i < gadgetsCount; i++)
        {
            if (list[i] == gadget)
            {
                throw ErrorMessage
                (
                    "StaticPool: gadget %s [%s] already registered (object duplication).",
                    name,
                    info->name
                );

                return false;
            }
        }

        for (i = 0 ; i < gadgetsCount; i++)
        {
            if (0 == std::strcmp(list[i]->getStringRepresentation().getText(), name))
            {
                throw ErrorMessage
                (
                    "StaticPool: gadget %s [%s] already registered (name duplication).",
                    name,
                    info->name
                );

                return false;
            }
        }

        for (i = 0 ; i < gadgetsCount; i++)
        {
            if (list[i]->getType() == info)
            {
                throw ErrorMessage
                (
                    "StaticPool: gadget %s [%s] already registered (type duplication).",
                    name,
                    info->name
                );

                return false;
            }
        }

        list[gadgetsCount] = gadget;
        gadgetsCount++;

        return true;
    }

    ////////////////////////////////////////////////////////////////
    //
    // <kao2.0058A9B0>
    ////////////////////////////////////////////////////////////////

    int Kao2StaticPool::findGadget(TypeInfo* info) const
    {
        for (int i = 0; i < gadgetsCount; i++)
        {
            if (list[i]->getType() == info)
            {
                return i;
            }
        }

        return (-1);
    }

    ////////////////////////////////////////////////////////////////
    //
    // <kao2.0058A760>
    ////////////////////////////////////////////////////////////////

    void Kao2StaticPool::serializeGadget(Archive &ar, Gadget** gadget) const
    {
        int i;
        TypeInfo* info = nullptr;

        if (ar.isInReadMode())
        {
            ar.checkTypeInfo(&info);

            i = findGadget(info);

            if (i < 0)
            {
                throw ErrorMessage
                (
                    "StaticPool: static gadget \"%s\" not found.",
                    info->name
                );
            }
            else
            {
                (*gadget) = list[i];
            }
        }
        else
        {
            if (nullptr != (*gadget))
            {
                info = (*gadget)->getType();
            }

            ar.checkTypeInfo(&info);
        }
    }

}
