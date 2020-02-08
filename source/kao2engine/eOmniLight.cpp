#include <kao2engine/eOmniLight.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eOmniLight interface
    // <kao2.0047F130> (constructor)
    // <kao2.0047F220> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_OMNILIGHT_TYPEINFO
    (
        E_OMNILIGHT_ID,
        "eOmniLight",
        &E_LIGHT_TYPEINFO,
        []() -> eObject*
        {
            return new eOmniLight;
        }
    );

    TypeInfo* eOmniLight::getType() const
    {
        return &E_OMNILIGHT_TYPEINFO;
    }

    eOmniLight::eOmniLight()
    : eLight()
    {
        /*[0x6C]*/ direction[0] = 0;
        /*[0x70]*/ direction[1] = 0;
        /*[0x74]*/ direction[2] = 0;
        /*[0x78]*/ direction[3] = 1.0f;
        /*[0x7C]*/ direction[4] = 0;
        /*[0x80]*/ direction[5] = 0;
    }

    eOmniLight::~eOmniLight() {}


    ////////////////////////////////////////////////////////////////
    // eOmniLight serialization
    // <kao2.0047F510>
    ////////////////////////////////////////////////////////////////
    void eOmniLight::serialize(Archive &ar)
    {
        eLight::serialize(ar);

        ar.readOrWrite(&(direction[0]), 0x04);
        ar.readOrWrite(&(direction[1]), 0x04);
        ar.readOrWrite(&(direction[2]), 0x04);
        ar.readOrWrite(&(direction[3]), 0x04);
        ar.readOrWrite(&(direction[4]), 0x04);
        ar.readOrWrite(&(direction[5]), 0x04);
    }

}
