#ifndef H_KAO2AR_GRAVITATION
#define H_KAO2AR_GRAVITATION

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eGravitation interface
    // <kao2.005CF4A8> (vptr)
    ////////////////////////////////////////////////////////////////

    class eGravitation : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x50]*/

        /*** Methods ***/

        public:

            eGravitation();
            ~eGravitation();

        private:

            void createFromOtherObject(const eGravitation &other);

        public:

            eGravitation(const eGravitation &other);
            eGravitation& operator = (const eGravitation &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eGravitation TypeInfo
    // <kao2.004415B0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_GRAVITATION_ID = 0x3BD892F0;

    extern TypeInfo E_GRAVITATION_TYPEINFO;

}

#endif
