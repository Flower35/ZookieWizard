#ifndef H_KAO2AR_CYLINDERISECTGADGET
#define H_KAO2AR_CYLINDERISECTGADGET

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCylinderIsectGadget interface
    // <kao2.005D5500> (vptr)
    ////////////////////////////////////////////////////////////////

    class eCylinderIsectGadget : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*[0x14]*/

        /*** Methods ***/

        public:

            eCylinderIsectGadget();
            ~eCylinderIsectGadget();

        private:

            void createFromOtherObject(const eCylinderIsectGadget &other);

        public:

            eCylinderIsectGadget(const eCylinderIsectGadget &other);
            eCylinderIsectGadget& operator = (const eCylinderIsectGadget &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eCylinderIsectGadget TypeInfo
    // <kao2.005213B0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_CYLINDERISECTGADGET_ID = 0x2DC4FFFF;

    extern TypeInfo E_CYLINDERISECTGADGET_TYPEINFO;

}

#endif
