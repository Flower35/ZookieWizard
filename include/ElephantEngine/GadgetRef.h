#ifndef H_KAO2AR_GADGETREF
#define H_KAO2AR_GADGETREF

#include <ElephantEngine/eRefCounter.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // GadgetRef interface
    // <kao_tw.006A6908> (vptr)
    ////////////////////////////////////////////////////////////////

    class GadgetRef : public eRefCounter
    {
        /*** Properties ***/

        protected:

            /*[0x08]*/ int32_t unknown_id;

        /*** Methods ***/

        public:

            GadgetRef(int32_t new_id);
            ~GadgetRef();

        private:

            void createFromOtherObject(const GadgetRef &other);

        public:

            GadgetRef(const GadgetRef &other);
            GadgetRef& operator = (const GadgetRef &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            eString getStringRepresentation() const override;
    };


    ////////////////////////////////////////////////////////////////
    // GadgetRef TypeInfo
    // <kao_tw.00627260> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_GADGETREF_ID = 0x1321F152;

    extern TypeInfo E_GADGETREF_TYPEINFO;

}

#endif
