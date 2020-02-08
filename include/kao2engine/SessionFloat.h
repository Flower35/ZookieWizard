#ifndef H_KAO2AR_SESSIONFLOAT
#define H_KAO2AR_SESSIONFLOAT

#include <kao2engine/Float.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // SessionFloat interface
    // <kao2.005D8510> (vptr)
    ////////////////////////////////////////////////////////////////

    class SessionFloat : public Float
    {

        /*** Methods ***/

        public:

            SessionFloat();
            ~SessionFloat();

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // SessionFloat TypeInfo
    // <kao2.0059CC50> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SESSIONFLOAT_ID = 0x0002000E;

    extern TypeInfo E_SESSIONFLOAT_TYPEINFO;

}

#endif
