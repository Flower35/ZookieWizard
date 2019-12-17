#ifndef H_KAO2AR_TEXTRANSFORM
#define H_KAO2AR_TEXTRANSFORM

#include <kao2engine/eRefCounter.h>

#include <kao2engine/eLeafCtrl.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eTexTransform interface
    ////////////////////////////////////////////////////////////////

    class eTexTransform : public eRefCounter
    {

        /*** Properties ***/

        protected:

            /*[0x08]*/ eLeafCtrl<float>* unknown_08;
            /*[0x0C]*/ eLeafCtrl<float>* unknown_0C;
            /*[0x10]*/ eLeafCtrl<float>* unknown_10;
            /*[0x14]*/ eLeafCtrl<float>* unknown_14;

        /*** Methods ***/

        public:

            eTexTransform();
            ~eTexTransform();

            void serialize(Archive &ar) override;
            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eTexTransform TypeInfo
    // <kao2.00472DB0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_TEXTRANSFORM_ID = 0x1004;

    extern TypeInfo E_TEXTRANSFORM_TYPEINFO;

}

#endif
