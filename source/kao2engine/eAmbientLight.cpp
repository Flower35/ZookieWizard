#include <kao2engine/eAmbientLight.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eAmbientLight interface
    // <kao2.005AE430> (constructor)
    // <kao2.005AE550> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_AMBIENTLIGHT_TYPEINFO
    (
        E_AMBIENTLIGHT_ID,
        "eAmbientLight",
        &E_LIGHT_TYPEINFO,
        []() -> eObject*
        {
            return new eAmbientLight;
        }
    );

    TypeInfo* eAmbientLight::getType()
    {
        return &E_AMBIENTLIGHT_TYPEINFO;
    }

    eAmbientLight::eAmbientLight()
    : eLight()
    {
        /*[0x3C]*/ diffuse[0] = 0;
        /*[0x40]*/ diffuse[1] = 0;
        /*[0x44]*/ diffuse[2] = 0;
        /*[0x48]*/ diffuse[3] = 0;
    }

    eAmbientLight::~eAmbientLight() {}

}
