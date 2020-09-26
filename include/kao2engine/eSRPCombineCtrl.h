#ifndef H_KAO2AR_SRPCOMBINECTRL
#define H_KAO2AR_SRPCOMBINECTRL

#include <kao2engine/eCtrl.h>
#include <kao2engine/eLeafCtrl.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSRPCombineCtrl interface
    // <kao2.005CF8A4> (vptr)
    ////////////////////////////////////////////////////////////////

    class eSRPCombineCtrl : public eCtrl<eSRP>
    {
        /*** Properties ***/

        protected:

            /*[0x08]*/ eCtrl<float>* sclCtrl;
            /*[0x0C]*/ eCtrl<eQuat>* rotCtrl;
            /*[0x10]*/ eCtrl<ePoint3>* posCtrl;

        /*** Methods ***/

        public:

            eSRPCombineCtrl();
            ~eSRPCombineCtrl();

        private:

            void createFromOtherObject(const eSRPCombineCtrl &other);

        public:

            eSRPCombineCtrl(const eSRPCombineCtrl &other);
            eSRPCombineCtrl& operator = (const eSRPCombineCtrl &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            /* << eCtrl >> */

            /*[[vptr]+0x28]*/ void ctrlApplyTransform(eSRP*, float) const override;

            void ctrlSetStaticKeyframe(eSRP &new_value, int param) override;

            void ctrlClearKeyframes(int32_t anim_id) override;
            void ctrlSetLoopType(int32_t anim_id, int32_t loop_type, int32_t param) override;
            void ctrlAddKeyframe(int32_t anim_id, float new_time, eSRP &new_data, int32_t param) override;
    };


    ////////////////////////////////////////////////////////////////
    // eSRPCombineCtrl TypeInfo
    // <kao2.004A16F0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SRPCOMBINECTRL_ID = 0x9020;

    extern TypeInfo E_SRPCOMBINECTRL_TYPEINFO;

}

#endif
