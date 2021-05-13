#ifndef H_KAO2AR_STATICSND
#define H_KAO2AR_STATICSND

#include <ElephantEngine/eSnd.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eStaticSnd interface
    // <kao2.005CEFE8> (vptr)
    ////////////////////////////////////////////////////////////////

    class eStaticSnd : public eSnd
    {
        /*** Methods ***/

        public:

            eStaticSnd();
            ~eStaticSnd();

        private:

            void createFromOtherObject(const eStaticSnd &other);

        public:

            eStaticSnd(const eStaticSnd &other);
            eStaticSnd& operator = (const eStaticSnd &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eStaticSnd TypeInfo
    // <kao2.00439E20> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_STATICSND_ID = 0x39D5A029;

    extern TypeInfo E_STATICSND_TYPEINFO;

}

#endif
