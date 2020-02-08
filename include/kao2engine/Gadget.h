#ifndef H_KAO2AR_GADGET
#define H_KAO2AR_GADGET

#include <kao2engine/eRefCounter.h>

namespace ZookieWizard
{
    class Actor;

    ////////////////////////////////////////////////////////////////
    // Gadget interface
    ////////////////////////////////////////////////////////////////

    class Gadget : public eRefCounter
    {

        /*** Properties ***/

        protected:

            /*[0x08]*/ Actor* unknown_08;
            /*[0x0C]*/ eString name;

        /*** Methods ***/

        public:

            Gadget();
            ~Gadget();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            eString getStringRepresentation() const override;
            eString generateScriptText() const override;

            virtual eString getDefaultGadgetName() const;
    };


    ////////////////////////////////////////////////////////////////
    // Gadget TypeInfo
    // <kao2.005980C0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_GADGET_ID = 0x00020000;

    extern TypeInfo E_GADGET_TYPEINFO;

}

#endif
