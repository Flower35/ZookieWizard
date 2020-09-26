#include <kao2engine/eIceCubeMarks.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eIceCubeMarks interface
    // <kao2.0055AF70> (constructor)
    // <kao2.0055B000> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_ICECUBEMARKS_TYPEINFO
    (
        E_ICECUBEMARKS_ID,
        "eIceCubeMarks",
        &E_MARKS_TYPEINFO,
        []() -> eObject*
        {
            return new eIceCubeMarks;
        }
    );

    TypeInfo* eIceCubeMarks::getType() const
    {
        return &E_ICECUBEMARKS_TYPEINFO;
    }

    eIceCubeMarks::eIceCubeMarks()
    : eMarks()
    {}

    eIceCubeMarks::~eIceCubeMarks()
    {}


    ////////////////////////////////////////////////////////////////
    // eIceCubeMarks: cloning the object
    ////////////////////////////////////////////////////////////////

    void eIceCubeMarks::createFromOtherObject(const eIceCubeMarks &other)
    {}

    eIceCubeMarks::eIceCubeMarks(const eIceCubeMarks &other)
    : eMarks(other)
    {
        createFromOtherObject(other);
    }

    eIceCubeMarks& eIceCubeMarks::operator = (const eIceCubeMarks &other)
    {
        if ((&other) != this)
        {
            eMarks::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eIceCubeMarks::cloneFromMe() const
    {
        return new eIceCubeMarks(*this);
    }

}
