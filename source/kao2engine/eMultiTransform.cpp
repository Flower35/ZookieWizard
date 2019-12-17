#include <kao2engine/eMultiTransform.h>
#include <kao2ar/Archive.h>

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

    TypeInfo* eMultiTransform::getType()
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
    // Transform structture
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
    // eMultiTransform serialization
    // <kao2.004B0B30>
    ////////////////////////////////////////////////////////////////
    void eMultiTransform::serialize(Archive &ar)
    {
        int32_t i;

        eGroup::serialize(ar);

        /* Grupa */

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
