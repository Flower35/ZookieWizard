#include <ElephantEngine/ePathFinder.h>
#include <ElephantBase/Archive.h>

#include <ElephantEngine/eGroundTest.h>
#include <ElephantEngine/eNPCMap.h>

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

    const TypeInfo* ePathFinder::getType() const
    {
        return &E_PATHFINDER_TYPEINFO;
    }

    ePathFinder::ePathFinder()
    : Gadget()
    {
        /*[0x10]*/ points_Count = 0;
        /*[0x14]*/ points_MaxLength = 0;
        /*[0x18]*/ points = nullptr;

        /*[0x1C]*/ unknown_1C = nullptr;
        /*[0x28]*/ unknown_28 = nullptr;

        /*[0x20]*/ map = nullptr;
    }

    ePathFinder::~ePathFinder()
    {
        unknown_28->decRef();

        unknown_1C->decRef();

        if (nullptr != points)
        {
            delete[](points);
        }
    }


    ////////////////////////////////////////////////////////////////
    // ePathFinder: cloning the object
    ////////////////////////////////////////////////////////////////

    void ePathFinder::createFromOtherObject(const ePathFinder &other)
    {
        if (other.points_Count > 0)
        {
            points_MaxLength = other.points_Count;
            points = new ePoint3 [points_MaxLength];

            for (points_Count = 0; points_Count < points_MaxLength; points_Count++)
            {
                points[points_Count] = other.points[points_Count];
            }
        }
        else
        {
            points_Count = 0;
            points_MaxLength = 0;
            points = nullptr;
        }

        /****************/

        unknown_1C = other.unknown_1C;
        if (nullptr != unknown_1C)
        {
            unknown_1C->incRef();
        }

        map = other.map;

        unknown_24 = other.unknown_24;

        unknown_28 = other.unknown_28;
        if (nullptr != unknown_28)
        {
            unknown_28->incRef();
        }

        unknown_2C = other.unknown_2C;
        unknown_30 = other.unknown_30;
        unknown_34 = other.unknown_34;
    }

    ePathFinder::ePathFinder(const ePathFinder &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    ePathFinder& ePathFinder::operator = (const ePathFinder &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            if (nullptr != points)
            {
                delete[](points);
            }

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* ePathFinder::cloneFromMe() const
    {
        return new ePathFinder(*this);
    }


    ////////////////////////////////////////////////////////////////
    // ePathFinder: serialization
    // <kao2.00426F80>
    ////////////////////////////////////////////////////////////////
    void ePathFinder::serialize(Archive &ar)
    {
        int32_t i;

        Gadget::serialize(ar);

        /* [0x10] unknown group */

        if (ar.isInReadMode())
        {
            if (nullptr != points)
            {
                delete[](points);
                points = nullptr;

                points_MaxLength = 0;
                points_Count = 0;
            }

            ar.readOrWrite(&points_MaxLength, 0x04);

            points = new ePoint3 [points_MaxLength];

            for (i = 0; i < points_MaxLength; i++)
            {
                points[i].serialize(ar);

                points_Count = (i+1);
            }
        }
        else
        {
            ar.readOrWrite(&points_Count, 0x04);

            for (i = 0; i < points_Count; i++)
            {
                points[i].serialize(ar);
            }
        }

        /* [0x1C] unknown object */

        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&unknown_1C, nullptr);

        /* [0x20] "eNPCMap" link */

        ar.serialize((eObject**)&map, &E_NPCMAP_TYPEINFO);

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
