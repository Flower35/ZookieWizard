#ifndef H_KAO2AR_GEOARRAY
#define H_KAO2AR_GEOARRAY

#include <ElephantEngine/eRefCounter.h>

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

        private:

            void createFromOtherObject(const eGeoArray<T> &other);

        public:

            eGeoArray(const eGeoArray<T> &other);
            eGeoArray<T>& operator = (const eGeoArray<T> &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            /* << eGeoArray >> */

            T* getData() const;
            int32_t getLength() const;

            void setup(int32_t new_length, T* new_data);
    };


    ////////////////////////////////////////////////////////////////
    // eGeoArray<ushort> TypeInfo
    // <kao2.0046FAA0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_GEOARRAY_USHORT_ID = 0xEEEEEEE0;

    extern TypeInfo E_GEOARRAY_USHORT_TYPEINFO;


    ////////////////////////////////////////////////////////////////
    // eGeoArray<ePoint2> TypeInfo
    // <kao2.0046FB10> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_GEOARRAY_EPOINT2_ID = 0xEEEEEEE1;

    extern TypeInfo E_GEOARRAY_EPOINT2_TYPEINFO;


    ////////////////////////////////////////////////////////////////
    // eGeoArray<ePoint3> TypeInfo
    // <kao2.0046FB80> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_GEOARRAY_EPOINT3_ID = 0xEEEEEEE2;

    extern TypeInfo E_GEOARRAY_EPOINT3_TYPEINFO;


    ////////////////////////////////////////////////////////////////
    // eGeoArray<ePoint4> TypeInfo
    // <kao2.0046FBF0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_GEOARRAY_EPOINT4_ID = 0xEEEEEEE3;

    extern TypeInfo E_GEOARRAY_EPOINT4_TYPEINFO;


    ////////////////////////////////////////////////////////////////
    // eGeoArray<eABB> TypeInfo
    // <kao2.004B88F0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_GEOARRAY_EABB_ID = 0xEEEEEEE4;

    extern TypeInfo E_GEOARRAY_EABB_TYPEINFO;


    ////////////////////////////////////////////////////////////////
    // eGeoArray<ePhyVertex> TypeInfo
    // <kao2.004B2600> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_GEOARRAY_EPHYVERTEX_ID = 0xEEEEEEE5;

    extern TypeInfo E_GEOARRAY_EPHYVERTEX_TYPEINFO;

}

#endif
