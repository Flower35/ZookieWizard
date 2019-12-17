#ifndef H_KAO2AR_MORPHERTARGET
#define H_KAO2AR_MORPHERTARGET

#include <kao2engine/eRefCounter.h>

#include <kao2engine/eGeoArray.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eMorpherTarget interface
    ////////////////////////////////////////////////////////////////

    class eMorpherTarget : public eRefCounter
    {

        /*** Properties ***/

        protected:

            /*[0x08]*/ eGeoArray<ePoint4>* unknown_08;
            /*[0x0C]*/ eGeoArray<ePoint4>* unknown_0C;
            /*[0x10]*/ eString name;

        /*** Methods ***/

        public:

            eMorpherTarget();
            ~eMorpherTarget();

            void serialize(Archive &ar) override;
            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eMorpherTarget TypeInfo
    // <kao2.0049EF40> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_MORPHERTARGET_ID = 0x3017;

    extern TypeInfo E_MORPHERTARGET_TYPEINFO;

}

#endif
