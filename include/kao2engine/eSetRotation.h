#ifndef H_KAO2AR_SETROTATION
#define H_KAO2AR_SETROTATION

#include <kao2engine/eLookAtCtrl.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSetRotation interface
    // <kao2.005D5718> (vptr)
    ////////////////////////////////////////////////////////////////

    class eSetRotation : public eLookAtCtrl
    {
        /*** Properties ***/

        protected:

            /*[0x28]*/
            /*(...)*/
            /*[0x34]*/

        /*** Methods ***/

        public:

            eSetRotation();
            ~eSetRotation();

        private:

            void createFromOtherObject(const eSetRotation &other);

        public:

            eSetRotation(const eSetRotation &other);
            eSetRotation& operator = (const eSetRotation &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eSetRotation TypeInfo
    // <kao2.005234B0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SETROTATION_ID = 0x3C1A9145;

    extern TypeInfo E_SETROTATION_TYPEINFO;

}

#endif
