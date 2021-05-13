#include <ElephantEngine/eMarks.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eMarks interface
    // <kao2.0055AB90> (constructor)
    // <kao2.0055AC20> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_MARKS_TYPEINFO
    (
        E_MARKS_ID,
        "eMarks",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eMarks;
        }
    );

    TypeInfo* eMarks::getType() const
    {
        return &E_MARKS_TYPEINFO;
    }

    eMarks::eMarks()
    : Gadget()
    {}

    eMarks::~eMarks()
    {}


    ////////////////////////////////////////////////////////////////
    // eMarks: cloning the object
    ////////////////////////////////////////////////////////////////

    void eMarks::createFromOtherObject(const eMarks &other)
    {}

    eMarks::eMarks(const eMarks &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eMarks& eMarks::operator = (const eMarks &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eMarks::cloneFromMe() const
    {
        return new eMarks(*this);
    }

}
