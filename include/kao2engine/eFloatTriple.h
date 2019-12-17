#ifndef H_KAO2AR_FLOATTRIPLE
#define H_KAO2AR_FLOATTRIPLE

#include <kao2engine/eRefCounter.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFloatTriple interface
    ////////////////////////////////////////////////////////////////

    class eFloatTriple : public eRefCounter
    {

        /*** Properties ***/

        protected:

            /*[0x08-0x10]*/ float values[3];

        /*** Methods ***/

        public:

            eFloatTriple();

            void serialize(Archive &ar) override;
            TypeInfo* getType() override;

            eString getStringRepresentation() override;
    };


    ////////////////////////////////////////////////////////////////
    // eFloatTriple TypeInfo
    // <kao2.0058AD20> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_FLOATTRIPLE_ID = 0x1020F154;

    extern TypeInfo E_FLOATTRIPLE_TYPEINFO;

}

#endif
