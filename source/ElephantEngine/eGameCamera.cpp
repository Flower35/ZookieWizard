#include <ElephantEngine/eGameCamera.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eGameCamera interface
    // <kao2.004D984B> (constructor)
    // <kao2.004D7EA0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_GAMECAMERA_TYPEINFO
    (
        E_GAMECAMERA_ID,
        "eGameCamera",
        &E_CAMERA_TYPEINFO,
        []() -> eObject*
        {
            return new eGameCamera("Observer");
        }
    );

    const TypeInfo* eGameCamera::getType() const
    {
        return &E_GAMECAMERA_TYPEINFO;
    }

    eGameCamera::eGameCamera(eString x)
    : eCamera()
    {
        /*[0x14]*/ name = x;
    }

    eGameCamera::~eGameCamera()
    {}


    ////////////////////////////////////////////////////////////////
    // eGameCamera: cloning the object
    ////////////////////////////////////////////////////////////////

    void eGameCamera::createFromOtherObject(const eGameCamera &other)
    {}

    eGameCamera::eGameCamera(const eGameCamera &other)
    : eCamera(other)
    {
        createFromOtherObject(other);
    }

    eGameCamera& eGameCamera::operator = (const eGameCamera &other)
    {
        if ((&other) != this)
        {
            eCamera::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eGameCamera::cloneFromMe() const
    {
        return new eGameCamera(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eGameCamera: serialization
    // <kao2.004D9190>
    ////////////////////////////////////////////////////////////////
    void eGameCamera::serialize(Archive &ar)
    {
        /* calls `eGameCamera::beginCameraDebug()` */
        /* if Debug Flag 0x2A is set, `eObserver::serialize()` is called instead of `eCamera::serialize()` */

        eCamera::serialize(ar);
    }

}
