#ifndef H_KAO2AR_FOCMILL471DEFLECTOR
#define H_KAO2AR_FOCMILL471DEFLECTOR

#include <kao2engine/Gadget.h>

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

            void serialize(Archive &ar) override;
            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eFocMill471Deflector TypeInfo
    // <kao_tw.005B5D10> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_FOCMILL471DEFLECTOR_ID = 0x05072618;

    extern TypeInfo E_FOCMILL471DEFLECTOR_TYPEINFO;

}

#endif
