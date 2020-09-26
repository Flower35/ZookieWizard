#ifndef H_KAO2AR_EGGSFACTORY
#define H_KAO2AR_EGGSFACTORY

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eEggsFactory interface
    // <kao2.005D46A8> (vptr)
    ////////////////////////////////////////////////////////////////

    class eEggsFactory : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x34]*/

        /*** Methods ***/

        public:

            eEggsFactory();
            ~eEggsFactory();

        private:

            void createFromOtherObject(const eEggsFactory &other);

        public:

            eEggsFactory(const eEggsFactory &other);
            eEggsFactory& operator = (const eEggsFactory &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eEggsFactory TypeInfo
    // <kao2.005068A0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_EGGSFACTORY_ID = 0x3BF54C3F;

    extern TypeInfo E_EGGSFACTORY_TYPEINFO;

}

#endif
