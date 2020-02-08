#ifndef H_KAO2AR_BOIDS
#define H_KAO2AR_BOIDS

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eBoids interface
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

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eBoids TypeInfo
    // <kao2.00435980> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_BOIDS_ID = 0x3B061261;

    extern TypeInfo E_BOIDS_TYPEINFO;

}

#endif
