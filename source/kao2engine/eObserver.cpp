#include <kao2engine/eObserver.h>
#include <kao2ar/Archive.h>

#include <kao2engine/ePathCamCtrl.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eObserver interface
    // <kao2.0047FD20> (constructor)
    // <kao2.0047FEA0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_OBSERVER_TYPEINFO
    (
        E_OBSERVER_ID,
        "eObserver",
        &E_TRANSFORM_TYPEINFO,
        []() -> eObject*
        {
            return new eObserver;
        }
    );

    TypeInfo* eObserver::getType() const
    {
        return &E_OBSERVER_TYPEINFO;
    }

    eObserver::eObserver()
    : eTransform()
    {
        /*[0x014C]*/ pathCtrl = nullptr;

        /*[0x0170-0x0190]*/
        look[0][0] = 0;
        look[0][1] = 1.0f;
        look[0][2] = 0;
        look[1][0] = 0;
        look[1][1] = 0;
        look[1][2] = 1.0f;
        look[2][0] = 1.0f;
        look[2][1] = 0;
        look[2][2] = 0;

        /*[0x194]*/ unknown_0194 = 0;

        /*[0x0154-0x0160]*/
        unknown_0154[0] = 200.0f;
        unknown_0154[1] = (-200.0f);
        unknown_0154[2] = (-200.0f);
        unknown_0154[3] = 200.0f;

        /*[0x0168]*/ nearPlane = 32.0f;
        /*[0x016C]*/ farPlane = 220000.0f;

        /*[0x0151]*/ unknown_0151 = 0x00;
        /*[0x0164]*/ fov = 75.0f;

        name = "Observer";

        flags |= 0x40000041;

        /*[0x0150]*/ unknown_0150 = 0x00;
    }

    eObserver::~eObserver()
    {
        pathCtrl->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // eObserver serialization
    // <kao2.004807C0>
    ////////////////////////////////////////////////////////////////
    void eObserver::serialize(Archive &ar)
    {
        /* Serialize "eNode" and "eTransform" (without "eGroup!") */

        eNode::serialize(ar);

        if (ar.isInWriteMode())
        {
            deserializationCorrection();
        }

        defaultTransform.serialize(ar);
        worldTransform.serialize(ar);

        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&ctrl, &E_CTRL_ESRP_TYPEINFO);

        if (ar.isInReadMode())
        {
            setXForm(defaultTransform);
        }

        /* [0x0151] unknown */
        ar.readOrWrite(&unknown_0151, 0x01);

        ar.readOrWrite(&(unknown_0154[0]), 0x04);
        ar.readOrWrite(&(unknown_0154[1]), 0x04);
        ar.readOrWrite(&(unknown_0154[2]), 0x04);
        ar.readOrWrite(&(unknown_0154[3]), 0x04);
        ar.readOrWrite(&fov, 0x04);
        ar.readOrWrite(&nearPlane, 0x04);
        ar.readOrWrite(&farPlane, 0x04);
        ar.readOrWrite(&(look[0][0]), 0x04);
        ar.readOrWrite(&(look[0][1]), 0x04);
        ar.readOrWrite(&(look[0][2]), 0x04);
        ar.readOrWrite(&(look[1][0]), 0x04);
        ar.readOrWrite(&(look[1][1]), 0x04);
        ar.readOrWrite(&(look[1][2]), 0x04);
        ar.readOrWrite(&(look[2][0]), 0x04);
        ar.readOrWrite(&(look[2][1]), 0x04);
        ar.readOrWrite(&(look[2][2]), 0x04);
        ar.readOrWrite(&unknown_0194, 0x04);
        ar.readOrWrite(&unknown_0198, 0x04);

        /* [0x0150] unknown */
        ar.readOrWrite(&unknown_0150, 0x01);

        /* Path Camera Controller */
        /* ( Every camera MUST have this object set !!! ) */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&pathCtrl, &E_PATHCAMCTRL_TYPEINFO);
    }


    ////////////////////////////////////////////////////////////////
    // eObserver: getters and setters
    ////////////////////////////////////////////////////////////////

    float eObserver::getFieldOfView() const
    {
        return fov;
    }

    float eObserver::getNearPlane() const
    {
        return nearPlane;
    }

    float eObserver::getFarPlane() const
    {
        return farPlane;
    }

    void eObserver::setFieldOfView(float new_fov)
    {
        fov = new_fov;
    }

    void eObserver::setNearPlane(float new_value)
    {
        nearPlane = new_value;
    }

    void eObserver::setFarPlane(float new_value)
    {
        farPlane = new_value;
    }


    ////////////////////////////////////////////////////////////////
    // eObserver: get or set ePathCamCtrl
    ////////////////////////////////////////////////////////////////

    ePathCamCtrl* eObserver::getPathCamCtrl() const
    {
        return pathCtrl;
    }

    void eObserver::setPathCamCtrl(ePathCamCtrl* new_pathctrl)
    {
        if (pathCtrl != new_pathctrl)
        {
            if (nullptr != pathCtrl)
            {
                pathCtrl->decRef();
            }

            pathCtrl = new_pathctrl;

            if (nullptr != pathCtrl)
            {
                pathCtrl->incRef();
            }
        }
    }

}
