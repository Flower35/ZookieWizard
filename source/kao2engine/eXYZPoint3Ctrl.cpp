#include <kao2engine/eXYZPoint3Ctrl.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eXYZPoint3Ctrl interface
    // <kao2.004A0C69> (constructor)
    // <kao2.004A10A0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_XYZPOINT3CTRL_TYPEINFO
    (
        E_XYZPOINT3CTRL_ID,
        "eXYZPoint3Ctrl",
        &E_CTRL_EPOINT3_TYPEINFO,
        []() -> eObject*
        {
            return new eXYZPoint3Ctrl;
        }
    );

    TypeInfo* eXYZPoint3Ctrl::getType()
    {
        return &E_XYZPOINT3CTRL_TYPEINFO;
    }

    eXYZPoint3Ctrl::eXYZPoint3Ctrl()
    : eCtrl<ePoint3>()
    {
        /*[0x08]*/ xCtrl = nullptr;
        /*[0x0C]*/ yCtrl = nullptr;
        /*[0x10]*/ zCtrl = nullptr;
    }

    eXYZPoint3Ctrl::~eXYZPoint3Ctrl()
    {
        xCtrl->decRef();
        yCtrl->decRef();
        zCtrl->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // eXYZPoint3Ctrl: animation function
    // [[vptr]+0x28] Modify "ePoint3" based on current time
    // <kao2.004A0D20>
    ////////////////////////////////////////////////////////////////
    void eXYZPoint3Ctrl::ctrlApplyTransform(ePoint3* e, float time)
    {
        if (nullptr != e)
        {
            /* Z-controller */

            if (nullptr != zCtrl)
            {
                zCtrl->ctrlApplyTransform(&(e->z), time);
            }
            else
            {
                e->z = 0;
            }

            /* Y-controller */

            if (nullptr != yCtrl)
            {
                yCtrl->ctrlApplyTransform(&(e->y), time);
            }
            else
            {
                e->y = 0;
            }

            /* X-controller */

            if (nullptr != xCtrl)
            {
                xCtrl->ctrlApplyTransform(&(e->x), time);
            }
            else
            {
                e->x = 0;
            }
        }
    }
    

    ////////////////////////////////////////////////////////////////
    // eXYZPoint3Ctrl serialization
    // <kao2.004A0D70>
    ////////////////////////////////////////////////////////////////
    void eXYZPoint3Ctrl::serialize(Archive &ar)
    {
        /* X-controller */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&xCtrl, &E_LEAFCTRL_FLOAT_TYPEINFO);

        /* Y-controller */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&yCtrl, &E_LEAFCTRL_FLOAT_TYPEINFO);

        /* Z-controller */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&zCtrl, &E_LEAFCTRL_FLOAT_TYPEINFO);
    }

}
