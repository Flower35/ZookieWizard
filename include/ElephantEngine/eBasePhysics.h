#ifndef H_KAO2AR_BASEPHYSICS
#define H_KAO2AR_BASEPHYSICS

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eBasePhysics interface
    // <kao2.005D3068> (vptr)
    ////////////////////////////////////////////////////////////////

    class eBasePhysics : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x0010]*/
            /*(...)*/
            /*[0x0750]*/

        /*** Methods ***/

        public:

            eBasePhysics();
            ~eBasePhysics();

        private:

            void createFromOtherObject(const eBasePhysics &other);

        public:

            eBasePhysics(const eBasePhysics &other);
            eBasePhysics& operator = (const eBasePhysics &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;

            /* << Gadget >> */

            eString getDefaultGadgetName() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eBasePhysics TypeInfo
    // <kao2.004DC8D0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_BASEPHYSICS_ID = 0x0002DF00;

    extern TypeInfo E_BASEPHYSICS_TYPEINFO;

}

#endif
