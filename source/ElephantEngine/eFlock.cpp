#include <ElephantEngine/eFlock.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFlock interface
    // <kao2.0042E006> (constructor)
    // <kao2.0042E0A0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_FLOCK_TYPEINFO
    (
        E_FLOCK_ID,
        "eFlock",
        &E_PATHCTRL_TYPEINFO,
        []() -> eObject*
        {
            return new eFlock;
        }
    );

    TypeInfo* eFlock::getType() const
    {
        return &E_FLOCK_TYPEINFO;
    }

    eFlock::eFlock()
    : ePathCtrl()
    {
        /*[0x50]*/ unknown_50 = nullptr;
    }

    eFlock::~eFlock()
    {
        /*[0x90]*/
    }


    ////////////////////////////////////////////////////////////////
    // eFlock: cloning the object
    ////////////////////////////////////////////////////////////////

    void eFlock::createFromOtherObject(const eFlock &other)
    {
        unknown_50 = other.unknown_50;
    }

    eFlock::eFlock(const eFlock &other)
    : ePathCtrl(other)
    {
        createFromOtherObject(other);
    }

    eFlock& eFlock::operator = (const eFlock &other)
    {
        if ((&other) != this)
        {
            ePathCtrl::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eFlock::cloneFromMe() const
    {
        return new eFlock(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eFlock: serialization
    // <kao2.0042DD60>
    ////////////////////////////////////////////////////////////////
    void eFlock::serialize(Archive &ar)
    {
        ePathCtrl::serialize(ar);

        /* [0x50] unknown */

        ar.serialize((eObject**)&unknown_50, nullptr);
    }

}
