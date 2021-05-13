#ifndef H_KAO2AR_GLOVETARGET
#define H_KAO2AR_GLOVETARGET

#include <ElephantEngine/eEggTarget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eGloveTarget interface
    // <kao2.005D45A0> (vptr)
    ////////////////////////////////////////////////////////////////

    class eGloveTarget : public eEggTarget
    {
        /*** Properties ***/

        protected:

            /*[0x38]*/

        /*** Methods ***/

        public:

            eGloveTarget();
            ~eGloveTarget();

        private:

            void createFromOtherObject(const eGloveTarget &other);

        public:

            eGloveTarget(const eGloveTarget &other);
            eGloveTarget& operator = (const eGloveTarget &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eGloveTarget TypeInfo
    // <kao2.005044E0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_GLOVETARGET_ID = 0x3DEABEDF;

    extern TypeInfo E_GLOVETARGET_TYPEINFO;

}

#endif
