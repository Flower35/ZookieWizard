#ifndef H_KAO2AR_XYZEULERROTATION
#define H_KAO2AR_XYZEULERROTATION

#include <kao2engine/eCtrl.h>
#include <kao2engine/eLeafCtrl.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eXYZEulerRotation interface
    // <kao2.005D1AB8> (vptr)
    ////////////////////////////////////////////////////////////////

    class eXYZEulerRotation : public eCtrl<eQuat>
    {
        /*** Properties ***/

        protected:

            /*[0x08]*/ eLeafCtrl<float>* xCtrl;
            /*[0x0C]*/ eLeafCtrl<float>* yCtrl;
            /*[0x10]*/ eLeafCtrl<float>* zCtrl;
            /*[0x14]*/ int32_t unknown_14;

        /*** Methods ***/

        public:

            eXYZEulerRotation();
            ~eXYZEulerRotation();

        private:

            void createFromOtherObject(const eXYZEulerRotation &other);

        public:

            eXYZEulerRotation(const eXYZEulerRotation &other);
            eXYZEulerRotation& operator = (const eXYZEulerRotation &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            /* << eCtrl >> */

            /*[[vptr]+0x28]*/ void ctrlApplyTransform(eQuat*, float) const override;

            void ctrlSetStaticKeyframe(eQuat &new_value, int32_t param) override;

            void ctrlClearKeyframes(int32_t anim_id) override;
            void ctrlSetLoopType(int32_t anim_id, int32_t loop_type, int32_t param) override;
            void ctrlAddKeyframe(int32_t anim_id, float new_time, eQuat &new_data, int32_t param) override;
    };


    ////////////////////////////////////////////////////////////////
    // eXYZEulerRotation TypeInfo
    // <kao2.004A1190> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_XYZEULERROTATION_ID = 0x9040;

    extern TypeInfo E_XYZEULERROTATION_TYPEINFO;

}

#endif
