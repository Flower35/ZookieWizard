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

            eCtrl();
            ~eCtrl();

        private:

            void createFromOtherObject(const eCtrl<T> &other);

        public:

            eCtrl(const eCtrl<T> &other);
            eCtrl<T>& operator = (const eCtrl<T> &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;

            /* << eCtrl >> */

            /*[[vptr]+0x24]*/ virtual T ctrlGetTransform(T, eAnimate*) const;
            /*[[vptr]+0x28]*/ virtual void ctrlApplyTransform(T*, float) const = 0;

            virtual void ctrlSetStaticKeyframe(T &new_value, int32_t param) = 0;

            virtual void ctrlClearKeyframes(int32_t anim_id) = 0;
            virtual void ctrlSetLoopType(int32_t anim_id, int32_t loop_type, int32_t param) = 0;
            virtual void ctrlAddKeyframe(int32_t anim_id, float new_time, T &new_data, int32_t param) = 0;
    };


    ////////////////////////////////////////////////////////////////
    // eCtrl<eSRP> TypeInfo
    // <kao2.004A0880> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_CTRL_ESRP_ID = 0x9002;

    extern TypeInfo E_CTRL_ESRP_TYPEINFO;


    ////////////////////////////////////////////////////////////////
    // eCtrl<ePoint3> TypeInfo
    // <kao2.004A08F0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_CTRL_EPOINT3_ID = 0x9003;

    extern TypeInfo E_CTRL_EPOINT3_TYPEINFO;


    ////////////////////////////////////////////////////////////////
    // eCtrl<eQuat> TypeInfo
    // <kao2.004A0960> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_CTRL_EQUAT_ID = 0x9005;

    extern TypeInfo E_CTRL_EQUAT_TYPEINFO;


    ////////////////////////////////////////////////////////////////
    // eCtrl<float> TypeInfo
    // <kao2.004A09D0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_CTRL_FLOAT_ID = 0x9006;

    extern TypeInfo E_CTRL_FLOAT_TYPEINFO;

}

#endif
