#ifndef H_KAO2AR_TEXTWRITEREX
#define H_KAO2AR_TEXTWRITEREX

#include <kao2engine/eTextWriter.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eTextWriterEx interface
    // <kao2.005D0038> (vptr)
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

        private:

            void createFromOtherObject(const eTextWriterEx &other);

        public:

            eTextWriterEx(const eTextWriterEx &other);
            eTextWriterEx& operator = (const eTextWriterEx &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eTextWriterEx TypeInfo
    // <kao2.0045B2D0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_TEXTWRITEREX_ID = 0x3F39AC2F;

    extern TypeInfo E_TEXTWRITEREX_TYPEINFO;

}

#endif
