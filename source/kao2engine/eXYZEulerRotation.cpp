#include <kao2engine/eXYZEulerRotation.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eXYZEulerRotation interface
    // <kao2.004A11F9> (constructor)
    // <kao2.004A1600> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_XYZEULERROTATION_TYPEINFO
    (
        E_XYZEULERROTATION_ID,
        "eXYZEulerRotation",
        &E_CTRL_EQUAT_TYPEINFO,
        []() -> eObject*
        {
            return new eXYZEulerRotation;
        }
    );

    TypeInfo* eXYZEulerRotation::getType()
    {
        return &E_XYZEULERROTATION_TYPEINFO;
    }

    eXYZEulerRotation::eXYZEulerRotation()
    : eCtrl<eQuat>()
    {
        /*[0x08]*/ xCtrl = nullptr;
        /*[0x0C]*/ yCtrl = nullptr;
        /*[0x10]*/ zCtrl = nullptr;
        /*[0x14]*/ unknown_14 = 0x24;
    }

    eXYZEulerRotation::~eXYZEulerRotation()
    {
        xCtrl->decRef();
        yCtrl->decRef();
        zCtrl->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // eXYZEulerRotation: animation function
    // [[vptr]+0x28] Modify "eQuat" based on current time
    // <kao2.0049FE70>
    ////////////////////////////////////////////////////////////////
    void eXYZEulerRotation::ctrlApplyTransform(eQuat* e, float time)
    {
        float x, y, z, cx, cy, cz, sx, sy, sz;

        if (nullptr != e)
        {
            /* Z-controller */

            if (nullptr != zCtrl)
            {
                zCtrl->ctrlApplyTransform(&(z), time);
            }
            else
            {
                z = 0;
            }

            /* Y-controller */

            if (nullptr != yCtrl)
            {
                yCtrl->ctrlApplyTransform(&(y), time);
            }
            else
            {
                y = 0;
            }

            /* X-controller */

            if (nullptr != xCtrl)
            {
                xCtrl->ctrlApplyTransform(&(x), time);
            }
            else
            {
                x = 0;
            }

            /* Euler rotation to Quaternion conversion */

            cx = std::cosf(x/2);
            cy = std::cosf(y/2);
            cz = std::cosf(z/2);
            sx = std::sinf(x/2);
            sz = std::sinf(y/2);
            sy = std::sinf(z/2);

            e->w = (cx * cy * cz) + (sx * sy * sz);
            e->z = (sx * cy * cz) - (cx * cy * sz);
            e->y = (cx * sy * cz) + (sx * cy * sz);
            e->x = (cx * cy * sz) - (sx * sy * cz);
        }
    }


    ////////////////////////////////////////////////////////////////
    // eXYZEulerRotation serialization
    // <kao2.004A1370>
    ////////////////////////////////////////////////////////////////
    void eXYZEulerRotation::serialize(Archive &ar)
    {
        /* X-controller */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&xCtrl, &E_LEAFCTRL_FLOAT_TYPEINFO);

        /* Y-controller */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&yCtrl, &E_LEAFCTRL_FLOAT_TYPEINFO);

        /* Z-controller */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&zCtrl, &E_LEAFCTRL_FLOAT_TYPEINFO);

        /* [0x14] unknown */
        ar.readOrWrite(&unknown_14, 0x04);
    }

}
