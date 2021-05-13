#ifndef H_KAO2AR_BOIDS
#define H_KAO2AR_BOIDS

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eBoids interface
    // <kao2.005CEBF0> (vptr)
    ////////////////////////////////////////////////////////////////

    class eBoids : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0xE0]*/

        /*** Methods ***/

        public:

            eBoids();
            ~eBoids();

        private:

            void createFromOtherObject(const eBoids &other);

        public:

            eBoids(const eBoids &other);
            eBoids& operator = (const eBoids &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eBoids TypeInfo
    // <kao2.00435950> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_BOIDS_ID = 0x3B061261;

    extern TypeInfo E_BOIDS_TYPEINFO;

}

#endif
