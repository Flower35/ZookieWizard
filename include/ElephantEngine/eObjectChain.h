#ifndef H_KAO2AR_OBJECTCHAIN
#define H_KAO2AR_OBJECTCHAIN

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eObjectChain interface
    // <kao2.005D5858> (vptr)
    ////////////////////////////////////////////////////////////////

    class eObjectChain : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x4C]*/

        /*** Methods ***/

        public:

            eObjectChain();
            ~eObjectChain();

        private:

            void createFromOtherObject(const eObjectChain &other);

        public:

            eObjectChain(const eObjectChain &other);
            eObjectChain& operator = (const eObjectChain &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eObjectChain TypeInfo
    // <kao2.00525FC0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_OBJECTCHAIN_ID = 0x000204C4;

    extern TypeInfo E_OBJECTCHAIN_TYPEINFO;

}

#endif
