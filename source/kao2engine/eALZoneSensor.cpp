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

    TypeInfo* eALZoneSensor::getType() const
    {
        return &E_ALZONESENSOR_TYPEINFO;
    }

    eALZoneSensor::eALZoneSensor()
    : eALBox()
    {
        sensorName = "Hero";
    }

    eALZoneSensor::eALZoneSensor(eZone* zone, float* boxBound)
    : eALZoneSensor()
    {
        createAxisListEntry(zone, boxBound);
    }

    eALZoneSensor::~eALZoneSensor()
    {}


    ////////////////////////////////////////////////////////////////
    // eALZoneSensor: cloning the object
    ////////////////////////////////////////////////////////////////

    void eALZoneSensor::createFromOtherObject(const eALZoneSensor &other)
    {
        sensorName = other.sensorName;
    }

    eALZoneSensor::eALZoneSensor(const eALZoneSensor &other)
    : eALBox(other)
    {
        createFromOtherObject(other);
    }

    eALZoneSensor& eALZoneSensor::operator = (const eALZoneSensor &other)
    {
        if ((&other) != this)
        {
            eALBox::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eALZoneSensor::cloneFromMe() const
    {
        return new eALZoneSensor(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eALZoneSensor: serialization
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
