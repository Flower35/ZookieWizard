#ifndef H_KAO2AR_BASEBALLBIEG
#define H_KAO2AR_BASEBALLBIEG

#include <ElephantEngine/eSplineWalk.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eBaseballBieg interface
    // <kao2.005CFFD8> (vptr)
    ////////////////////////////////////////////////////////////////

    class eBaseballBieg : public eSplineWalk
    {
        /*** Properties ***/

        protected:

            /*[0x88]*/
            /*[0x8C]*/
            /*[0x90]*/

        /*** Methods ***/

        public:

            eBaseballBieg();
            ~eBaseballBieg();

        private:

            void createFromOtherObject(const eBaseballBieg &other);

        public:

            eBaseballBieg(const eBaseballBieg &other);
            eBaseballBieg& operator = (const eBaseballBieg &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eBaseballBieg TypeInfo
    // <kao2.0045A0F0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_BASEBALLBIEG_ID = 0x3BCFE7E9;

    extern TypeInfo E_BASEBALLBIEG_TYPEINFO;

}

#endif
