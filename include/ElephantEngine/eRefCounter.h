#ifndef H_KAO2AR_REFCOUNTER
#define H_KAO2AR_REFCOUNTER

#include <ElephantBase/eObject.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eRefCounter interface
    // <kao2.005CD9A4> (vptr)
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

        private:

            void createFromOtherObject(const eRefCounter &other);

        public:

            eRefCounter(const eRefCounter &other);
            eRefCounter& operator = (const eRefCounter &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;

            /* << eRefCounter >> */

            void incRef();
            void decRef();
            int32_t getReferenceCount() const;
    };


    ////////////////////////////////////////////////////////////////
    // eRefCounter TypeInfo
    // <kao2.00463270> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_REFCOUNTER_ID = 0x200D;

    extern TypeInfo E_REFCOUNTER_TYPEINFO;

}

#endif
