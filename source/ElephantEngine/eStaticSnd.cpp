#include <ElephantEngine/eStaticSnd.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eStaticSnd interface
    // <kao2.00439C40> (constructor)
    // <kao2.00439CC0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_STATICSND_TYPEINFO
    (
        E_STATICSND_ID,
        "eStaticSnd",
        &E_SND_TYPEINFO,
        []() -> eObject*
        {
            return new eStaticSnd;
        }
    );

    TypeInfo* eStaticSnd::getType() const
    {
        return &E_STATICSND_TYPEINFO;
    }

    eStaticSnd::eStaticSnd()
    : eSnd()
    {}

    eStaticSnd::~eStaticSnd()
    {}


    ////////////////////////////////////////////////////////////////
    // eStaticSnd: cloning the object
    ////////////////////////////////////////////////////////////////

    void eStaticSnd::createFromOtherObject(const eStaticSnd &other)
    {}

    eStaticSnd::eStaticSnd(const eStaticSnd &other)
    : eSnd(other)
    {
        createFromOtherObject(other);
    }

    eStaticSnd& eStaticSnd::operator = (const eStaticSnd &other)
    {
        if ((&other) != this)
        {
            eSnd::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eStaticSnd::cloneFromMe() const
    {
        return new eStaticSnd(*this);
    }

}
