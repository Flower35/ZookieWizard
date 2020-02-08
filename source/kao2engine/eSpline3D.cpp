#include <kao2engine/eSpline3D.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSpline3D interface
    // <kao2.004A6A00> (constructor)
    // <kao2.004A6AA0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SPLINE3D_TYPEINFO
    (
        E_SPLINE3D_ID,
        "eSpline3D",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return new eSpline3D;
        }
    );

    TypeInfo* eSpline3D::getType() const
    {
        return &E_SPLINE3D_TYPEINFO;
    }

    eSpline3D::eSpline3D()
    : eRefCounter()
    {
        /*[0x08]*/ jointsCount = 0;
        /*[0x0C]*/ jointsMaxLength = 0;
        /*[0x10]*/ joints = nullptr;
        /*[0x14]*/ unknown_14 = 0;
    }

    eSpline3D::~eSpline3D()
    {
        if (nullptr != joints)
        {
            delete[](joints);
        }
    }


    ////////////////////////////////////////////////////////////////
    // Spline Joint structure
    // <kao2.09724B48> (serialization)
    ////////////////////////////////////////////////////////////////

    eSplineJointBase::eSplineJointBase()
    {
        unknown_00[0] = 0;
        unknown_00[1] = 0;
        unknown_00[2] = 0;

        unknown_0C[0] = 0;
        unknown_0C[1] = 0;
        unknown_0C[2] = 0;

        unknown_18[0] = 0;
        unknown_18[1] = 0;
        unknown_18[2] = 0;
    }

    void eSplineJointBase::serializeSplineJoint(Archive &ar)
    {
        /*[0x00-0x08]*/
        ar.readOrWrite(&(unknown_00[0]), 0x04);
        ar.readOrWrite(&(unknown_00[1]), 0x04);
        ar.readOrWrite(&(unknown_00[2]), 0x04);

        /*[0x0C-0x14]*/
        ar.readOrWrite(&(unknown_0C[0]), 0x04);
        ar.readOrWrite(&(unknown_0C[1]), 0x04);
        ar.readOrWrite(&(unknown_0C[2]), 0x04);

        /*[0x18-0x20]*/
        ar.readOrWrite(&(unknown_18[0]), 0x04);
        ar.readOrWrite(&(unknown_18[1]), 0x04);
        ar.readOrWrite(&(unknown_18[2]), 0x04);

        /* [0x24] Joint name */
        ar.serializeString(name);
    }


    ////////////////////////////////////////////////////////////////
    // eSpline3D serialization
    // <kao2.004A70B0>
    ////////////////////////////////////////////////////////////////
    void eSpline3D::serialize(Archive &ar)
    {
        int32_t i;

        if (ar.isInReadMode())
        {
            ar.readOrWrite(&jointsMaxLength, 0x04);

            if (nullptr != joints)
            {
                delete[](joints);
            }

            joints = new eSplineJointBase [jointsMaxLength];

            for (i = 0; i <jointsMaxLength; i++)
            {
                joints[i].serializeSplineJoint(ar);

                jointsCount = (i+1);
            }
        }
        else
        {
            ar.readOrWrite(&jointsCount, 0x04);

            for (i = 0; i < jointsCount; i++)
            {
                joints[i].serializeSplineJoint(ar);
            }
        }

        /* [0x14] unknown */
        ar.readOrWrite(&unknown_14, 0x04);
    }

}
