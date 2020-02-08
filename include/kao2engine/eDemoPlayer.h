#ifndef H_KAO2AR_DEMOPLAYER
#define H_KAO2AR_DEMOPLAYER

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eDemoPlayer interface
    ////////////////////////////////////////////////////////////////

    class eDemoPlayer : public Gadget
    {

        /*** Methods ***/

        public:

            eDemoPlayer();
            ~eDemoPlayer();

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eDemoPlayer TypeInfo
    // <kao2.00458EB0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_DEMOPLAYER_ID = 0x3D3B21E9;

    extern TypeInfo E_DEMOPLAYER_TYPEINFO;

}

#endif
