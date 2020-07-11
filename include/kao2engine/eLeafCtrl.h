#ifndef H_KAO2AR_LEAFCTRL
#define H_KAO2AR_LEAFCTRL

#include <kao2engine/eCtrl.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Keyframe
    ////////////////////////////////////////////////////////////////

    template <typename T>
    struct eKeyBase
    {
        float time;
        T data[3];

        void serializeKey(Archive &ar);
    };


    ////////////////////////////////////////////////////////////////
    // eLeafCtrl interface
    ////////////////////////////////////////////////////////////////

    template <typename T>
    class eLeafCtrl : public eCtrl<T>
    {
        /*** Properties ***/

        protected:

            /*[0x08]*/ int32_t unknown_08;
            /*[0x0C]*/ int32_t unknown_0C;

            /*[0x10]*/ int32_t keysCount;
            /*[0x14]*/ int32_t keysMaxLength;
            /*[0x18]*/ eKeyBase<T>* keys;

            /*[0x1C-0x28]*/ T defaultKeyframeValue;

        /*** Methods ***/

        public:

            eLeafCtrl<T>();
            ~eLeafCtrl<T>();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            /*[[vptr]+0x28]*/ void ctrlApplyTransform(T*, float) const override;

            void ctrlSetStaticKeyframe(T &new_value, int param) override;

            void ctrlClearKeyframes(int anim_id) override;
            void ctrlAddKeyframe(int anim_id, float new_time, T &new_data, int param) override;

            void setDefaultValue(T new_value);

        private:

            int getKeyframeId(float time) const;
            T interpolate(float ratio, T &first, T &second, T &other) const;

            void clearLeafKeys();
            void addLeafKey(float new_time, T new_data);
    };


    ////////////////////////////////////////////////////////////////
    // eLeafCtrl<eFloatKey> TypeInfo
    // <kao2.004A2D50> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_LEAFCTRL_FLOAT_ID = 0xA001;

    extern TypeInfo E_LEAFCTRL_FLOAT_TYPEINFO;

    ////////////////////////////////////////////////////////////////
    // eLeafCtrl<ePoint3Key> TypeInfo
    // <kao2.004A3550> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_LEAFCTRL_EPOINT3_ID = 0xA002;

    extern TypeInfo E_LEAFCTRL_EPOINT3_TYPEINFO;

    ////////////////////////////////////////////////////////////////
    // eLeafCtrl<eRotationKey> TypeInfo
    // <kao2.004A3550> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_LEAFCTRL_EQUAT_ID = 0xA003;

    extern TypeInfo E_LEAFCTRL_EQUAT_TYPEINFO;

}

#endif
