#ifndef H_KAO2AR_MARKS
#define H_KAO2AR_MARKS

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eMarks interface
    // <kao2.005D6B88> (vptr)
    ////////////////////////////////////////////////////////////////

    class eMarks : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x80]*/

        /*** Methods ***/

        public:

            eMarks();
            ~eMarks();

        private:

            void createFromOtherObject(const eMarks &other);

        public:

            eMarks(const eMarks &other);
            eMarks& operator = (const eMarks &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eMarks TypeInfo
    // <kao2.0055B0A0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_MARKS_ID = 0x3B3E6951;

    extern TypeInfo E_MARKS_TYPEINFO;

}

#endif
