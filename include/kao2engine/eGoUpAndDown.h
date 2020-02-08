#ifndef H_KAO2AR_GOUPANDDOWN
#define H_KAO2AR_GOUPANDDOWN

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eGoUpAndDown interface
    // <kao_tw.006A05E8> (vptr)
    ////////////////////////////////////////////////////////////////

    class eGoUpAndDown : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x2C]*/

        /*** Methods ***/

        public:

            eGoUpAndDown();
            ~eGoUpAndDown();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eGoUpAndDown TypeInfo
    // <kao_tw.0056E6C0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_GOUPANDDOWN_ID = 0x4DE45EE0;

    extern TypeInfo E_GOUPANDDOWN_TYPEINFO;

}

#endif
