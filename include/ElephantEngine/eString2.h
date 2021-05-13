#ifndef H_KAO2AR_STRING2
#define H_KAO2AR_STRING2

#include <ElephantEngine/eRefCounter.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eString2 interface
    ////////////////////////////////////////////////////////////////

    class eString2 : public eRefCounter
    {
        /*** Properties ***/

        protected:

            /*[0x08]*/ eString str;

        /*** Methods ***/

        public:

            eString2();
            ~eString2();

            void serialize(Archive &ar) override;
            const TypeInfo* getType() const override;

            eString getStringRepresentation() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eString2 TypeInfo
    // <kao2.0058AB40> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_STRING2_ID = 0x1320F152;

    extern TypeInfo E_STRING2_TYPEINFO;

}

#endif
