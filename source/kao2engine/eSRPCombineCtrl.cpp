#include <kao2engine/eSRPCombineCtrl.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSRPCombineCtrl interface
    // <kao2.004A1759> (constructor)
    // <kao2.0044B7D0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SRPCOMBINECTRL_TYPEINFO
    (
        E_SRPCOMBINECTRL_ID,
        "eSRPCombineCtrl",
        &E_CTRL_ESRP_TYPEINFO,
        []() -> eObject*
        {
            return new eSRPCombineCtrl;
        }
    );

    TypeInfo* eSRPCombineCtrl::getType()
    {
        return &E_SRPCOMBINECTRL_TYPEINFO;
    }

    eSRPCombineCtrl::eSRPCombineCtrl()
    : eCtrl<eSRP>()
    {
        /*[0x08]*/ sclCtrl = nullptr;
        /*[0x0C]*/ rotCtrl = nullptr;
        /*[0x10]*/ posCtrl = nullptr;
    }

    eSRPCombineCtrl::~eSRPCombineCtrl()
    {
        sclCtrl->decRef();
        rotCtrl->decRef();
        posCtrl->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // eSRPCombineCtrl: animation function
    // [[vptr]+0x28] Modify "eSRP" based on current time
    // <kao2.0044B480>
    ////////////////////////////////////////////////////////////////
    void eSRPCombineCtrl::ctrlApplyTransform(eSRP* e, float time)
    {
        if (nullptr != e)
        {
            /* Position controller */

            if (nullptr != posCtrl)
            {
                posCtrl->ctrlApplyTransform(&(e->pos), time);
            }
            else
            {
                e->pos = {0, 0, 0};
            }

            /* Rotation controller */

            if (nullptr != rotCtrl)
            {
                rotCtrl->ctrlApplyTransform(&(e->rot), time);
            }
            else
            {
                e->rot = {0, 0, 0, 1.0f};
            }

            /* Scale controller */

            if (nullptr != sclCtrl)
            {
                sclCtrl->ctrlApplyTransform(&(e->scale), time);
            }
            else
            {
                e->scale = 1.0f;
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eSRPCombineCtrl serialization
    // <kao2.0044B550>
    ////////////////////////////////////////////////////////////////
    void eSRPCombineCtrl::serialize(Archive &ar)
    {
        /* Scale conroller */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&sclCtrl, &E_LEAFCTRL_FLOAT_TYPEINFO);

        /* Rotation controller */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&rotCtrl, &E_CTRL_EQUAT_TYPEINFO);

        /* Position controller */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&posCtrl, &E_CTRL_EPOINT3_TYPEINFO);
    }

}
