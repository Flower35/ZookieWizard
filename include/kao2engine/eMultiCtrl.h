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

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            /*[[vptr]+0x24]*/ T ctrlGetTransform(T, eAnimate*) const override;
            /*[[vptr]+0x28]*/ void ctrlApplyTransform(T*, float) const override;

        private:

            int getKeyframeId(float time);

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
