#include <ElephantEngine/eBaseballBieg.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eBaseballBieg interface
    // <kao2.00459E10> (constructor)
    // <kao2.00458FF0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_BASEBALLBIEG_TYPEINFO
    (
        E_BASEBALLBIEG_ID,
        "eBaseballBieg",
        &E_SPLINEWALK_TYPEINFO,
        []() -> eObject*
        {
            return new eBaseballBieg;
        }
    );

    TypeInfo* eBaseballBieg::getType() const
    {
        return &E_BASEBALLBIEG_TYPEINFO;
    }

    eBaseballBieg::eBaseballBieg()
    : eSplineWalk()
    {}

    eBaseballBieg::~eBaseballBieg()
    {}


    ////////////////////////////////////////////////////////////////
    // eBaseballBieg: cloning the object
    ////////////////////////////////////////////////////////////////

    void eBaseballBieg::createFromOtherObject(const eBaseballBieg &other)
    {}

    eBaseballBieg::eBaseballBieg(const eBaseballBieg &other)
    : eSplineWalk(other)
    {
        createFromOtherObject(other);
    }

    eBaseballBieg& eBaseballBieg::operator = (const eBaseballBieg &other)
    {
        if ((&other) != this)
        {
            eSplineWalk::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eBaseballBieg::cloneFromMe() const
    {
        return new eBaseballBieg(*this);
    }

}
