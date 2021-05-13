#ifndef H_KAO2AR_MORPHERMOD
#define H_KAO2AR_MORPHERMOD

#include <ElephantEngine/eModifier.h>

#include <ElephantBase/Collection.h>

namespace ZookieWizard
{
    class eMultiBlockIndexCtrl;

    ////////////////////////////////////////////////////////////////
    // eMorpherMod interface
    // <kao2.005D1A1C> (vptr)
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

        private:

            void createFromOtherObject(const eMorpherMod &other);

        public:

            eMorpherMod(const eMorpherMod &other);
            eMorpherMod& operator = (const eMorpherMod &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
            void serialize(Archive &ar) override;
    };


    ////////////////////////////////////////////////////////////////
    // eMorpherMod TypeInfo
    // <kao2.0049F7E0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_MORPHERMOD_ID = 0x3018;

    extern TypeInfo E_MORPHERMOD_TYPEINFO;

}

#endif
