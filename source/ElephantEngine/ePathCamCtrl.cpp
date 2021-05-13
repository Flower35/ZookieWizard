#include <ElephantEngine/ePathCamCtrl.h>
#include <ElephantBase/Archive.h>

#include <ElephantEngine/eCamera.h>
#include <ElephantEngine/eBezierSplineNode.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePathCamCtrl interface
    // <kao2.00529570> (constructor)
    // <kao2.00529840> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_PATHCAMCTRL_TYPEINFO
    (
        E_PATHCAMCTRL_ID,
        "ePathCamCtrl",
        &E_CAMERACTRL_TYPEINFO,
        []() -> eObject*
        {
            return new ePathCamCtrl;
        }
    );

    TypeInfo* ePathCamCtrl::getType() const
    {
        return &E_PATHCAMCTRL_TYPEINFO;
    }

    ePathCamCtrl::ePathCamCtrl()
    : eCameraCtrl()
    {
        /*[0x08]*/ camera = nullptr;
        /*[0x0C]*/ bezier = nullptr;

        /*[0x1C]*/ unknown_1C = 0;

        /*[0x20-0x23]*/
        unknown_20[0] = 0x00;
        unknown_20[1] = 0x01;
        unknown_20[2] = 0x00;
        unknown_20[3] = 0x01;

        /*[0x24]*/ unknown_24 = 0;
        /*[0x28]*/ unknown_28 = 180.0f;

        /*[0x38]*/ unknown_38 = 0;
    }

    ePathCamCtrl::~ePathCamCtrl()
    {
        bezier->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // ePathCamCtrl: cloning the object
    ////////////////////////////////////////////////////////////////

    void ePathCamCtrl::createFromOtherObject(const ePathCamCtrl &other)
    {
        /* << MUST BE RESOLVED! >> */
        camera = nullptr;

        bezier = other.bezier;
        if (nullptr != bezier)
        {
            bezier->incRef();
        }

        position = other.position;

        unknown_1C = other.unknown_1C;

        unknown_20[0] = other.unknown_20[0];
        unknown_20[1] = other.unknown_20[1];
        unknown_20[2] = other.unknown_20[2];
        unknown_20[3] = other.unknown_20[3];

        unknown_24 = other.unknown_24;

        unknown_28 = other.unknown_28;

        unknown_38 = other.unknown_38;
    }

    ePathCamCtrl::ePathCamCtrl(const ePathCamCtrl &other)
    : eCameraCtrl(other)
    {
        createFromOtherObject(other);
    }

    ePathCamCtrl& ePathCamCtrl::operator = (const ePathCamCtrl &other)
    {
        if ((&other) != this)
        {
            eCameraCtrl::operator = (other);

            /****************/

            bezier->decRef();

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* ePathCamCtrl::cloneFromMe() const
    {
        return new ePathCamCtrl(*this);
    }


    ////////////////////////////////////////////////////////////////
    // ePathCamCtrl: serialization
    // <kao2.0052A780>
    ////////////////////////////////////////////////////////////////
    void ePathCamCtrl::serialize(Archive &ar)
    {
        int32_t i;

        /* [0x08] eCamera link */
        ar.serialize((eObject**)&camera, &E_CAMERA_TYPEINFO);

        /* ASSERTION */
        if (!ar.assertLastSerializedNode(camera))
        {
            throw ErrorMessage
            (
                "ePathCamCtrl::serialize():\n" \
                "incorrect Camera linked to this PathCameraCtrl!"
            );
        }

        /* Empty object link */
        i = 0x01;
        ar.readOrWrite(&i, 0x04);
        if (0x01 != i)
        {
            throw ErrorMessage
            (
                "ePathCamCtrl::serialize():\n" \
                "non-empty object is not supported!"
            );
        }

        /* [0x38] unknown */
        ar.readOrWrite(&unknown_38, 0x04);

        /* [0x24] unknown */
        ar.readOrWrite(&unknown_24, 0x04);

        /* [0x0C] eBezierSplineNode link */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&bezier, &E_BEZIERSPLINENODE_TYPEINFO);

        /* [0x1C] unknown */
        ar.readOrWrite(&unknown_1C, 0x04);

        /* [0x20] unknown */
        ar.readOrWrite(&(unknown_20[0]), 0x01);

        /* [0x21] unknown */
        ar.readOrWrite(&(unknown_20[1]), 0x01);

        /* [0x10] Assumed initial position */
        position.serialize(ar);

        if (ar.getVersion() >= 0x7C)
        {
            /* [0x28] unknown */
            ar.readOrWrite(&unknown_28, 0x04);

            /* [0x22] unknown */
            ar.readOrWrite(&(unknown_20[2]), 0x01);

            /* [0x23] unknown */
            ar.readOrWrite(&(unknown_20[3]), 0x01);
        }
        else
        {
            unknown_28 = 180.0f;
            unknown_20[2] = 0x00;
            unknown_20[3] = 0x00;
        }
    }


    ////////////////////////////////////////////////////////////////
    // ePathCamCtrl: get or set the camera link
    ////////////////////////////////////////////////////////////////

    eCamera* ePathCamCtrl::getCameraLink() const
    {
        return camera;
    }

    void ePathCamCtrl::setCameraLink(eCamera* new_camera)
    {
        camera = new_camera;
    }


    ////////////////////////////////////////////////////////////////
    // ePathCamCtrl: get or set the bezier spline link
    ////////////////////////////////////////////////////////////////

    eBezierSplineNode* ePathCamCtrl::getBezierLink() const
    {
        return bezier;
    }

    void ePathCamCtrl::setBezierLink(eBezierSplineNode* new_bezier)
    {
        if (bezier != new_bezier)
        {
            bezier->decRef();

            bezier = new_bezier;

            if (nullptr != bezier)
            {
                bezier->incRef();
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // ePathCamCtrl: get or set the initial position
    ////////////////////////////////////////////////////////////////

    ePoint3 ePathCamCtrl::getPosition() const
    {
        return position;
    }

    void ePathCamCtrl::setPosition(ePoint3 new_position)
    {
        position = new_position;
    }

}
