#ifndef H_KAO2AR_MODIFIER
#define H_KAO2AR_MODIFIER

#include <kao2engine/eRefCounter.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eModifier interface
    // <kao2.005CDE70> (vptr)
    ////////////////////////////////////////////////////////////////

    class eModifier : public eRefCounter
    {
        /*** Methods ***/

        public:

            eModifier();
            ~eModifier();

        private:

            void createFromOtherObject(const eModifier &other);

        public:

            eModifier(const eModifier &other);
            eModifier& operator = (const eModifier &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eModifier TypeInfo
    // <kao2.0046D860> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_MODIFIER_ID = 0x4004;

    extern TypeInfo E_MODIFIER_TYPEINFO;

}

#endif
