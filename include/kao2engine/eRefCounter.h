#ifndef H_KAO2AR_REFCOUNTER
#define H_KAO2AR_REFCOUNTER

#include <kao2ar/eObject.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eRefCounter interface
    ////////////////////////////////////////////////////////////////

    class eRefCounter : public eObject
    {

        /*** Properties ***/

        protected:

            /*[0x04]*/ int32_t referenceCount;

        /*** Methods ***/

        public:

            eRefCounter();
            ~eRefCounter();

            TypeInfo* getType() const override;

            void incRef();
            void decRef();
    };


    ////////////////////////////////////////////////////////////////
    // eRefCounter TypeInfo
    // <kao2.00463270> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_REFCOUNTER_ID = 0x200D;

    extern TypeInfo E_REFCOUNTER_TYPEINFO;

}

#endif
