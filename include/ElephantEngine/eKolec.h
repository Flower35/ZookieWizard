#ifndef H_KAO2AR_KOLEC
#define H_KAO2AR_KOLEC

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eKolec interface
    // <kao2.005CFC78> (vptr)
    ////////////////////////////////////////////////////////////////

    class eKolec : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x30]*/

        /*** Methods ***/

        public:

            eKolec();
            ~eKolec();

        private:

            void createFromOtherObject(const eKolec &other);

        public:

            eKolec(const eKolec &other);
            eKolec& operator = (const eKolec &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eKolec TypeInfo
    // <kao2.00451AB0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_KOLEC_ID = 0x3D0FB836;

    extern TypeInfo E_KOLEC_TYPEINFO;

}

#endif
