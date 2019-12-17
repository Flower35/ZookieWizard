#ifndef H_KAO2AR_TEXTWRITER
#define H_KAO2AR_TEXTWRITER

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eTextWriter interface
    ////////////////////////////////////////////////////////////////

    class eTextWriter : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x6C]*/

        /*** Methods ***/

        public:

            eTextWriter();
            ~eTextWriter();

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eTextWriter TypeInfo
    // <kao2.0041EB50> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_TEXTWRITER_ID = 0x3B238DF2;

    extern TypeInfo E_TEXTWRITER_TYPEINFO;

}

#endif
