#ifndef H_KAO2AR_LISAJOUX
#define H_KAO2AR_LISAJOUX

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eLisajoux interface
    // <kao2.005D70D8> (vptr)
    ////////////////////////////////////////////////////////////////

    class eLisajoux : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x50]*/

        /*** Methods ***/

        public:

            eLisajoux();
            ~eLisajoux();

        private:

            void createFromOtherObject(const eLisajoux &other);

        public:

            eLisajoux(const eLisajoux &other);
            eLisajoux& operator = (const eLisajoux &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eLisajoux TypeInfo
    // <kao2.005651E0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_LISAJOUX_ID = 0x3BEBD8FA;

    extern TypeInfo E_LISAJOUX_TYPEINFO;

}

#endif
