#ifndef H_KAO2AR_SNDEMITER
#define H_KAO2AR_SNDEMITER

#include <kao2engine/eTransform.h>

#include <kao2ar/Collection.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSndEmiter interface
    // <kao2.005D624C> (vptr)
    ////////////////////////////////////////////////////////////////

    class eSndEmiter : public eTransform
    {
        /*** Properties ***/

        protected:

            /*[0xAC-0xB4]*/ Collection<ArFunctions::serialize_eRefCounter> controllers;

        /*** Methods ***/

        public:

            eSndEmiter();
            ~eSndEmiter();

        private:

            void createFromOtherObject(const eSndEmiter &other);

        public:

            eSndEmiter(const eSndEmiter &other);
            eSndEmiter& operator = (const eSndEmiter &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;
    };


    ////////////////////////////////////////////////////////////////
    // eSndEmiter TypeInfo
    // <kao2.0056A950> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SNDEMITER_ID = 0x12345567;

    extern TypeInfo E_SNDEMITER_TYPEINFO;

}

#endif
