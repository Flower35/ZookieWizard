#ifndef H_KAO2AR_TORPEDOMODE
#define H_KAO2AR_TORPEDOMODE

#include <kao2engine/eFSOp.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eTorpedoMode interface
    // <kao2.005D2738> (vptr)
    ////////////////////////////////////////////////////////////////

    class eTorpedoMode : public eFSOp
    {

        /*** Properties ***/

        protected:

            /*[0x24]*/
            /*(...)*/
            /*[0xC0]*/

        /*** Methods ***/

        public:

            eTorpedoMode();
            ~eTorpedoMode();

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eTorpedoMode TypeInfo
    // <kao2.004CD0D0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_TORPEDOMODE_ID = 0x7074ED01;

    extern TypeInfo E_TORPEDOMODE_TYPEINFO;

}

#endif
