#include <ElephantEngine/eFollowWPF.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFollowWPF interface
    // <kao2.0042FF10> (constructor)
    // <kao2.0042FF90> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_FOLLOWWPF_TYPEINFO
    (
        E_FOLLOWWPF_ID,
        "eFollowWPF",
        &E_PATHCTRL_TYPEINFO,
        []() -> eObject*
        {
            return new eFollowWPF;
        }
    );

    const TypeInfo* eFollowWPF::getType() const
    {
        return &E_FOLLOWWPF_TYPEINFO;
    }

    eFollowWPF::eFollowWPF()
    : ePathCtrl()
    {
        /*[0x50]*/ unknown_50 = nullptr;

        /*[0x68]*/ unknown_68 = 0x00;

        /*[0x60]*/ unknown_60 = 1.0f;
        /*[0x64]*/ unknown_64 = 1.0f;
    }

    eFollowWPF::~eFollowWPF()
    {}


    ////////////////////////////////////////////////////////////////
    // eFollowWPF: cloning the object
    ////////////////////////////////////////////////////////////////

    void eFollowWPF::createFromOtherObject(const eFollowWPF &other)
    {
        unknown_50 = other.unknown_50;

        unknown_54 = other.unknown_54;
        unknown_58 = other.unknown_58;
        unknown_5C = other.unknown_5C;

        unknown_60 = other.unknown_60;
        unknown_64 = other.unknown_64;

        unknown_68 = other.unknown_68;
    }

    eFollowWPF::eFollowWPF(const eFollowWPF &other)
    : ePathCtrl(other)
    {
        createFromOtherObject(other);
    }

    eFollowWPF& eFollowWPF::operator = (const eFollowWPF &other)
    {
        if ((&other) != this)
        {
            ePathCtrl::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eFollowWPF::cloneFromMe() const
    {
        return new eFollowWPF(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eFollowWPF: serialization
    // <kao2.0042FE70>
    ////////////////////////////////////////////////////////////////
    void eFollowWPF::serialize(Archive &ar)
    {
        ePathCtrl::serialize(ar);

        /* [0x50] unknown link */

        ar.serialize((eObject**)&unknown_50, nullptr);

        /* [0x54] unknown values */

        ar.readOrWrite(&unknown_54, 0x04);
        ar.readOrWrite(&unknown_58, 0x04);
        ar.readOrWrite(&unknown_5C, 0x04);

        /* [0x64] unknown */

        ar.readOrWrite(&unknown_64, 0x04);
    }

}
