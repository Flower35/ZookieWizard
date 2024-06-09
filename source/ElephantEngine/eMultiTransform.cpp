#include <ElephantEngine/eMultiTransform.h>
#include <ElephantBase/Archive.h>
#include <ElephantEngine/Log.h>
#include <ElephantEngine/eMultiTransformNode.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eMultiTransform interface
    // <kao2.004B08D0> (constructor)
    // <kao2.004B09E0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_MULTITRANSFORM_TYPEINFO
    (
        E_MULTITRANSFORM_ID,
        "eMultiTransform",
        &E_GROUP_TYPEINFO,
        []() -> eObject*
        {
            return new eMultiTransform;
        }
    );

    const TypeInfo* eMultiTransform::getType() const
    {
        return &E_MULTITRANSFORM_TYPEINFO;
    }

    eMultiTransform::eMultiTransform()
    : eGroup()
    {
        /*[0x48]*/ transformsCount = 0;
        /*[0x4C]*/ transformsMaxLength = 0;
        /*[0x50]*/ transforms = nullptr;

        /*[0x60] */ unknown_60 = (-1.0f);
        /*[0x64] */ unknown_64 = 20;
    }

    eMultiTransform::~eMultiTransform()
    {
        if (nullptr != transforms)
        {
            delete[](transforms);
        }
    }


    ////////////////////////////////////////////////////////////////
    // eMultiTransform: cloning the object
    ////////////////////////////////////////////////////////////////

    void eMultiTransform::createFromOtherObject(const eMultiTransform &other)
    {
        if (other.transformsCount > 0)
        {
            transformsMaxLength = other.transformsCount;

            transforms = new eMultiTransformBase [transformsMaxLength];

            for (transformsCount = 0; transformsCount < transformsMaxLength; transformsCount++)
            {
                transforms[transformsCount] = other.transforms[transformsCount];
            }
        }
        else
        {
            transformsCount = 0;
            transformsMaxLength = 0;
            transforms = nullptr;
        }

        unknown_54 = other.unknown_54;
        unknown_58 = other.unknown_58;
        unknown_5C = other.unknown_5C;
        unknown_60 = other.unknown_60;
        unknown_64 = other.unknown_64;
    }

    eMultiTransform::eMultiTransform(const eMultiTransform &other)
    : eGroup(other)
    {
        createFromOtherObject(other);
    }

    eMultiTransform& eMultiTransform::operator = (const eMultiTransform &other)
    {
        if ((&other) != this)
        {
            eGroup::operator = (other);

            /****************/

            if (nullptr != transforms)
            {
                delete[](transforms);
            }

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eMultiTransform::cloneFromMe() const
    {
        return new eMultiTransform(*this);
    }


    ////////////////////////////////////////////////////////////////
    // Transform Base structture
    // <kao2.004B14FC> (serialization)
    ////////////////////////////////////////////////////////////////

    void eMultiTransformBase::serializeTransform(Archive& ar)
    {
        int i;

        /*byte unknownAll[0x40];
        ar.readOrWrite(&(unknownAll[0]), 0x040);

        char hexstr[301];
        for (i = 0; i < 0x40; i++)
        {
            sprintf_s(hexstr + i * 3, sizeof(hexstr + i * 3), "%02x ", unknownAll[i]);
        }
        hexstr[i * 3] = 0;

        eString message;
        message += hexstr;
        theLog.print(message);*/

        ar.readOrWrite(&(dummy_rotationA[0]), 0x04);
        ar.readOrWrite(&(dummy_rotationA[1]), 0x04);
        ar.readOrWrite(&(dummy_rotationA[2]), 0x04);

        ar.readOrWrite(&color, 0x04);

        ar.readOrWrite(&(dummy_rotationB[0]), 0x04);
        ar.readOrWrite(&(dummy_rotationB[1]), 0x04);
        ar.readOrWrite(&(dummy_rotationB[2]), 0x04);

        ar.readOrWrite(&unknown_1C, 0x04);

        ar.readOrWrite(&(rotation[0]), 0x04);
        ar.readOrWrite(&(rotation[1]), 0x04);
        ar.readOrWrite(&(rotation[2]), 0x04);

        ar.readOrWrite(&unknown_2C, 0x04);

        ar.readOrWrite(&(position[0]), 0x04);
        ar.readOrWrite(&(position[1]), 0x04);
        ar.readOrWrite(&(position[2]), 0x04);

        ar.readOrWrite(&scale, 0x04);

        /*char hexstr[1029];
        int i = 0;
        int columnLength = 11;
        sprintf_s(hexstr + columnLength * i++, 19, "%10.3f ", unknown_00[0]);
        sprintf_s(hexstr + columnLength * i++, 19, "%10.3f ", unknown_00[1]);
        sprintf_s(hexstr + columnLength * i++, 19, "%10.3f ", unknown_00[2]);

        sprintf_s(hexstr + columnLength * i++, 19, "////////// ", unknown_0C);

        sprintf_s(hexstr + columnLength * i++, 19, "%10.3f ", unknown_10[0]);
        sprintf_s(hexstr + columnLength * i++, 19, "%10.3f ", unknown_10[1]);
        sprintf_s(hexstr + columnLength * i++, 19, "%10.3f ", unknown_10[2]);

        sprintf_s(hexstr + columnLength * i++, 19, "%10.3f ", unknown_1C);

        sprintf_s(hexstr + columnLength * i++, 19, "%10.3f ", unknown_20[0]);
        sprintf_s(hexstr + columnLength * i++, 19, "%10.3f ", unknown_20[1]);
        sprintf_s(hexstr + columnLength * i++, 19, "%10.3f ", unknown_20[2]);
        sprintf_s(hexstr + columnLength * i++, 19, "%10.3f ", unknown_20[3]);

        sprintf_s(hexstr + columnLength * i++, 19, "%10.3f ", unknown_30[0]);
        sprintf_s(hexstr + columnLength * i++, 19, "%10.3f ", unknown_30[1]);
        sprintf_s(hexstr + columnLength * i++, 19, "%10.3f ", unknown_30[2]);
        sprintf_s(hexstr + columnLength * i++, 19, "%10.3f ", unknown_30[3]);
        hexstr[columnLength * i] = 0;
        eString message;
        message += hexstr;
        theLog.print(message);*/
    }


    ////////////////////////////////////////////////////////////////
    // eMultiTransform: serialization
    // <kao2.004B0B30>
    ////////////////////////////////////////////////////////////////
    void eMultiTransform::serialize(Archive &ar)
    {
        int32_t i;
        eNode* test_node;
        eMultiTransformNode* instance;
        eMultiTransformBase* temp_transform;

        eGroup::serialize(ar);

        if (ar.isInReadMode())
        {
            if (nullptr != transforms)
            {
                delete[](transforms);
                transforms = nullptr;

                transformsCount = 0;
            }

            ar.readOrWrite(&transformsMaxLength, 0x04);

            transforms = new eMultiTransformBase [transformsMaxLength];

            for (i = 0; i < transformsMaxLength; i++)
            {
                transforms[i].serializeTransform(ar);

                transformsCount = (i+1);

                TypeInfo* test_typeinfo = &E_MULTITRANSFORMNODE_TYPEINFO;
                instance = (eMultiTransformNode*)test_typeinfo->create();

                if (nullptr != instance)
                {
                    appendChild(instance);
                    instance->editingNewNodeSetup();
                    instance->setupInstance(transforms[i]);
                }
            }
        }
        else
        {
            /*ar.readOrWrite(&transformsCount, 0x04);

            for (i = 0; i < transformsCount; i++)
            {
                transforms[i].serializeTransform(ar, *this);
            }*/

            int32_t nodesCount = getNodesCount();
            int32_t instancesCount = nodesCount - getNonVirtualNodesCount();

            /*for (i = 0; i < nodesCount; i++)
            {
                test_node = getIthChild(i);
                if (test_node != nullptr && test_node->getType()->checkHierarchy(&E_MULTITRANSFORMNODE_TYPEINFO))
                {
                    instancesCount++;
                }
            }*/

            ar.readOrWrite(&instancesCount, 0x04);

            for (i = 0; i < nodesCount; i++)
            {
                test_node = getIthChild(i);
                if (test_node != nullptr && test_node->getType()->checkHierarchy(&E_MULTITRANSFORMNODE_TYPEINFO))
                {
                    instance = (eMultiTransformNode*)test_node;
                    temp_transform = new eMultiTransformBase();
                    instance->setupBase(*temp_transform);

                    temp_transform->serializeTransform(ar);
                    delete temp_transform;
                }
            }
        }

        /* unknown values */

        ar.readOrWrite(&unknown_54, 0x04);//-1.71793866
        ar.readOrWrite(&unknown_58, 0x04);//42.8847466
        ar.readOrWrite(&unknown_5C, 0x04);//132.013535
        ar.readOrWrite(&unknown_60, 0x04);//249.311020
        ar.readOrWrite(&unknown_64, 0x04);//2
    }

}
