#include <ElephantEngine/eMotorowki.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eMotorowki interface
    // <kao2.0045D650> (constructor)
    // <kao2.0045D750> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_MOTOROWKI_TYPEINFO
    (
        E_MOTOROWKI_ID,
        "eMotorowki",
        &E_SPLINEWALK_TYPEINFO,
        []() -> eObject*
        {
            return new eMotorowki;
        }
    );

    const TypeInfo* eMotorowki::getType() const
    {
        return &E_MOTOROWKI_TYPEINFO;
    }

    eMotorowki::eMotorowki()
    : eSplineWalk()
    {}

    eMotorowki::~eMotorowki()
    {}


    ////////////////////////////////////////////////////////////////
    // eMotorowki: cloning the object
    ////////////////////////////////////////////////////////////////

    void eMotorowki::createFromOtherObject(const eMotorowki &other)
    {}

    eMotorowki::eMotorowki(const eMotorowki &other)
    : eSplineWalk(other)
    {
        createFromOtherObject(other);
    }

    eMotorowki& eMotorowki::operator = (const eMotorowki &other)
    {
        if ((&other) != this)
        {
            eSplineWalk::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eMotorowki::cloneFromMe() const
    {
        return new eMotorowki(*this);
    }

}
