#include <kao2engine/eALZoneSensor.h>
#include <kao2ar/Archive.h>

#include <kao2engine/eZone.h>

#include <kao2engine/ePivot.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eALZoneSensor interface
    // <kao2.0049D0D0> (constructor)
    // <kao2.0049CEB0> (overloaded constructor)
    // <kao2.0049D080> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_ALZONESENSOR_TYPEINFO
    (
        E_ALZONESENSOR_ID,
        "eALZoneSensor",
        &E_ALBOX_TYPEINFO,
        []() -> eObject*
        {
            return new eALZoneSensor;
        }
    );

    TypeInfo* eALZoneSensor::getType()
    {
        return &E_ALZONESENSOR_TYPEINFO;
    }

    eALZoneSensor::eALZoneSensor()
    : eALBox()
    {
        sensorName = "Hero";
    }

    eALZoneSensor::eALZoneSensor(eZone* zone, float* boxBound)
    : eALBox()
    {
        sensorName = "Hero";

        prepareZone(zone, boxBound);
    }

    eALZoneSensor::~eALZoneSensor() {}


    ////////////////////////////////////////////////////////////////
    // eALZoneSensor: prepare zone
    // <kao2.004AABC0>
    ////////////////////////////////////////////////////////////////
    void eALZoneSensor::prepareZone(eZone* zone, float* boxBound)
    {
        int32_t i;
        int32_t j;

        if (nullptr != zone)
        {
            zone->setSensor(this);
        }

        unknown_0C = zone;
        unknown_08 = nullptr;

        if (unknown_8C < 2)
        {
            /* set [0x8C] (unknown) */

            if (function_004AAB60())
            {
                unknown_8C = 0x01;
            }
            else
            {
                unknown_8C = 0x00;
            }
        }

        /* Update sub-structures */

        j = 0;

        for (i = 0; i < 3; i++)
        {
            *(float*)&(test[i][0].unknown_08) = boxBound[j];
            test[i][0].unknown_0F = j;
            test[i][0].unknown_0E = false;

            j++;

            *(float*)&(test[i][1].unknown_08) = boxBound[j];
            test[i][1].unknown_0F = j;
            test[i][1].unknown_0E = true;

            j++;
        }

        if (0x02 != unknown_8C)
        {
            function_004A9CC0();
        }
        else
        {
            function_004A99C0();
        }
    }


    ////////////////////////////////////////////////////////////////
    // eALZoneSensor serialization
    // <kao2.0049D370>
    ////////////////////////////////////////////////////////////////
    void eALZoneSensor::serialize(Archive &ar)
    {
        int32_t a;
        TypeInfo* t;

        eALBox::serialize(ar);

        /* Deprecated type */
        /* Egngine suggests "Actor" TypeInfo, but levels use "ePivot" */
        t = &E_PIVOT_TYPEINFO;
        ar.checkTypeInfo(&t);

        /* Colliders */
        a = 0;
        ar.readOrWrite(&a, 0x04);
        if (0 != a)
        {
            throw ErrorMessage
            (
                "eALZoneSensore::serialize():\n" \
                "nonzero number of colliders in stream."
            );
        }

        /* Someone's name */
        if (ar.getVersion() >= 0x75)
        {
            ar.serializeString(sensorName);
        }
    }

}
