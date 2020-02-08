#ifndef H_KAO2AR_MULTIBLOCKINDEXCTRL
#define H_KAO2AR_MULTIBLOCKINDEXCTRL

#include <kao2engine/eRefCounter.h>

#include <kao2ar/Collection.h>

namespace ZookieWizard
{
    class Actor;

    ////////////////////////////////////////////////////////////////
    // eMultiBlockIndexCtrl interface
    ////////////////////////////////////////////////////////////////

    class eMultiBlockIndexCtrl : public eRefCounter
    {

        /*** Properties ***/

        protected:

            /*[0x08]*/ Actor* actor;
            /*[0x0C-0x14]*/ Collection<ArFunctions::serialize_eRefCounter> controllers;

        /*** Methods ***/

        public:

            eMultiBlockIndexCtrl();
            ~eMultiBlockIndexCtrl();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eMultiBlockIndexCtrl TypeInfo
    // <kao2.004BD7E0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_MULTIBLOCKINDEXCTRL_ID = 0xFFFFFFFF;

    extern TypeInfo E_MULTIBLOCKINDEXCTRL_TYPEINFO;

}

#endif
