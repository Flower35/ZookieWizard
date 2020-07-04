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
        /*[0x78]*/ attenuationConstant = 1.0f;
        /*[0x7C]*/ attenuationLinear = 0;
        /*[0x80]*/ attenuationQuadratic = 0;
    }

    eOmniLight::~eOmniLight() {}


    ////////////////////////////////////////////////////////////////
    // eOmniLight serialization
    // <kao2.0047F510>
    ////////////////////////////////////////////////////////////////
    void eOmniLight::serialize(Archive &ar)
    {
        eLight::serialize(ar);

        position.serialize(ar);

        ar.readOrWrite(&attenuationConstant, 0x04);
        ar.readOrWrite(&attenuationLinear, 0x04);
        ar.readOrWrite(&attenuationQuadratic, 0x04);
    }


    ////////////////////////////////////////////////////////////////
    // eOmniLight: get or set position
    ////////////////////////////////////////////////////////////////

    ePoint3 eOmniLight::getPosition() const
    {
        return position;
    }

    void eOmniLight::setPosition(ePoint3 &new_position)
    {
        position = new_position;
    }

}
