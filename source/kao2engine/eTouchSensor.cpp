#include <kao2engine/eTouchSensor.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eTouchSensor interface
    // <kao2.004BA6D0> (constructor)
    // <kao2.004BA8E0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_TOUCHSENSOR_TYPEINFO
    (
        E_TOUCHSENSOR_ID,
        "eTouchSensor",
        &E_GROUP_TYPEINFO,
        []() -> eObject*
        {
            return new eTouchSensor;
        }
    );

    TypeInfo* eTouchSensor::getType() const
    {
        return &E_TOUCHSENSOR_TYPEINFO;
    }

    eTouchSensor::eTouchSensor()
    : eGroup()
    {}

    eTouchSensor::~eTouchSensor() {}


    ////////////////////////////////////////////////////////////////
    // eTouchSensor serialization
    // <kao2.004BAAD0>
    ////////////////////////////////////////////////////////////////
    void eTouchSensor::serialize(Archive &ar)
    {
        int32_t i;
        int32_t num_tables;

        eGroup::serialize(ar);

        /* [0x4C] action tables */

        num_tables = 0x04;
        ar.readOrWrite(&num_tables, 0x04);

        for (i = 0; i < num_tables; i++)
        {
            actionTables[i].serialize(ar);
        }

        /* Other action tables `[num_tables, 4)` are already reset by default */
    }

}
