#include <kao2engine/eDirectionalLight.h>
#include <kao2ar/Archive.h>

#include <kao2engine/eTransform.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eDirectionalLight interface
    // <kao2.0047F660> (constructor)
    // <kao2.0047F750> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_DIRECTIONALLIGHT_TYPEINFO
    (
        E_DIRECTIONALLIGHT_ID,
        "eDirectionalLight",
        &E_LIGHT_TYPEINFO,
        []() -> eObject*
        {
            return new eDirectionalLight;
        }
    );

    TypeInfo* eDirectionalLight::getType()
    {
        return &E_DIRECTIONALLIGHT_TYPEINFO;
    }

    eDirectionalLight::eDirectionalLight()
    : eLight()
    {
        /*[0x6C-0x74]*/
        direction[0] = 1.0f;
        direction[1] = 0;
        direction[2] = 0;

        /*[0x78]*/ unknown_78 = nullptr;
    }

    eDirectionalLight::~eDirectionalLight()
    {
        unknown_78->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // eDirectionalLight serialization
    // <kao2.0047FBC0>
    ////////////////////////////////////////////////////////////////
    void eDirectionalLight::serialize(Archive &ar)
    {
        eLight::serialize(ar);

        ar.readOrWrite(&(direction[0]), 0x04);
        ar.readOrWrite(&(direction[1]), 0x04);
        ar.readOrWrite(&(direction[2]), 0x04);

        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&unknown_78, &E_TRANSFORM_TYPEINFO);
    }

}
