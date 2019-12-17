#ifndef H_KAO2AR_TEXTWRITERFIELDS2
#define H_KAO2AR_TEXTWRITERFIELDS2

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eTextWriterFields2 interface
    // <kao2.005D5320> (vptr)
    ////////////////////////////////////////////////////////////////

    class eTextWriterFields2 : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x30]*/

        /*** Methods ***/

        public:

            eTextWriterFields2();
            ~eTextWriterFields2();

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eTextWriterFields2 TypeInfo
    // <kao2.0051E150> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_TEXTWRITERFIELDS2_ID = 0x3A238DF4;

    extern TypeInfo E_TEXTWRITERFIELDS2_TYPEINFO;

}

#endif
