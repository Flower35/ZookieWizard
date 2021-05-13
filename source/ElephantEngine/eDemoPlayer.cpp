#include <ElephantEngine/eDemoPlayer.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eDemoPlayer interface
    // <kao2.00458B80> (constructor)
    // <kao2.00458BF0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_DEMOPLAYER_TYPEINFO
    (
        E_DEMOPLAYER_ID,
        "eDemoPlayer",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eDemoPlayer;
        }
    );

    TypeInfo* eDemoPlayer::getType() const
    {
        return &E_DEMOPLAYER_TYPEINFO;
    }

    eDemoPlayer::eDemoPlayer()
    : Gadget()
    {}

    eDemoPlayer::~eDemoPlayer()
    {}


    ////////////////////////////////////////////////////////////////
    // eDemoPlayer: cloning the object
    ////////////////////////////////////////////////////////////////

    void eDemoPlayer::createFromOtherObject(const eDemoPlayer &other)
    {}

    eDemoPlayer::eDemoPlayer(const eDemoPlayer &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eDemoPlayer& eDemoPlayer::operator = (const eDemoPlayer &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eDemoPlayer::cloneFromMe() const
    {
        return new eDemoPlayer(*this);
    }

}
