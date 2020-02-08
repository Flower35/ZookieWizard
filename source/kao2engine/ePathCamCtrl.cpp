#include <kao2engine/ePathCamCtrl.h>
#include <kao2ar/Archive.h>

#include <kao2engine/eCamera.h>
#include <kao2engine/eBezierSplineNode.h>

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
        /*[0x08]*/ cam = nullptr;
        /*[0x0C]*/ bezier = nullptr;

        /*[0x10-0x18]*/
        pos[0] = 0;
        pos[1] = 0;
        pos[2] = 0;

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

    ePathCamCtrl::~ePathCamCtrl() {}


    ////////////////////////////////////////////////////////////////
    // ePathCamCtrl serialization
    // <kao2.0052A780>
    ////////////////////////////////////////////////////////////////
    void ePathCamCtrl::serialize(Archive &ar)
    {
        int32_t i;

        /* [0x08] eCamera link */
        ar.serialize((eObject**)&cam, &E_CAMERA_TYPEINFO);

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
        ar.serialize((eObject**)&bezier, &E_BEZIERSPLINENODE_TYPEINFO);

        /* [0x1C] unknown */
        ar.readOrWrite(&unknown_1C, 0x04);

        /* [0x20] unknown */
        ar.readOrWrite(&(unknown_20[0]), 0x01);

        /* [0x21] unknown */
        ar.readOrWrite(&(unknown_20[1]), 0x01);

        /* [0x10] Assumed position */
        ar.readOrWrite(&(pos[0]), 0x04);
        ar.readOrWrite(&(pos[1]), 0x04);
        ar.readOrWrite(&(pos[2]), 0x04);

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

}
