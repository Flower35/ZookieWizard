#include <ElephantEngine/eFogEnv.h>
#include <ElephantBase/Archive.h>

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

    eFogEnv::~eFogEnv()
    {}


    ////////////////////////////////////////////////////////////////
    // eFogEnv: cloning the object
    ////////////////////////////////////////////////////////////////

    void eFogEnv::createFromOtherObject(const eFogEnv &other)
    {
        color[0] = other.color[0];
        color[1] = other.color[1];
        color[2] = other.color[2];
        color[3] = other.color[3];

        fogStart = other.fogStart;
        fogEnd = other.fogEnd;
        fogMax = other.fogMax;
    }

    eFogEnv::eFogEnv(const eFogEnv &other)
    : eRefCounter(other)
    {
        createFromOtherObject(other);
    }

    eFogEnv& eFogEnv::operator = (const eFogEnv &other)
    {
        if ((&other) != this)
        {
            eRefCounter::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eFogEnv::cloneFromMe() const
    {
        return new eFogEnv(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eFogEnv: serialization
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


    ////////////////////////////////////////////////////////////////
    // eFogEnv: some getters and setters
    ////////////////////////////////////////////////////////////////

    void eFogEnv::getFogColor(float* values) const
    {
        values[0] = color[0];
        values[1] = color[1];
        values[2] = color[2];
    }

    float eFogEnv::getFogStart() const
    {
        return fogStart;
    }

    float eFogEnv::getFogEnd() const
    {
        return fogEnd;
    }

    float eFogEnv::getFogMax() const
    {
        return fogMax;
    }

    void eFogEnv::setFogColor(float* values)
    {
        color[0] = values[0];
        color[1] = values[1];
        color[2] = values[2];
    }

    void eFogEnv::setFogStart(float value)
    {
        fogStart = value;
    }

    void eFogEnv::setFogEnd(float value)
    {
        fogEnd = value;
    }

    void eFogEnv::setFogMax(float value)
    {
        fogMax = value;
    }

}
