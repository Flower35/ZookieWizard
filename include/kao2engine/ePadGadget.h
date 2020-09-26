#ifndef H_KAO2AR_PADGADGET
#define H_KAO2AR_PADGADGET

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePadGadget interface
    ////////////////////////////////////////////////////////////////

    class ePadGadget : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x0010]*/
            /*(...)*/
            /*[0x0120]*/

        /*** Methods ***/

        public:

            ePadGadget();
            ~ePadGadget();

        private:

            void createFromOtherObject(const ePadGadget &other);

        public:

            ePadGadget(const ePadGadget &other);
            ePadGadget& operator = (const ePadGadget &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;

            /* << Gadget >> */

            eString getDefaultGadgetName() const override;
    };


    ////////////////////////////////////////////////////////////////
    // ePadGadget TypeInfo
    // <kao2.004C82D0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_PADGADGET_ID = 0x0002FBAD;

    extern TypeInfo E_PADGADGET_TYPEINFO;

}

#endif
