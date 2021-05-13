#include <ElephantEngine/eTouchSensor.h>
#include <ElephantBase/Archive.h>

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

    const TypeInfo* eTouchSensor::getType() const
    {
        return &E_TOUCHSENSOR_TYPEINFO;
    }

    eTouchSensor::eTouchSensor()
    : eGroup()
    {}

    eTouchSensor::~eTouchSensor()
    {}


    ////////////////////////////////////////////////////////////////
    // eTouchSensor: cloning the object
    ////////////////////////////////////////////////////////////////

    void eTouchSensor::createFromOtherObject(const eTouchSensor &other)
    {
        for (int32_t a = 0; a < 4; a++)
        {
            actionTables[a] = other.actionTables[a];
        }
    }

    eTouchSensor::eTouchSensor(const eTouchSensor &other)
    : eGroup(other)
    {
        createFromOtherObject(other);
    }

    eTouchSensor& eTouchSensor::operator = (const eTouchSensor &other)
    {
        if ((&other) != this)
        {
            eGroup::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eTouchSensor::cloneFromMe() const
    {
        return new eTouchSensor(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eTouchSensor: serialization
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
