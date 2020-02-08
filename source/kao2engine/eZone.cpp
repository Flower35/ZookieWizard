#include <kao2engine/eZone.h>
#include <kao2ar/Archive.h>

#include <kao2engine/eALZoneSensor.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eZone interface
    // <kao2.0049D4F0> (constructor)
    // <kao2.0049D830> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_ZONE_TYPEINFO
    (
        E_ZONE_ID,
        "eZone",
        &E_NODE_TYPEINFO,
        []() -> eObject*
        {
            return nullptr;
        }
    );

    TypeInfo* eZone::getType() const
    {
        return &E_ZONE_TYPEINFO;
    }

    eZone::eZone()
    : eNode()
    {
        eALZoneSensor* test_sensor;

        /*[0x64] empty group */
        /*[0x68] empty group */
        /*[0x6C] empty group */

        /*[0x1C]*/ flags |= 0x40000000;

        /*[0x14]*/ name = "Zone";

        float boxBound[6] =
        {
            0, 0, 0,
            1.0f, 1.0f, 1.0f
        };

        test_sensor = new eALZoneSensor(this, boxBound);

        /* [0x18] replace "eALZoneSensor" */

        setAxisListBox(test_sensor);
    }

    eZone::~eZone()
    {}


    ////////////////////////////////////////////////////////////////
    // eZone serialization
    // <kao2.0049DD20>
    ////////////////////////////////////////////////////////////////
    void eZone::serialize(Archive &ar)
    {
        int32_t a;

        eNode::serialize(ar);

        /* Something deprecated */
        a = 0x01;
        ar.readOrWrite(&a, 0x01);

        /* [0x64] unknown group */
        a = 0;
        ar.readOrWrite(&a, 0x04);
        if (0 != a)
        {
            throw ErrorMessage
            (
                "eZone::serialize():\n" \
                "non-empty group is not supported !!!"
            );
        }

        /* [0x3C] [0x50] Enter actions and Leave actions */
        enterActions.serialize(ar);
        leaveActions.serialize(ar);

        if (ar.isInReadMode())
        {
            flags |= 0x00000004;
        }
    }

}
