#ifndef H_KAO2AR_BONUSBIEG
#define H_KAO2AR_BONUSBIEG

#include <kao2engine/eBaseballBieg.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eBonusBieg interface
    // <kao2.005CFF78> (vptr)
    ////////////////////////////////////////////////////////////////

    class eBonusBieg : public eBaseballBieg
    {

        /*** Properties ***/

        protected:

            /*[0x94]*/
            /*(...)*/
            /*[0xD4]*/

        /*** Methods ***/

        public:

            eBonusBieg();
            ~eBonusBieg();

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eBonusBieg TypeInfo
    // <kao2.00459D40> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_BONUSBIEG_ID = 0x3BCFE7E4;

    extern TypeInfo E_BONUSBIEG_TYPEINFO;

}

#endif
