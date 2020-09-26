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

            /*[0x08]*/ Actor* parentActor;
            /*[0x0C]*/ eString name;

        /*** Methods ***/

        public:

            Gadget();
            ~Gadget();

        private:

            void createFromOtherObject(const Gadget &other);

        public:

            Gadget(const Gadget &other);
            Gadget& operator = (const Gadget &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            eString getStringRepresentation() const override;
            eString generateScriptText() const override;

            /* << Gadget >> */

            virtual eString getDefaultGadgetName() const;
    };


    ////////////////////////////////////////////////////////////////
    // Gadget TypeInfo
    // <kao2.00598090> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_GADGET_ID = 0x00020000;

    extern TypeInfo E_GADGET_TYPEINFO;

}

#endif
