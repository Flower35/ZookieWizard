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

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eIceCubeMarks TypeInfo
    // <kao2.0055B1A0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_ICECUBEMARKS_ID = 0x3B3E6952;

    extern TypeInfo E_ICECUBEMARKS_TYPEINFO;

}

#endif
