#ifndef H_KAO2AR_TEXTWRITER
#define H_KAO2AR_TEXTWRITER

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eTextWriter interface
    // <kao2.005CDF50> (vptr)
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

        private:

            void createFromOtherObject(const eTextWriter &other);

        public:

            eTextWriter(const eTextWriter &other);
            eTextWriter& operator = (const eTextWriter &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eTextWriter TypeInfo
    // <kao2.0041EB20> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_TEXTWRITER_ID = 0x3B238DF2;

    extern TypeInfo E_TEXTWRITER_TYPEINFO;

}

#endif
