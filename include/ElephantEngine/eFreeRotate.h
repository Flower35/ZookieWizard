#ifndef H_KAO2AR_FREEROTATE
#define H_KAO2AR_FREEROTATE

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFreeRotate interface
    // <kao2.005D5958> (vptr)
    ////////////////////////////////////////////////////////////////

    class eFreeRotate : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x28]*/

        /*** Methods ***/

        public:

            eFreeRotate();
            ~eFreeRotate();

        private:

            void createFromOtherObject(const eFreeRotate &other);

        public:

            eFreeRotate(const eFreeRotate &other);
            eFreeRotate& operator = (const eFreeRotate &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eFreeRotate TypeInfo
    // <kao2.00527EF0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_FREEROTATE_ID = 0x01234322;

    extern TypeInfo E_FREEROTATE_TYPEINFO;

}

#endif
