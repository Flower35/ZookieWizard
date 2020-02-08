#ifndef H_KAO2AR_AMBIENTLIGHT
#define H_KAO2AR_AMBIENTLIGHT

#include <kao2engine/eLight.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eAmbientLight interface
    ////////////////////////////////////////////////////////////////

    class eAmbientLight : public eLight
    {

        /*** Methods ***/

        public:

            eAmbientLight();
            ~eAmbientLight();

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eAmbientLight TypeInfo
    // <kao2.005AE670> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_AMBIENTLIGHT_ID = 0x03454503;

    extern TypeInfo E_AMBIENTLIGHT_TYPEINFO;

}

#endif
