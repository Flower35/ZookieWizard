#ifndef H_KAO2AR_MULTIBLOCKINDEXCTRL
#define H_KAO2AR_MULTIBLOCKINDEXCTRL

#include <kao2engine/eRefCounter.h>

#include <kao2ar/Collection.h>

namespace ZookieWizard
{
    class Actor;

    ////////////////////////////////////////////////////////////////
    // eMultiBlockIndexCtrl interface
    // <kao2.005D1A48> (vptr)
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

        private:

            void createFromOtherObject(const eMultiBlockIndexCtrl &other);

        public:

            eMultiBlockIndexCtrl(const eMultiBlockIndexCtrl &other);
            eMultiBlockIndexCtrl& operator = (const eMultiBlockIndexCtrl &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;
    };


    ////////////////////////////////////////////////////////////////
    // eMultiBlockIndexCtrl TypeInfo
    // <kao2.004BD7B0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_MULTIBLOCKINDEXCTRL_ID = 0xFFFFFFFF;

    extern TypeInfo E_MULTIBLOCKINDEXCTRL_TYPEINFO;

}

#endif
