#ifndef H_KAO2AR_XYZPOINT3CTRL
#define H_KAO2AR_XYZPOINT3CTRL

#include <kao2engine/eCtrl.h>
#include <kao2engine/eLeafCtrl.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eXYZPoint3Ctrl interface
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

            void serialize(Archive &ar) override;
            TypeInfo* getType() override;

            /*[[vptr]+0x28]*/ void ctrlApplyTransform(ePoint3*, float) override;
    };


    ////////////////////////////////////////////////////////////////
    // eXYZPoint3Ctrl TypeInfo
    // <kao2.004A0C30> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_XYZPOINT3CTRL_ID = 0x9030;

    extern TypeInfo E_XYZPOINT3CTRL_TYPEINFO;

}

#endif
