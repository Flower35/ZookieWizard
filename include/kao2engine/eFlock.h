#ifndef H_KAO2AR_FLOCK
#define H_KAO2AR_FLOCK

#include <kao2engine/ePathCtrl.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFlock interface
    // <kao2.005CE750> (vptr)
    ////////////////////////////////////////////////////////////////

    class eFlock : public ePathCtrl
    {

        /*** Properties ***/

        protected:

            /*[0x50]*/ eObject* unknown_50;
            /*(...)*/
            /*[0x90]*/
            /*(...)*/
            /*[0xBC]*/

        /*** Methods ***/

        public:

            eFlock();
            ~eFlock();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eFlock TypeInfo
    // <kao2.0042DFD0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_FLOCK_ID = 0xF001A029;

    extern TypeInfo E_FLOCK_TYPEINFO;

}

#endif
