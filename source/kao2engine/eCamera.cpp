#include <kao2engine/eCamera.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCamera interface
    // <kao2.0050E1A0> (constructor)
    // <kao2.0050E450> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_CAMERA_TYPEINFO
    (
        E_CAMERA_ID,
        "eCamera",
        &E_OBSERVER_TYPEINFO,
        []() -> eObject*
        {
            return new eCamera;
        }
    );

    TypeInfo* eCamera::getType() const
    {
        return &E_CAMERA_TYPEINFO;
    }

    eCamera::eCamera()
    : eObserver()
    {
        /*[0x01CC]*/ unknown_01CC = 0x01;

        /*[0x01D0]*/ target = nullptr;

        /*[0x01D8-0x01E4]*/
        unknown_01D8[0] = 80.0f;
        unknown_01D8[1] = 600.0f;
        unknown_01D8[2] = 0;
        unknown_01D8[3] = 200.0f;
    }

    eCamera::~eCamera()
    {
        target->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // eCamera serialization
    // <kao2.0050EA80>
    ////////////////////////////////////////////////////////////////
    void eCamera::serialize(Archive &ar)
    {
        int32_t i;

        eObserver::serialize(ar);

        /* Camera target point */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&target, &E_TRANSFORM_TYPEINFO);

        /* Empty object link */
        i = 0x01;
        ar.readOrWrite(&i, 0x04);
        if (0x01 != i)
        {
            throw ErrorMessage
            (
                "eCamera::serialize():\n" \
                "non-empty object is not supported!"
            );
        }

        /* [0x01DC] unknown (note: different order) */
        ar.readOrWrite(&(unknown_01D8[1]), 0x04);
        ar.readOrWrite(&(unknown_01D8[3]), 0x04);
        ar.readOrWrite(&(unknown_01D8[0]), 0x04);
        ar.readOrWrite(&(unknown_01D8[2]), 0x04);

        /* [0x01CC] unknown */
        ar.readOrWrite(&unknown_01CC, 0x01);
    }

}
