#ifndef H_KAO2AR_3FXARRAY
#define H_KAO2AR_3FXARRAY

#include <ElephantEngine/eGeoArray.h>

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

        private:

            void createFromOtherObject(const e3fXArray &other);

        public:

            e3fXArray(const e3fXArray &other);
            e3fXArray& operator = (const e3fXArray &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };

    namespace ArFunctions
    {
        void serialize_e3fXArray(Archive &ar, eGeoArray<ePoint4>** o);
    }

    ////////////////////////////////////////////////////////////////
    // e3fXArray TypeInfo
    // <kao_tw.004348A0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_3FXARRAY_ID = 0xEEEEEEDF;

    extern TypeInfo E_3FXARRAY_TYPEINFO;

}

#endif
