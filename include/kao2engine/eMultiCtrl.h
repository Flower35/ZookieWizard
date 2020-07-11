#ifndef H_KAO2AR_MULTICTRL
#define H_KAO2AR_MULTICTRL

#include <kao2engine/eCtrl.h>

#include <kao2ar/Collection.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eMultiCtrl interface
    ////////////////////////////////////////////////////////////////

    template <typename T>
    class eMultiCtrl : public eCtrl<T>
    {
        /*** Properties ***/

        protected:

            /*[0x08-0x10]*/ Collection<ArFunctions::serialize_eRefCounter> controllers;

        /*** Methods ***/

        public:

            eMultiCtrl<T>();
            ~eMultiCtrl<T>();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            /*[[vptr]+0x24]*/ T ctrlGetTransform(T, eAnimate*) const override;
            /*[[vptr]+0x28]*/ void ctrlApplyTransform(T*, float) const override;

            void ctrlSetStaticKeyframe(T &new_value, int32_t param) override;

            void ctrlClearKeyframes(int anim_id) override;
            void ctrlAddKeyframe(int anim_id, float new_time, T &new_data, int param) override;

            void multiCtrl_SetSize(int32_t new_size);
            void multiCtrl_SetTrack(int32_t id, void* new_controller);
            void multiCtrl_DeleteTrack(int32_t deleted_id);

    };


    ////////////////////////////////////////////////////////////////
    // eMultiCtrl<eSRPCtrl> TypeInfo
    // <kao2.004A1950> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_MULTICTRL_ESRP_ID = 0x9010;

    extern TypeInfo E_MULTICTRL_ESRP_TYPEINFO;

    ////////////////////////////////////////////////////////////////
    // eMultiCtrl<eFloatCtrl> TypeInfo
    // <kao2.004A1F50> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_MULTICTRL_FLOAT_ID = 0x9012;

    extern TypeInfo E_MULTICTRL_FLOAT_TYPEINFO;

}

#endif
