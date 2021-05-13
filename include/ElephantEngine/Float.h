#ifndef H_KAO2AR_FLOAT_GADGET
#define H_KAO2AR_FLOAT_GADGET

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Float interface
    // <kao2.005D8328> (vptr)
    ////////////////////////////////////////////////////////////////

    class Float : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/ float value;

        /*** Methods ***/

        public:

            Float();
            ~Float();

        private:

            void createFromOtherObject(const Float &other);

        public:

            Float(const Float &other);
            Float& operator = (const Float &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
            void serialize(Archive &ar) override;
    };


    ////////////////////////////////////////////////////////////////
    // Float TypeInfo
    // <kao2.0059ACF0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_FLOAT_GADGET_ID = 0x0002000D;

    extern TypeInfo E_FLOAT_GADGET_TYPEINFO;

}

#endif
