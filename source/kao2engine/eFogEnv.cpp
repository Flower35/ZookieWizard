#include <kao2engine/eFogEnv.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFogEnv interface
    // <kao2.0047E650> (constructor)
    // <kao2.0047E6E0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_FOGENV_TYPEINFO
    (
        E_FOGENV_ID,
        "eFogEnv",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return new eFogEnv;
        }
    );

    TypeInfo* eFogEnv::getType() const
    {
        return &E_FOGENV_TYPEINFO;
    }

    eFogEnv::eFogEnv()
    : eRefCounter()
    {
        /* Missing `color[3]` param in `eFogEnv` definition overlaps with `fogStart` param. */

        /*[0x08]*/ color[0] = 1.0f;
        /*[0x0C]*/ color[1] = 0;
        /*[0x10]*/ color[2] = 1.0f;
        color[3] = 1.0f;

        /*[0x14]*/ fogStart = (-1.0f);
        /*[0x18]*/ fogEnd = 1.0f;
        /*[0x1C]*/ fogMax = (-1.0f);
    }

    eFogEnv::~eFogEnv() {}


    ////////////////////////////////////////////////////////////////
    // eFogEnv serialization
    // <kao2.0047E6F0>
    ////////////////////////////////////////////////////////////////
    void eFogEnv::serialize(Archive &ar)
    {
        /* Fog color */
        ar.readOrWrite(&(color[0]), 0x04);
        ar.readOrWrite(&(color[1]), 0x04);
        ar.readOrWrite(&(color[2]), 0x04);

        /* Other fog parameters */
        ar.readOrWrite(&fogStart, 0x04);
        ar.readOrWrite(&fogEnd, 0x04);

        if (ar.getVersion() < 0x77)
        {
            fogMax = 1.0;
        }
        else
        {
            ar.readOrWrite(&fogMax, 0x04);
        }
    }

}
