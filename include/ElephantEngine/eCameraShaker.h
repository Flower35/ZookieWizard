#ifndef H_KAO2AR_CAMERASHAKER
#define H_KAO2AR_CAMERASHAKER

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCameraShaker interface
    // <kao2.005D2C68> (vptr)
    ////////////////////////////////////////////////////////////////

    class eCameraShaker : public Gadget
    {
        /*** Methods ***/

        public:

            eCameraShaker();
            ~eCameraShaker();

        private:

            void createFromOtherObject(const eCameraShaker &other);

        public:

            eCameraShaker(const eCameraShaker &other);
            eCameraShaker& operator = (const eCameraShaker &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eCameraShaker TypeInfo
    // <kao2.004D5980> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_CAMERASHAKER_ID = 0xCA3E7A11;

    extern TypeInfo E_CAMERASHAKER_TYPEINFO;

}

#endif
