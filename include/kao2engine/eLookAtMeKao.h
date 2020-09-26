#ifndef H_KAO2AR_LOOKATMEKAO
#define H_KAO2AR_LOOKATMEKAO

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eLookAtMeKao interface
    // <kao2.005D2FC8> (vptr)
    ////////////////////////////////////////////////////////////////

    class eLookAtMeKao : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x20]*/

        /*** Methods ***/

        public:

            eLookAtMeKao();
            ~eLookAtMeKao();

        private:

            void createFromOtherObject(const eLookAtMeKao &other);

        public:

            eLookAtMeKao(const eLookAtMeKao &other);
            eLookAtMeKao& operator = (const eLookAtMeKao &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eLookAtMeKao TypeInfo
    // <kao2.004DB940> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_LOOKATMEKAO_ID = 0xAFF1AFFC;

    extern TypeInfo E_LOOKATMEKAO_TYPEINFO;

}

#endif
