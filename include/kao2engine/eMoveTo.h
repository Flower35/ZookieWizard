#ifndef H_KAO2AR_MOVETO
#define H_KAO2AR_MOVETO

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eMoveTo interface
    ////////////////////////////////////////////////////////////////

    class eMoveTo : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x30]*/

        /*** Methods ***/

        public:

            eMoveTo();
            ~eMoveTo();

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eMoveTo TypeInfo
    // <kao2.0051F840> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_MOVETO_ID = 0x4DE45EDF;

    extern TypeInfo E_MOVETO_TYPEINFO;

}

#endif
