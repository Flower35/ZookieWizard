#ifndef H_KAO2AR_GEOARRAY
#define H_KAO2AR_GEOARRAY

#include <kao2engine/eRefCounter.h>

namespace ZookieWizard
{
    ////////////////////////////////////////////////////////////////
    // eGeoArray interface
    ////////////////////////////////////////////////////////////////

    template <typename T>
    class eGeoArray : public eRefCounter
    {
        /*** Properties ***/

        protected:

            /*[0x08]*/ T* data;
            /*[0x0C]*/ int32_t length;

        /*** Methods ***/

        public:

            eGeoArray();
            ~eGeoArray();

            void serialize(Archive &ar) override;
            TypeInfo* getType() override;

            T* getData();
            int32_t getLength();

            void setup(int32_t new_length, T* new_data);
    };


    ////////////////////////////////////////////////////////////////
    // eGeoArray<ushort> TypeInfo
    // <kao2.0046FC50> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_GEOARRAY_USHORT_ID = 0xEEEEEEE0;

    extern TypeInfo E_GEOARRAY_USHORT_TYPEINFO;

    ////////////////////////////////////////////////////////////////
    // eGeoArray<ePoint2> TypeInfo
    // <kao2.0046FCC0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_GEOARRAY_EPOINT2_ID = 0xEEEEEEE1;

    extern TypeInfo E_GEOARRAY_EPOINT2_TYPEINFO;

    ////////////////////////////////////////////////////////////////
    // eGeoArray<ePoint3> TypeInfo
    // <kao2.0046FD30> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_GEOARRAY_EPOINT3_ID = 0xEEEEEEE2;

    extern TypeInfo E_GEOARRAY_EPOINT3_TYPEINFO;

    ////////////////////////////////////////////////////////////////
    // eGeoArray<ePoint4> TypeInfo
    // <kao2.0046FFC0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_GEOARRAY_EPOINT4_ID = 0xEEEEEEE3;

    extern TypeInfo E_GEOARRAY_EPOINT4_TYPEINFO;

    ////////////////////////////////////////////////////////////////
    // eGeoArray<eABB> TypeInfo
    // <kao2.004B89C0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_GEOARRAY_EABB_ID = 0xEEEEEEE4;

    extern TypeInfo E_GEOARRAY_EABB_TYPEINFO;

    ////////////////////////////////////////////////////////////////
    // eGeoArray<ePhyVertex> TypeInfo
    // <kao2.004B27E0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_GEOARRAY_EPHYVERTEX_ID = 0xEEEEEEE5;

    extern TypeInfo E_GEOARRAY_EPHYVERTEX_TYPEINFO;

}

#endif
