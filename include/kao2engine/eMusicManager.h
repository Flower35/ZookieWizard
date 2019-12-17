#ifndef H_KAO2AR_MUSICMANAGER
#define H_KAO2AR_MUSICMANAGER

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eMusicManager interface
    ////////////////////////////////////////////////////////////////

    class eMusicManager : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x0010]*/
            /*(...)*/
            /*[0x308]*/

        /*** Methods ***/

        public:

            eMusicManager();
            ~eMusicManager();

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eMusicManager TypeInfo
    // <kao2.0041D040> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_MUSICMANAGER_ID = 0xFF8A7791;

    extern TypeInfo E_MUSICMANAGER_TYPEINFO;

    
    ////////////////////////////////////////////////////////////////
    // Static Gadget
    ////////////////////////////////////////////////////////////////

    extern eMusicManager theMusicManager;

}

#endif
