#ifndef H_KAO2AR_CLONECHILD
#define H_KAO2AR_CLONECHILD

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCloneChild interface
    // <kao2.005D8880> (vptr)
    ////////////////////////////////////////////////////////////////

    class eCloneChild : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/

        /*** Methods ***/

        public:

            eCloneChild();
            ~eCloneChild();

        private:

            void createFromOtherObject(const eCloneChild &other);

        public:

            eCloneChild(const eCloneChild &other);
            eCloneChild& operator = (const eCloneChild &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eCloneChild TypeInfo
    // <kao2.005A54D0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_CLONECHILD_ID = 0x3D819CF1;

    extern TypeInfo E_CLONECHILD_TYPEINFO;

}

#endif
