#ifndef H_KAO2AR_PADROT
#define H_KAO2AR_PADROT

#include <ElephantEngine/eLookAtCtrl.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePadRot interface
    // <kao2.005D3018> (vptr)
    ////////////////////////////////////////////////////////////////

    class ePadRot : public eLookAtCtrl
    {
        /*** Properties ***/

        protected:

            /*[0x2C]*/
            /*(...)*/
            /*[0x54]*/

        /*** Methods ***/

        public:

            ePadRot();
            ~ePadRot();

        private:

            void createFromOtherObject(const ePadRot &other);

        public:

            ePadRot(const ePadRot &other);
            ePadRot& operator = (const ePadRot &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // ePadRot TypeInfo
    // <kao2.004DBD70> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_PADROT_ID = 0x3C1A9105;

    extern TypeInfo E_PADROT_TYPEINFO;

}

#endif
