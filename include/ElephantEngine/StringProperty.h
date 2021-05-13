#ifndef H_KAO2AR_STRINGPROPERTY
#define H_KAO2AR_STRINGPROPERTY

#include <ElephantEngine/eRefCounter.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // StringProperty interface
    ////////////////////////////////////////////////////////////////

    class StringProperty : public eRefCounter
    {

        /*** Properties ***/

        protected:

            /*[0x08]*/ eString prop;
            /*[0x0C]*/ eString value;
            /*[0x10]*/ int32_t checked;
            /*[0x14]*/ bool state;

        /*** Methods ***/

        public:

            StringProperty();
            ~StringProperty();

            void serialize(Archive &ar) override;
            const TypeInfo* getType() const override;

            eString getStringRepresentation() const override;
    };


    ////////////////////////////////////////////////////////////////
    // StringProperty TypeInfo
    // <kao2.00593350> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_STRINGPROPERTY_ID = 0xFFFFFFFF;

    extern TypeInfo E_STRINGPROPERTY_TYPEINFO;

}

#endif
