#ifndef H_KAO2AR_PLASZCZKA
#define H_KAO2AR_PLASZCZKA

#include <ElephantEngine/eWalk.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePlaszczka interface
    // <kao2.005CFA28> (vptr)
    ////////////////////////////////////////////////////////////////

    class ePlaszczka : public eWalk
    {
        /*** Properties ***/

        protected:

            /*[0x88]*/
            /*(...)*/
            /*[0xA0]*/

        /*** Methods ***/

        public:

            ePlaszczka();
            ~ePlaszczka();

        private:

            void createFromOtherObject(const ePlaszczka &other);

        public:

            ePlaszczka(const ePlaszczka &other);
            ePlaszczka& operator = (const ePlaszczka &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // ePlaszczka TypeInfo
    // <kao2.0044DAF0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_PLASZCZKA_ID = 0xF0C1A024;

    extern TypeInfo E_PLASZCZKA_TYPEINFO;

}

#endif
