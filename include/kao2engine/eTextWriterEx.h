#ifndef H_KAO2AR_TEXTWRITEREX
#define H_KAO2AR_TEXTWRITEREX

#include <kao2engine/eTextWriter.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eTextWriterEx interface
    ////////////////////////////////////////////////////////////////

    class eTextWriterEx : public eTextWriter
    {

        /*** Properties ***/

        protected:

            /*[0x70]*/
            /*(...)*/
            /*[0xB0]*/

        /*** Methods ***/

        public:

            eTextWriterEx();
            ~eTextWriterEx();

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eTextWriterEx TypeInfo
    // <kao2.0045B300> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_TEXTWRITEREX_ID = 0x3F39AC2F;

    extern TypeInfo E_TEXTWRITEREX_TYPEINFO;

}

#endif
