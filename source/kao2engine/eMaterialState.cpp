#include <kao2engine/eMaterialState.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eMaterialState interface
    // <kao2.00482430> (constructor)
    // <kao2.004824E0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_MATERIALSTATE_TYPEINFO
    (
        E_MATERIALSTATE_ID,
        "eMaterialState",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return new eMaterialState;
        }
    );

    TypeInfo* eMaterialState::getType()
    {
        return &E_MATERIALSTATE_TYPEINFO;
    }

    eMaterialState::eMaterialState()
    : eRefCounter()
    {
        /*[0x28-0x34]*/
        unknown_28[0] = 0;
        unknown_28[1] = 0;
        unknown_28[2] = 0;
        unknown_28[3] = 1.0f;

        /*[0x08-0x14]*/
        unknown_08[0] = 0.5f;
        unknown_08[1] = 0.5f;
        unknown_08[2] = 0.5f;
        unknown_08[3] = 1.0f;

        /*[0x18-0x24]*/
        unknown_18[0] = 0.5f;
        unknown_18[1] = 0.5f;
        unknown_18[2] = 0.5f;
        unknown_18[3] = 1.0f;

        /*[0x38-0x44]*/
        unknown_38[0] = 0.5f;
        unknown_38[1] = 0.5f;
        unknown_38[2] = 0.5f;
        unknown_38[3] = 1.0f;

        /*[0x48]*/ unknown_48 = 0;
        /*[0x4C]*/ unknown_4C = true;

    }

    eMaterialState::~eMaterialState() {}


    ////////////////////////////////////////////////////////////////
    // eMaterialState serialization
    // <kao2.00482500>
    ////////////////////////////////////////////////////////////////
    void eMaterialState::serialize(Archive &ar)
    {
        /* [0x18] unknown */
        ar.readOrWrite(&(unknown_18[0]), 0x04);
        ar.readOrWrite(&(unknown_18[1]), 0x04);
        ar.readOrWrite(&(unknown_18[2]), 0x04);
        ar.readOrWrite(&(unknown_18[3]), 0x04);

        /* [0x08] unknown */
        ar.readOrWrite(&(unknown_08[0]), 0x04);
        ar.readOrWrite(&(unknown_08[1]), 0x04);
        ar.readOrWrite(&(unknown_08[2]), 0x04);
        ar.readOrWrite(&(unknown_08[3]), 0x04);

        if (ar.isInReadMode())
        {
            if (ar.getVersion() < 0x74)
            {
                unknown_08[0] = 0.5f;
                unknown_08[1] = 0.5f;
                unknown_08[2] = 0.5f;
                unknown_08[3] = 1.0f;

                unknown_18[0] = 0.5f;
                unknown_18[1] = 0.5f;
                unknown_18[2] = 0.5f;
                unknown_18[3] = 1.0f;
            }
        }

        if (ar.getVersion() >= 0x71)
        {
            /* [0x28] unknown */
            ar.readOrWrite(&(unknown_28[0]), 0x04);
            ar.readOrWrite(&(unknown_28[1]), 0x04);
            ar.readOrWrite(&(unknown_28[2]), 0x04);
            ar.readOrWrite(&(unknown_28[3]), 0x04);

            /* [0x38] unknown */
            ar.readOrWrite(&(unknown_38[0]), 0x04);
            ar.readOrWrite(&(unknown_38[1]), 0x04);
            ar.readOrWrite(&(unknown_38[2]), 0x04);
            ar.readOrWrite(&(unknown_38[3]), 0x04);
        }
        else
        {
            unknown_28[0] = 0;
            unknown_28[1] = 0;
            unknown_28[2] = 0;
            unknown_28[3] = 0;

            unknown_38[0] = 0;
            unknown_38[1] = 0;
            unknown_38[2] = 0;
            unknown_38[3] = 0;
        }

        /* [0x48] unknown */
        if (ar.getVersion() >= 0x72)
        {
            ar.readOrWrite(&unknown_48, 0x04);
        }
        else
        {
            unknown_48 = 0;
        }

        /* [0x4C] unknown */
        if (ar.getVersion() >= 0x76)
        {
            ar.readOrWrite(&unknown_4C, 0x01);
        }
        else
        {
            unknown_4C = true;
        }
    }

}
