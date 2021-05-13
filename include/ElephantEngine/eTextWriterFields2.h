#ifndef H_KAO2AR_TEXTWRITERFIELDS2
#define H_KAO2AR_TEXTWRITERFIELDS2

#include <ElephantEngine/Gadget.h>

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

        private:

            void createFromOtherObject(const eTextWriterFields2 &other);

        public:

            eTextWriterFields2(const eTextWriterFields2 &other);
            eTextWriterFields2& operator = (const eTextWriterFields2 &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eTextWriterFields2 TypeInfo
    // <kao2.0051E120> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_TEXTWRITERFIELDS2_ID = 0x3A238DF4;

    extern TypeInfo E_TEXTWRITERFIELDS2_TYPEINFO;

}

#endif
