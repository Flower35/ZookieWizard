#ifndef H_KAO2AR_FLOAT
#define H_KAO2AR_FLOAT

#include <ElephantEngine/eRefCounter.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFloat interface
    ////////////////////////////////////////////////////////////////

    class eFloat : public eRefCounter
    {

        /*** Properties ***/

        protected:

            /*[0x08]*/ float value;

        /*** Methods ***/

        public:

            eFloat();
            ~eFloat();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            eString getStringRepresentation() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eFloat TypeInfo
    // <kao2.00465EC0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_FLOAT_ID = 0x1020F152;

    extern TypeInfo E_FLOAT_TYPEINFO;

}

#endif
