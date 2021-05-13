#include <ElephantEngine/eWSGroup.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eWSGroup interface
    // <kao2.0049ACC0> (constructor)
    // <kao2.0049AD50> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_WSGROUP_TYPEINFO
    (
        E_WSGROUP_ID,
        "eWSGroup",
        &E_GROUP_TYPEINFO,
        []() -> eObject*
        {
            return new eWSGroup;
        }
    );

    const TypeInfo* eWSGroup::getType() const
    {
        return &E_WSGROUP_TYPEINFO;
    }

    eWSGroup::eWSGroup()
    : eGroup()
    {
        /*[0x4C]*/ unknown_4C = 0;
    }

    eWSGroup::~eWSGroup()
    {}


    ////////////////////////////////////////////////////////////////
    // eWSGroup: cloning the object
    ////////////////////////////////////////////////////////////////

    void eWSGroup::createFromOtherObject(const eWSGroup &other)
    {
        unknown_4C = other.unknown_4C;
    }

    eWSGroup::eWSGroup(const eWSGroup &other)
    : eGroup(other)
    {
        createFromOtherObject(other);
    }

    eWSGroup& eWSGroup::operator = (const eWSGroup &other)
    {
        if ((&other) != this)
        {
            eGroup::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eWSGroup::cloneFromMe() const
    {
        return new eWSGroup(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eWSGroup: serialization
    // <SaddleClub.00607B80>
    ////////////////////////////////////////////////////////////////
    void eWSGroup::serialize(Archive &ar)
    {
        eGroup::serialize(ar);

        if (ar.getVersion() > 0x93)
        {
            ar.readOrWrite(&unknown_4C, 0x04);
        }
    }

}
