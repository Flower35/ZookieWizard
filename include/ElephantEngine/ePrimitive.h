#ifndef H_KAO2AR_PRIMITIVE
#define H_KAO2AR_PRIMITIVE

#include <ElephantEngine/eRefCounter.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePrimitive interface
    // <kao2.005D0920> (vptr)
    ////////////////////////////////////////////////////////////////

    class ePrimitive : public eRefCounter
    {
        /*** Methods ***/

        public:

            ePrimitive();
            ~ePrimitive();

        private:

            void createFromOtherObject(const ePrimitive &other);

        public:

            ePrimitive(const ePrimitive &other);
            ePrimitive& operator = (const ePrimitive &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // ePrimitive TypeInfo
    // <kao2.004B9270> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_PRIMITIVE_ID = 0x00123456;

    extern TypeInfo E_PRIMITIVE_TYPEINFO;

}

#endif
