#ifndef H_KAO2AR_SNDEMITEROMNI
#define H_KAO2AR_SNDEMITEROMNI

#include <kao2engine/eSndEmiter.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSndEmiterOmni interface
    // <kao2.005D73F8> (vptr)
    ////////////////////////////////////////////////////////////////

    class eSndEmiterOmni : public eSndEmiter
    {
        /*** Properties ***/

        protected:

            /*[0xB8]*/
            /*(...)*/
            /*[0xC8]*/ float unknown_C8;
            /*[0xCC]*/ float unknown_CC;
            /*(...)*/
            /*[0xD8]*/

        /*** Methods ***/

        public:

            eSndEmiterOmni();
            ~eSndEmiterOmni();

        private:

            void createFromOtherObject(const eSndEmiterOmni &other);

        public:

            eSndEmiterOmni(const eSndEmiterOmni &other);
            eSndEmiterOmni& operator = (const eSndEmiterOmni &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;
    };


    ////////////////////////////////////////////////////////////////
    // eSndEmiterOmni TypeInfo
    // <kao2.0056CBF0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SNDEMITEROMNI_ID = 0x09994525;

    extern TypeInfo E_SNDEMITEROMNI_TYPEINFO;

}

#endif
