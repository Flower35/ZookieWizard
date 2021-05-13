#include <ElephantEngine/eMultiTransform.h>
#include <ElephantBase/Archive.h>

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

    TypeInfo* eMultiTransform::getType() const
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

    void eMultiTransformBase::serializeTransform(Archive &ar)
    {
        ar.readOrWrite(&(unknown_00[0]), 0x04);
        ar.readOrWrite(&(unknown_00[1]), 0x04);
        ar.readOrWrite(&(unknown_00[2]), 0x04);

        ar.readOrWrite(&(unknown_0C[0]), 0x04);

        ar.readOrWrite(&(unknown_10[0]), 0x04);
        ar.readOrWrite(&(unknown_10[1]), 0x04);
        ar.readOrWrite(&(unknown_10[2]), 0x04);

        ar.readOrWrite(&unknown_1C, 0x04);

        ar.readOrWrite(&(unknown_20[0]), 0x04);
        ar.readOrWrite(&(unknown_20[1]), 0x04);
        ar.readOrWrite(&(unknown_20[2]), 0x04);
        ar.readOrWrite(&(unknown_20[3]), 0x04);

        ar.readOrWrite(&(unknown_30[0]), 0x04);
        ar.readOrWrite(&(unknown_30[1]), 0x04);
        ar.readOrWrite(&(unknown_30[2]), 0x04);
        ar.readOrWrite(&(unknown_30[3]), 0x04);
    }


    ////////////////////////////////////////////////////////////////
    // eMultiTransform: serialization
    // <kao2.004B0B30>
    ////////////////////////////////////////////////////////////////
    void eMultiTransform::serialize(Archive &ar)
    {
        int32_t i;

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
            }
        }
        else
        {
            ar.readOrWrite(&transformsCount, 0x04);

            for (i = 0; i < transformsCount; i++)
            {
                transforms[i].serializeTransform(ar);
            }
        }

        /* unknown values */

        ar.readOrWrite(&unknown_54, 0x04);
        ar.readOrWrite(&unknown_58, 0x04);
        ar.readOrWrite(&unknown_5C, 0x04);
        ar.readOrWrite(&unknown_60, 0x04);
        ar.readOrWrite(&unknown_64, 0x04);
    }

}
