#ifndef H_KAO2AR_LEAFCTRL
#define H_KAO2AR_LEAFCTRL

#include <ElephantEngine/eCtrl.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eLeafCtrl helper definitions
    ////////////////////////////////////////////////////////////////

    #define KAO2_LEAFKEY_OORT_COUNT 6

    extern const char* theLeafOoRT[KAO2_LEAFKEY_OORT_COUNT];


    ////////////////////////////////////////////////////////////////
    // eLeafCtrl Keyframe
    ////////////////////////////////////////////////////////////////

    template <typename T>
    struct eKeyBase
    {
        /*** Properties ***/

        public:

            float time;
            T data[3];

        /*** Methods ***/

        public:

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

            /*[0x08]*/ int32_t outOfRangeTypeA;
            /*[0x0C]*/ int32_t outOfRangeTypeB;

            /*[0x10]*/ int32_t keysCount;
            /*[0x14]*/ int32_t keysMaxLength;
            /*[0x18]*/ eKeyBase<T>* keys;

            /*[0x1C-0x28]*/ T defaultKeyframeValue;

        /*** Methods ***/

        public:

            eLeafCtrl();
            ~eLeafCtrl();

        private:

            void createFromOtherObject(const eLeafCtrl<T> &other);

        public:

            eLeafCtrl(const eLeafCtrl<T> &other);
            eLeafCtrl& operator = (const eLeafCtrl<T> &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            /* << eCtrl >> */

            /*[[vptr]+0x28]*/ void ctrlApplyTransform(T*, float) const override;

            void ctrlSetStaticKeyframe(T &new_value, int param) override;

            void ctrlClearKeyframes(int32_t anim_id) override;
            void ctrlSetLoopType(int32_t anim_id, int32_t loop_type, int32_t param) override;
            void ctrlAddKeyframe(int32_t anim_id, float new_time, T &new_data, int32_t param) override;

            /* << eLeafCtrl >> */

            T getDefaultValue() const;
            void setDefaultValue(T new_value);

            int32_t getLeafLoopType(int32_t zero_if_a_otheriwse_b) const;

            int32_t getLeafKeysCount() const;
            void clearLeafKeys();
            bool getIthLeafKey(int32_t id, float &returned_time, T &returned_data);
            int32_t addLeafKey(float new_time, T new_data);
            bool removeIthLeafKey(int32_t id);

        private:

            /* << eLeafCtrl >> */

            int getKeyframeId(float time) const;
            T interpolate(float ratio, T &first, T &second, T &other) const;

            void recalculateInterpolationData();
    };


    ////////////////////////////////////////////////////////////////
    // eLeafCtrl<eFloatKey> TypeInfo
    // <kao2.004A17D0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_LEAFCTRL_FLOAT_ID = 0xA001;

    extern TypeInfo E_LEAFCTRL_FLOAT_TYPEINFO;


    ////////////////////////////////////////////////////////////////
    // eLeafCtrl<ePoint3Key> TypeInfo
    // <kao2.004A1840> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_LEAFCTRL_EPOINT3_ID = 0xA002;

    extern TypeInfo E_LEAFCTRL_EPOINT3_TYPEINFO;


    ////////////////////////////////////////////////////////////////
    // eLeafCtrl<eRotationKey> TypeInfo
    // <kao2.004A18B0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_LEAFCTRL_EQUAT_ID = 0xA003;

    extern TypeInfo E_LEAFCTRL_EQUAT_TYPEINFO;

}

#endif
