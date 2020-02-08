#ifndef H_KAO2AR_TOUCHSENSOR
#define H_KAO2AR_TOUCHSENSOR

#include <kao2engine/eGroup.h>

#include <kao2engine/eActionTable.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eTouchSensor interface
    // <kao2.005D23A0> (vptr)
    ////////////////////////////////////////////////////////////////

    class eTouchSensor : public eGroup
    {

        /*** Properties ***/

        protected:

            /*[0x48]*/
            /*[0x4C-0x98]*/ eActionTable actionTables[4];

        /*** Methods ***/

        public:

            eTouchSensor();
            ~eTouchSensor();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eTouchSensor TypeInfo
    // <kao2.004BABF0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_TOUCHSENSOR_ID = 0x0000FF01;

    extern TypeInfo E_TOUCHSENSOR_TYPEINFO;

}

#endif
