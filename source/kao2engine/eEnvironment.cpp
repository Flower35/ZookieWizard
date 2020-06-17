#include <kao2engine/eEnvironment.h>
#include <kao2ar/Archive.h>

#include <kao2engine/eFogEnv.h>
#include <kao2engine/eLight.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eEnvironment interface
    // <kao2.0047D550> (constructor)
    // <kao2.0047D810> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_ENVIRONMENT_TYPEINFO
    (
        E_ENVIRONMENT_ID,
        "eEnvironment",
        &E_GROUP_TYPEINFO,
        []() -> eObject*
        {
            return new eEnvironment("UntitledEnvironment");
        }
    );

    TypeInfo* eEnvironment::getType() const
    {
        return &E_ENVIRONMENT_TYPEINFO;
    }

    eEnvironment::eEnvironment(eString s)
    : eGroup(s, nullptr)
    {
        /*[0x54-0x60]*/
        unknown_54[0] = 0;
        unknown_54[1] = 0;
        unknown_54[2] = 0;
        unknown_54[3] = 1.0f;

        /*[0x64]*/ fog = nullptr;

    }

    eEnvironment::~eEnvironment()
    {
        /*[0x64]*/ fog->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // eEnvironment serialization
    // <kao2.0047DBA0>
    ////////////////////////////////////////////////////////////////
    void eEnvironment::serialize(Archive &ar)
    {
        eGroup::serialize(ar);

        lights.serialize(ar, &E_LIGHT_TYPEINFO);

        /* [0x54] unknown */
        ar.readOrWrite(&(unknown_54[0]), 0x04);
        ar.readOrWrite(&(unknown_54[1]), 0x04);
        ar.readOrWrite(&(unknown_54[2]), 0x04);
        ar.readOrWrite(&(unknown_54[3]), 0x04);

        if (0x1000 & flags)
        {
            if (ar.getVersion() < 0x78)
            {
                throw ErrorMessage
                (
                    "eEnvironment::serialize()\n" \
                    "ar.version() 120 required!"
                );
            }

            ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&fog, &E_FOGENV_TYPEINFO);
        }
        else
        {
            if (ar.isInReadMode())
            {
                fog->decRef();
                fog = nullptr;
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eEnvironment: find reference to some node when deleting it
    ////////////////////////////////////////////////////////////////
    void eEnvironment::findAndDereference(eNode* target)
    {
        lights.findAndDeleteChild((eRefCounter*)target);

        eGroup::findAndDereference(target);
    }


    ////////////////////////////////////////////////////////////////
    // eEnvironment: add lighting source
    ////////////////////////////////////////////////////////////////
    void eEnvironment::addLighting(eLight* new_light)
    {
        lights.appendChild(new_light);
    }

}
