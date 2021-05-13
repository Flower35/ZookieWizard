#ifndef H_KAO2AR_FSOP
#define H_KAO2AR_FSOP

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFSOp interface
    // <kao2.005D6B38> (vptr)
    ////////////////////////////////////////////////////////////////

    class eFSOp : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x20]*/

        /*** Methods ***/

        public:

            eFSOp();
            ~eFSOp();

        private:

            void createFromOtherObject(const eFSOp &other);

        public:

            eFSOp(const eFSOp &other);
            eFSOp& operator = (const eFSOp &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eFSOp TypeInfo
    // <kao2.0055A000> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_FSOP_ID = 0xFF777789;

    extern TypeInfo E_FSOP_TYPEINFO;

}

#endif
