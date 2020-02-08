#ifndef H_KAO2AR_MORPHERMOD
#define H_KAO2AR_MORPHERMOD

#include <kao2engine/eModifier.h>

#include <kao2ar/Collection.h>

namespace ZookieWizard
{
    class eMultiBlockIndexCtrl;

    ////////////////////////////////////////////////////////////////
    // eMorpherMod interface
    ////////////////////////////////////////////////////////////////

    class eMorpherMod : public eModifier
    {

        /*** Properties ***/

        protected:

            /*[0x08-0x10]*/ Collection<ArFunctions::serialize_eRefCounter> targets;
            /*[0x14]*/ eMultiBlockIndexCtrl* controller;

        /*** Methods ***/

        public:

            eMorpherMod();
            ~eMorpherMod();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eMorpherMod TypeInfo
    // <kao2.0049F810> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_MORPHERMOD_ID = 0x3018;

    extern TypeInfo E_MORPHERMOD_TYPEINFO;

}

#endif
