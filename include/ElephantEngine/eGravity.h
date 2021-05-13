#ifndef H_KAO2AR_GRAVITY
#define H_KAO2AR_GRAVITY

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eGravity interface
    // <kao2.005D5D10> (vptr)
    ////////////////////////////////////////////////////////////////

    class eGravity : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x2C]*/

        /*** Methods ***/

        public:

            eGravity();
            ~eGravity();

        private:

            void createFromOtherObject(const eGravity &other);

        public:

            eGravity(const eGravity &other);
            eGravity& operator = (const eGravity &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eGravity TypeInfo
    // <kao2.0052FC30> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_GRAVITY_ID = 0xAAAABBBD;

    extern TypeInfo E_GRAVITY_TYPEINFO;

}

#endif
