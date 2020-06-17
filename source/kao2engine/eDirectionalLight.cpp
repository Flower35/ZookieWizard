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

    TypeInfo* eDirectionalLight::getType() const
    {
        return &E_DIRECTIONALLIGHT_TYPEINFO;
    }

    eDirectionalLight::eDirectionalLight()
    : eLight()
    {
        /*[0x6C-0x74]*/
        position.x = 1.0f;

        /*[0x78]*/ target = nullptr;
    }

    eDirectionalLight::~eDirectionalLight()
    {
        target->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // eDirectionalLight serialization
    // <kao2.0047FBC0>
    ////////////////////////////////////////////////////////////////
    void eDirectionalLight::serialize(Archive &ar)
    {
        eLight::serialize(ar);

        position.serialize(ar);

        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&target, &E_TRANSFORM_TYPEINFO);
    }


    ////////////////////////////////////////////////////////////////
    // eDirectionalLight: get or set position
    ////////////////////////////////////////////////////////////////

    ePoint3 eDirectionalLight::getPosition() const
    {
        return position;
    }

    void eDirectionalLight::setPosition(ePoint3 &new_position)
    {
        position = new_position;
    }

}
