#ifndef H_KAO2AR_3FXARRAY
#define H_KAO2AR_3FXARRAY

#include <kao2engine/eGeoArray.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // e3fXArray interface
    // <kao_tw.00698B34> (vptr)
    ////////////////////////////////////////////////////////////////

    class e3fXArray : public eGeoArray<ePoint4>
    {

        /*** Methods ***/

        public:

            e3fXArray();
            ~e3fXArray();

            TypeInfo* getType() override;
    };

    namespace ArFunctions
    {
        void serialize_e3fXArray(Archive &ar, eGeoArray<ePoint4>** o);
    }

    ////////////////////////////////////////////////////////////////
    // e3fXArray TypeInfo
    // <kao_tw.004348D0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_3FXARRAY_ID = 0xEEEEEEDF;

    extern TypeInfo E_3FXARRAY_TYPEINFO;

}

#endif
