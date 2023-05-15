#include <ElephantEngine/eNPCMap.h>
#include <ElephantBase/Archive.h>
#include <ElephantBase/eDrawContext.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eNPCMap interface
    // <kao2.0041FF10> (constructor)
    // <kao2.004201E0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_NPCMAP_TYPEINFO
    (
        E_NPCMAP_ID,
        "eNPCMap",
        &E_GROUP_TYPEINFO,
        []() -> eObject*
        {
            return new eNPCMap;
        }
    );

    const TypeInfo* eNPCMap::getType() const
    {
        return &E_NPCMAP_TYPEINFO;
    }

    eNPCMap::eNPCMap()
    : eGroup()
    {
        /*[0x9C]*/ groupA_Count = 0;
        /*[0xA0]*/ groupA_MaxLength = 0;
        /*[0xA4]*/ groupA = nullptr;

        /*[0x54]*/ unknown_54 = 60.0f;

        /*[0x4C]*/ unknown_4C = 1;
        /*[0x50]*/ unknown_50 = 1;
        /*[0x60]*/ unknown_60 = new int32_t [1];

        /*[0x1C]*/ flags |= 0x10000000;

        /*[0x48]*/ unknown_48 = 0x00;
    }

    eNPCMap::~eNPCMap()
    {
        if (nullptr != unknown_60)
        {
            delete[](unknown_60);
        }

        if (nullptr != groupA)
        {
            delete[](groupA);
        }
    }


    ////////////////////////////////////////////////////////////////
    // eNPCMap: cloning the object
    ////////////////////////////////////////////////////////////////

    void eNPCMap::createFromOtherObject(const eNPCMap &other)
    {
        unknown_4C = other.unknown_4C;
        unknown_50 = other.unknown_50;

        boxBoundMin = other.boxBoundMin;
        boxBoundMax = other.boxBoundMax;

        unknown_54 = other.unknown_54;
        unknown_58 = other.unknown_58;
        unknown_5C = other.unknown_5C;

        /****************/

        if (other.groupA_Count > 0)
        {
            groupA_MaxLength = other.groupA_Count;
            groupA = new int32_t [groupA_MaxLength];

            for (groupA_Count = 0; groupA_Count < groupA_MaxLength; groupA_Count++)
            {
                groupA[groupA_Count] = other.groupA[groupA_Count];
            }
        }
        else
        {
            groupA_Count = 0;
            groupA_MaxLength = 0;
            groupA = nullptr;
        }

        /****************/

        int32_t a = unknown_50 * unknown_4C;
        unknown_60 = new int32_t [a];

        if (nullptr != other.unknown_60)
        {
            std::memcpy(unknown_60, other.unknown_60, sizeof(int32_t) * a);
        }
        else
        {
            std::memset(unknown_60, 0x00, sizeof(int32_t) * a);
        }

        /****************/

        unknown_7C = other.unknown_7C;

        navisCount = other.navisCount;

        unknown_AC = other.unknown_AC;

        unknown_48 = other.unknown_48;
    }

    eNPCMap::eNPCMap(const eNPCMap &other)
    : eGroup(other)
    {
        createFromOtherObject(other);
    }

    eNPCMap& eNPCMap::operator = (const eNPCMap &other)
    {
        if ((&other) != this)
        {
            eGroup::operator = (other);

            /****************/

            if (nullptr != unknown_60)
            {
                delete[](unknown_60);
            }

            if (nullptr != groupA)
            {
                delete[](groupA);
            }

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eNPCMap::cloneFromMe() const
    {
        return new eNPCMap(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eNPCMap: serialization
    // <kao2.00420DC0>
    ////////////////////////////////////////////////////////////////
    void eNPCMap::serialize(Archive &ar)
    {
        int32_t i;

        eGroup::serialize(ar);

        /* [0x4C] unknown values */

        ar.readOrWrite(&unknown_4C, 0x04);
        ar.readOrWrite(&unknown_50, 0x04);

        /* [0x64] unknown (3 floats) */

        boxBoundMin.serialize(ar);

        /* [0x70] unknown (3 floats) */

        boxBoundMax.serialize(ar);

        /* [0x54] unknown values */

        ar.readOrWrite(&unknown_54, 0x04);
        ar.readOrWrite(&unknown_58, 0x04);
        ar.readOrWrite(&unknown_5C, 0x04);

        /* [0x9C] unknown group */

        if (ar.isInReadMode())
        {
            if (nullptr != groupA)
            {
                delete[](groupA);
                groupA = nullptr;

                groupA_Count = 0;
                groupA_MaxLength = 0;
            }

            ar.readOrWrite(&groupA_MaxLength, 0x04);

            if (0 != groupA_MaxLength)
            {
                groupA = new int32_t [groupA_MaxLength];

                for (i = 0; i < groupA_MaxLength; i++)
                {
                    ar.readOrWrite(&(groupA[i]), 0x04);

                    groupA_Count = (i+1);
                }
            }
        }
        else
        {
            ar.readOrWrite(&groupA_Count, 0x04);

            for (i = 0; i < groupA_Count; i++)
            {
                ar.readOrWrite(&(groupA[i]), 0x04);
            }
        }

        /* [0x64] DUPLICATE SERIALIZATION */

        boxBoundMin.serialize(ar);

        /* [0x70] DUPLICATE SERIALIZATION */

        boxBoundMax.serialize(ar);

        /* [0x60] unknown series */

        i = unknown_50 * unknown_4C;

        if (ar.isInReadMode())
        {
            if (nullptr != unknown_60)
            {
                delete[](unknown_60);
                unknown_60 = nullptr;
            }

            unknown_60 = new int32_t [i];
        }

        ar.readOrWrite(unknown_60, sizeof(int32_t) * i);

        /* [0x7C] `eGroupManager::serialize()` */

        unknown_7C.serialize(ar);

        /* [0xA8] unknown values */

        ar.readOrWrite(&navisCount, 0x04);

        unknown_AC.serialize(ar);

        /* [0x48] unknown value */

        ar.readOrWrite(&unknown_48, 0x01);
    }


    ////////////////////////////////////////////////////////////////
    // eNPCMap: render this node
    ////////////////////////////////////////////////////////////////
    void eNPCMap::renderNode(eDrawContext &draw_context) const
    {
        eGroup::renderNode(draw_context);

        if (GUI::drawFlags::DRAW_FLAG_BOXZONES & draw_context.getDrawFlags())
        {
            /* Inactive color (orange) */
            float color[3] = {1.0f, 0.5f, 0};

            bool is_selected_or_marked = draw_context.isNodeSelectedOrMarked();

            if (is_selected_or_marked)
            {
                glPushMatrix();
                GUI::multiplyBySelectedObjectTransform(false);
            }

            if (draw_context.isNodeOutlined())
            {
                /* Active color */
                GUI::colorOfMarkedObject(color[0], color[1], color[2]);
            }

            GUI::renderBoundingBox
            (
                2.0f,
                color[0], color[1], color[2],
                boxBoundMin.x, boxBoundMin.y, boxBoundMin.z,
                boxBoundMax.x, boxBoundMax.y, boxBoundMax.z
            );

            if (is_selected_or_marked)
            {
                glPopMatrix();
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eNPCMap: custom TXT parser methods
    ////////////////////////////////////////////////////////////////

    int32_t eNPCMap::parsingSetProperty(char* result_msg, const TxtParsingNodeProp &property)
    {
        int32_t test;
        float dummy_floats[3];
        eString prop_name;

        if (1 != (test = eGroup::parsingSetProperty(result_msg, property)))
        {
            return test;
        }

        prop_name = property.getName();

        if (prop_name.compareExact("min", true))
        {
            if (!property.checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT3))
            {
                TxtParsingNode_ErrorPropType(result_msg, "min", TXT_PARSING_NODE_PROPTYPE_FLOAT3);
                return 2;
            }

            property.getValue(dummy_floats);

            boxBoundMin.x = dummy_floats[0];
            boxBoundMin.y = dummy_floats[1];
            boxBoundMin.z = dummy_floats[2];
            return 0;
        }
        else if (prop_name.compareExact("max", true))
        {
            if (!property.checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT3))
            {
                TxtParsingNode_ErrorPropType(result_msg, "max", TXT_PARSING_NODE_PROPTYPE_FLOAT3);
                return 2;
            }

            property.getValue(dummy_floats);

            boxBoundMax.x = dummy_floats[0];
            boxBoundMax.y = dummy_floats[1];
            boxBoundMax.z = dummy_floats[2];
            return 0;
        }

        return 1;
    }

    int32_t eNPCMap::parsingCustomMessage(char* result_msg, const eString &message, int32_t params_count, const TxtParsingNodeProp* params)
    {
        int32_t test;
        float dummy_floats[3];

        if (1 != (test = eGroup::parsingCustomMessage(result_msg, message, params_count, params)))
        {
            return test;
        }

        if (message.compareExact("setBoundaryBox", true))
        {
            if (2 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "setBoundaryBox", 2);
                return 2;
            }

            /********************************/

            if (!params[0].checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT3))
            {
                TxtParsingNode_ErrorArgType(result_msg, "setBoundaryBox", 1, TXT_PARSING_NODE_PROPTYPE_FLOAT3);
                return 2;
            }

            params[0].getValue(dummy_floats);

            boxBoundMin.x = dummy_floats[0];
            boxBoundMin.y = dummy_floats[1];
            boxBoundMin.z = dummy_floats[2];

            /********************************/

            if (!params[1].checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT3))
            {
                TxtParsingNode_ErrorArgType(result_msg, "setBoundaryBox", 2, TXT_PARSING_NODE_PROPTYPE_FLOAT3);
                return 2;
            }

            params[1].getValue(dummy_floats);

            boxBoundMax.x = dummy_floats[0];
            boxBoundMax.y = dummy_floats[1];
            boxBoundMax.z = dummy_floats[2];

            /********************************/

            customMapSetup(boxBoundMin, boxBoundMax, 8);
            return 0;
        }

        return 1;
    }


    ////////////////////////////////////////////////////////////////
    // eNPCMap: custom Map setup
    ////////////////////////////////////////////////////////////////
    void eNPCMap::customMapSetup(ePoint3 &box_min, ePoint3 &box_max, int32_t navis_in_group)
    {
        int i, size;

        boxBoundMin = box_min;
        boxBoundMax = box_max;

        unknown_48 = 0x00;

        unknown_4C = 124;
        unknown_50 = 124;

        if (nullptr != unknown_60)
        {
            delete[](unknown_60);
            unknown_60 = nullptr;
        }

        size = unknown_4C * unknown_50;

        unknown_60 = new int32_t [size];

        for (i = 0; i < size; i++)
        {
            unknown_60[i] = *(int32_t*)"KAO.";
        }

        unknown_54 = 48.0f;
        unknown_58 = 32.0f;
        unknown_5C = 64.0f;

        navisCount = navis_in_group;

        unknown_AC = (box_min + box_max) * 0.5f;
    }

}
