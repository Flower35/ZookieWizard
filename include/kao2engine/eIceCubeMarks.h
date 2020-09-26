#ifndef H_KAO2AR_ICECUBEMARKS
#define H_KAO2AR_ICECUBEMARKS

#include <kao2engine/eMarks.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eIceCubeMarks interface
    // <kao2.005D6BE0> (vptr)
    ////////////////////////////////////////////////////////////////

    class eIceCubeMarks : public eMarks
    {
        /*** Properties ***/

        protected:

            /*[0x84]*/
            /*(...)*/
            /*[0xA0]*/

        /*** Methods ***/

        public:

            eIceCubeMarks();
            ~eIceCubeMarks();

        private:

            void createFromOtherObject(const eIceCubeMarks &other);

        public:

            eIceCubeMarks(const eIceCubeMarks &other);
            eIceCubeMarks& operator = (const eIceCubeMarks &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eIceCubeMarks TypeInfo
    // <kao2.0055B170> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_ICECUBEMARKS_ID = 0x3B3E6952;

    extern TypeInfo E_ICECUBEMARKS_TYPEINFO;

}

#endif
