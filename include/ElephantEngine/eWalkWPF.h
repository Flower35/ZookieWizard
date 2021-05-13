#ifndef H_KAO2AR_WALKWPF
#define H_KAO2AR_WALKWPF

#include <ElephantEngine/eWalk.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eWalkWPF interface
    // <kao2.005CE240> (vptr)
    ////////////////////////////////////////////////////////////////

    class eWalkWPF : public eWalk
    {
        /*** Properties ***/

        protected:

            /*[0x88]*/
            /*(...)*/
            /*[0x94]*/

        /*** Methods ***/

        public:

            eWalkWPF();
            ~eWalkWPF();

        private:

            void createFromOtherObject(const eWalkWPF &other);

        public:

            eWalkWPF(const eWalkWPF &other);
            eWalkWPF& operator = (const eWalkWPF &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eWalkWPF TypeInfo
    // <kao2.00425720> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_WALKWPF_ID = 0xF0C10024;

    extern TypeInfo E_WALKWPF_TYPEINFO;

}

#endif
