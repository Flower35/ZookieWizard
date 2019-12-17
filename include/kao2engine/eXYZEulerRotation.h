#ifndef H_KAO2AR_XYZEULERROTATION
#define H_KAO2AR_XYZEULERROTATION

#include <kao2engine/eCtrl.h>
#include <kao2engine/eLeafCtrl.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eXYZEulerRotation interface
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

            void serialize(Archive &ar) override;
            TypeInfo* getType() override;

            /*[[vptr]+0x28]*/ void ctrlApplyTransform(eQuat*, float) override;
    };


    ////////////////////////////////////////////////////////////////
    // eXYZEulerRotation TypeInfo
    // <kao2.004A11C0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_XYZEULERROTATION_ID = 0x9040;

    extern TypeInfo E_XYZEULERROTATION_TYPEINFO;

}

#endif
