#include <kao2engine/ePathFinder.h>
#include <kao2ar/Archive.h>

#include <kao2engine/eGroundTest.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePathFinder interface
    // <kao2.00425C30> (constructor)
    // <kao2.00425D30> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_PATHFINDER_TYPEINFO
    (
        E_PATHFINDER_ID,
        "ePathFinder",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new ePathFinder;
        }
    );

    TypeInfo* ePathFinder::getType() const
    {
        return &E_PATHFINDER_TYPEINFO;
    }

    ePathFinder::ePathFinder()
    : Gadget()
    {
        /*[0x10]*/ group_Count = 0;
        /*[0x14]*/ group_MaxLength = 0;
        /*[0x18]*/ group = nullptr;

        /*[0x1C]*/ unknown_1C = nullptr;
        /*[0x28]*/ unknown_28 = nullptr;

        /*[0x20]*/ unknown_20 = nullptr;
    }

    ePathFinder::~ePathFinder()
    {
        if (nullptr != unknown_28)
        {
            unknown_28->decRef();
        }

        if (nullptr != unknown_1C)
        {
            unknown_1C->decRef();
        }

        if (nullptr != group)
        {
            delete[](group);
        }
    }


    ////////////////////////////////////////////////////////////////
    // ePathFinder serialization
    // <kao2.00426F80>
    ////////////////////////////////////////////////////////////////
    void ePathFinder::serialize(Archive &ar)
    {
        int32_t i;

        Gadget::serialize(ar);

        /* [0x10] unknown group */

        if (ar.isInReadMode())
        {
            if (nullptr != group)
            {
                delete[](group);
                group = nullptr;

                group_MaxLength = 0;
                group_Count = 0;
            }

            ar.readOrWrite(&group_MaxLength, 0x04);

            group = new ePoint3 [group_MaxLength];

            for (i = 0; i < group_MaxLength; i++)
            {
                group[i].serialize(ar);

                group_Count = (i+1);
            }
        }
        else
        {
            ar.readOrWrite(&group_Count, 0x04);

            for (i = 0; i < group_Count; i++)
            {
                group[i].serialize(ar);
            }
        }

        /* [0x1C] unknown object */

        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&unknown_1C, nullptr);

        /* [0x20] unknown link */

        ar.serialize((eObject**)&unknown_20, nullptr);

        /* [0x24] unknown value */

        ar.readOrWrite(&unknown_24, 0x01);

        /* [0x28] unknown object */

        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&unknown_28, &E_GROUNDTEST_TYPEINFO);

        /* [0x2C] unknown values */

        ar.readOrWrite(&unknown_2C, 0x04);
        ar.readOrWrite(&unknown_30, 0x04);
        ar.readOrWrite(&unknown_34, 0x04);
    }


    ////////////////////////////////////////////////////////////////
    // ePathFinder: get default name (scripting shenanigans)
    ////////////////////////////////////////////////////////////////
    eString ePathFinder::getDefaultGadgetName() const
    {
        return "pf";
    }

}
