#ifndef H_KAO2AR_FLOATPAIR
#define H_KAO2AR_FLOATPAIR

#include <ElephantEngine/eRefCounter.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFloatPair interface
    ////////////////////////////////////////////////////////////////

    class eFloatPair : public eRefCounter
    {

        /*** Properties ***/

        protected:

            /*[0x08-0x0C]*/ float values[2];

        /*** Methods ***/

        public:

            eFloatPair();
            ~eFloatPair();

            void serialize(Archive &ar) override;
            const TypeInfo* getType() const override;

            eString getStringRepresentation() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eFloatPair TypeInfo
    // <kao2.0058AC40> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_FLOATPAIR_ID = 0x1020F153;

    extern TypeInfo E_FLOATPAIR_TYPEINFO;

}

#endif
