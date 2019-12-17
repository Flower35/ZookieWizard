#ifndef H_KAO2AR_PRIMITIVE
#define H_KAO2AR_PRIMITIVE

#include <kao2engine/eRefCounter.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePrimitive interface
    ////////////////////////////////////////////////////////////////

    class ePrimitive : public eRefCounter
    {

        /*** Methods ***/

        public:

            ePrimitive();
            ~ePrimitive();

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // ePrimitive TypeInfo
    // <kao2.004B92A0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_PRIMITIVE_ID = 0x00123456;

    extern TypeInfo E_PRIMITIVE_TYPEINFO;

}

#endif
