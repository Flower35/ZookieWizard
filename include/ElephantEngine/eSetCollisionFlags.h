#ifndef H_KAO2AR_SETCOLLISIONFLAGS
#define H_KAO2AR_SETCOLLISIONFLAGS

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSetCollisionFlags interface
    // <kao2.005D82D8> (vptr)
    ////////////////////////////////////////////////////////////////

    class eSetCollisionFlags : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/

        /*** Methods ***/

        public:

            eSetCollisionFlags();
            ~eSetCollisionFlags();

        private:

            void createFromOtherObject(const eSetCollisionFlags &other);

        public:

            eSetCollisionFlags(const eSetCollisionFlags &other);
            eSetCollisionFlags& operator = (const eSetCollisionFlags &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eSetCollisionFlags TypeInfo
    // <kao2.0059A2A0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SETCOLLISIONFLAGS_ID = 0x0002FCC2;

    extern TypeInfo E_SETCOLLISIONFLAGS_TYPEINFO;

}

#endif
