#ifndef H_KAO2AR_MOTOROWKI
#define H_KAO2AR_MOTOROWKI

#include <kao2engine/eSplineWalk.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eMotorowki interface
    // <kao2.005D01E0> (vptr)
    ////////////////////////////////////////////////////////////////

    class eMotorowki : public eSplineWalk
    {
        /*** Properties ***/

        protected:

            /*[0x88]*/
            /*(...)*/
            /*[0xC8]*/

        /*** Methods ***/

        public:

            eMotorowki();
            ~eMotorowki();

        private:

            void createFromOtherObject(const eMotorowki &other);

        public:

            eMotorowki(const eMotorowki &other);
            eMotorowki& operator = (const eMotorowki &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eMotorowki TypeInfo
    // <kao2.0045EEB0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_MOTOROWKI_ID = 0x3A173F0E;

    extern TypeInfo E_MOTOROWKI_TYPEINFO;

}

#endif
