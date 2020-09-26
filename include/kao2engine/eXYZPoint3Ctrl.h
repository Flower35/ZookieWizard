#ifndef H_KAO2AR_XYZPOINT3CTRL
#define H_KAO2AR_XYZPOINT3CTRL

#include <kao2engine/eCtrl.h>
#include <kao2engine/eLeafCtrl.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eXYZPoint3Ctrl interface
    // <kao2.0051D1A84> (vptr)
    ////////////////////////////////////////////////////////////////

    class eXYZPoint3Ctrl : public eCtrl<ePoint3>
    {
        /*** Properties ***/

        protected:

            /*[0x08]*/ eLeafCtrl<float>* xCtrl;
            /*[0x0C]*/ eLeafCtrl<float>* yCtrl;
            /*[0x10]*/ eLeafCtrl<float>* zCtrl;

        /*** Methods ***/

        public:

            eXYZPoint3Ctrl();
            ~eXYZPoint3Ctrl();

        private:

            void createFromOtherObject(const eXYZPoint3Ctrl &other);

        public:

            eXYZPoint3Ctrl(const eXYZPoint3Ctrl &other);
            eXYZPoint3Ctrl& operator = (const eXYZPoint3Ctrl &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            /* << eCtrl >> */

            /*[[vptr]+0x28]*/ void ctrlApplyTransform(ePoint3*, float) const override;

            void ctrlSetStaticKeyframe(ePoint3 &new_value, int32_t param) override;

            void ctrlClearKeyframes(int anim_id) override;
            void ctrlSetLoopType(int32_t anim_id, int32_t loop_type, int32_t param) override;
            void ctrlAddKeyframe(int32_t anim_id, float new_time, ePoint3 &new_data, int32_t param) override;
    };


    ////////////////////////////////////////////////////////////////
    // eXYZPoint3Ctrl TypeInfo
    // <kao2.004A0C00> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_XYZPOINT3CTRL_ID = 0x9030;

    extern TypeInfo E_XYZPOINT3CTRL_TYPEINFO;

}

#endif
