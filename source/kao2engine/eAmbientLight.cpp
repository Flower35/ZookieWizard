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

    TypeInfo* eAmbientLight::getType() const
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

    eAmbientLight::~eAmbientLight()
    {}


    ////////////////////////////////////////////////////////////////
    // eAmbientLight: cloning the object
    ////////////////////////////////////////////////////////////////

    void eAmbientLight::createFromOtherObject(const eAmbientLight &other)
    {}

    eAmbientLight::eAmbientLight(const eAmbientLight &other)
    : eLight(other)
    {
        createFromOtherObject(other);
    }

    eAmbientLight& eAmbientLight::operator = (const eAmbientLight &other)
    {
        if ((&other) != this)
        {
            eLight::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eAmbientLight::cloneFromMe() const
    {
        return new eAmbientLight(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eAmbientLight: binding function
    // [[vptr]+0x74] <kao2.005AE5C0>
    ////////////////////////////////////////////////////////////////
    void eAmbientLight::bindLight(int32_t light_id) const
    {
        useBasicLightParams(light_id);
    }

}
