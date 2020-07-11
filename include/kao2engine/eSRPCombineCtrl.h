#ifndef H_KAO2AR_SRPCOMBINECTRL
#define H_KAO2AR_SRPCOMBINECTRL

#include <kao2engine/eCtrl.h>
#include <kao2engine/eLeafCtrl.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSRPCombineCtrl interface
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

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            /*[[vptr]+0x28]*/ void ctrlApplyTransform(eSRP*, float) const override;

            void ctrlSetStaticKeyframe(eSRP &new_value, int param) override;

            void ctrlClearKeyframes(int anim_id) override;
            void ctrlAddKeyframe(int anim_id, float new_time, eSRP &new_data, int param) override;
    };


    ////////////////////////////////////////////////////////////////
    // eSRPCombineCtrl TypeInfo
    // <kao2.004A1720> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SRPCOMBINECTRL_ID = 0x9020;

    extern TypeInfo E_SRPCOMBINECTRL_TYPEINFO;

}

#endif
