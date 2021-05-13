#ifndef H_KAO2AR_MORPHERTARGET
#define H_KAO2AR_MORPHERTARGET

#include <ElephantEngine/eRefCounter.h>

#include <ElephantEngine/eGeoArray.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eMorpherTarget interface
    // <kao2.005D1A00> (vptr)
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

        private:

            void createFromOtherObject(const eMorpherTarget &other);

        public:

            eMorpherTarget(const eMorpherTarget &other);
            eMorpherTarget& operator = (const eMorpherTarget &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
            void serialize(Archive &ar) override;
    };


    ////////////////////////////////////////////////////////////////
    // eMorpherTarget TypeInfo
    // <kao2.0049EF10> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_MORPHERTARGET_ID = 0x3017;

    extern TypeInfo E_MORPHERTARGET_TYPEINFO;

}

#endif
