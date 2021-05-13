#ifndef H_KAO2AR_ANIMNOTYFIER
#define H_KAO2AR_ANIMNOTYFIER

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eAnimNotyfier interface
    // <kao2.005CF5F0> (vptr)
    ////////////////////////////////////////////////////////////////

    class eAnimNotyfier : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*[0x14]*/
            /*[0x18]*/

        /*** Methods ***/

        public:

            eAnimNotyfier();
            ~eAnimNotyfier();

        private:

            void createFromOtherObject(const eAnimNotyfier &other);

        public:

            eAnimNotyfier(const eAnimNotyfier &other);
            eAnimNotyfier& operator = (const eAnimNotyfier &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eAnimNotyfier TypeInfo
    // <kao2.00444E30> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_ANIMNOTYFIER_ID = 0x3B272876;

    extern TypeInfo E_ANIMNOTYFIER_TYPEINFO;

}

#endif
