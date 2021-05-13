#ifndef H_KAO2AR_FOCMILL471DEFLECTOR
#define H_KAO2AR_FOCMILL471DEFLECTOR

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFocMill471Deflector interface
    // <kao_tw.006A2B9C> (vptr)
    ////////////////////////////////////////////////////////////////

    class eFocMill471Deflector : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*[0x14]*/

        /*** Methods ***/

        public:

            eFocMill471Deflector();
            ~eFocMill471Deflector();

        private:

            void createFromOtherObject(const eFocMill471Deflector &other);

        public:

            eFocMill471Deflector(const eFocMill471Deflector &other);
            eFocMill471Deflector& operator = (const eFocMill471Deflector &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;
    };


    ////////////////////////////////////////////////////////////////
    // eFocMill471Deflector TypeInfo
    // <kao_tw.005B5CE0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_FOCMILL471DEFLECTOR_ID = 0x05072618;

    extern TypeInfo E_FOCMILL471DEFLECTOR_TYPEINFO;

}

#endif
