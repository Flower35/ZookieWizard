#ifndef H_KAO2AR_SND
#define H_KAO2AR_SND

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSnd interface
    // <kao2.005CEEC8> (vptr)
    ////////////////////////////////////////////////////////////////

    class eSnd : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x68]*/

        /*** Methods ***/

        public:

            eSnd();
            ~eSnd();

        private:

            void createFromOtherObject(const eSnd &other);

        public:

            eSnd(const eSnd &other);
            eSnd& operator = (const eSnd &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eSnd TypeInfo
    // <kao2.00439D50> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SND_ID = 0x39D5A028;

    extern TypeInfo E_SND_TYPEINFO;

}

#endif
