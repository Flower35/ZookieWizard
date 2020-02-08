#ifndef H_KAO2AR_CTRL
#define H_KAO2AR_CTRL

#include <kao2engine/eCtrlBase.h>

namespace ZookieWizard
{
    struct eAnimate;

    ////////////////////////////////////////////////////////////////
    // eCtrl interface
    ////////////////////////////////////////////////////////////////

    template <typename T>
    class eCtrl : public eCtrlBase
    {
        /*** Methods ***/

        public:

            TypeInfo* getType() const override;

            /*[vptr]+0x24]*/ virtual T ctrlGetTransform(T, eAnimate*) const;
            /*[vptr]+0x28]*/ virtual void ctrlApplyTransform(T*, float) const = 0;

    };


    ////////////////////////////////////////////////////////////////
    // eCtrl<eSRP> TypeInfo
    // <kao2.004A1940> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_CTRL_ESRP_ID = 0x9002;

    extern TypeInfo E_CTRL_ESRP_TYPEINFO;

    ////////////////////////////////////////////////////////////////
    // eCtrl<ePoint3> TypeInfo
    // <kao2.004A1910> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_CTRL_EPOINT3_ID = 0x9003;

    extern TypeInfo E_CTRL_EPOINT3_TYPEINFO;

    ////////////////////////////////////////////////////////////////
    // eCtrl<eQuat> TypeInfo
    // <kao2.004A1930> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_CTRL_EQUAT_ID = 0x9005;

    extern TypeInfo E_CTRL_EQUAT_TYPEINFO;

    ////////////////////////////////////////////////////////////////
    // eCtrl<float> TypeInfo
    // <kao2.004A1920> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_CTRL_FLOAT_ID = 0x9006;

    extern TypeInfo E_CTRL_FLOAT_TYPEINFO;

}

#endif
