#ifndef H_KAO2AR_MOVETO
#define H_KAO2AR_MOVETO

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eMoveTo interface
    // <kao2.005D5410> (vptr)
    ////////////////////////////////////////////////////////////////

    class eMoveTo : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x30]*/

        /*** Methods ***/

        public:

            eMoveTo();
            ~eMoveTo();

        private:

            void createFromOtherObject(const eMoveTo &other);

        public:

            eMoveTo(const eMoveTo &other);
            eMoveTo& operator = (const eMoveTo &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eMoveTo TypeInfo
    // <kao2.0051F810> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_MOVETO_ID = 0x4DE45EDF;

    extern TypeInfo E_MOVETO_TYPEINFO;

}

#endif
