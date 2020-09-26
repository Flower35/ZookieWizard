#ifndef H_KAO2AR_SNDEMITERBOX
#define H_KAO2AR_SNDEMITERBOX

#include <kao2engine/eSndEmiter.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSndEmiterBox interface
    // <kao2.005E1130> (vptr)
    ////////////////////////////////////////////////////////////////

    class eSndEmiterBox : public eSndEmiter
    {
        /*** Properties ***/

        protected:

            /*[0xB8]*/
            /*(...)*/

            /*[0xC8-0x0D0]*/ ePoint3 boxBoundMin;
            /*[0xD4-0x0DC]*/ ePoint3 boxBoundMax;

        /*** Methods ***/

        public:

            eSndEmiterBox();
            ~eSndEmiterBox();

        private:

            void createFromOtherObject(const eSndEmiterBox &other);

        public:

            eSndEmiterBox(const eSndEmiterBox &other);
            eSndEmiterBox& operator = (const eSndEmiterBox &other);
            eObject* cloneFromMe() const override;

        /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;
    };


    ////////////////////////////////////////////////////////////////
    // eSndEmiterBox TypeInfo
    // <kao2.005AF010> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SNDEMITERBOX_ID = 0x09994524;

    extern TypeInfo E_SNDEMITERBOX_TYPEINFO;

}

#endif
