#include <kao2engine/eTextWriterFields2.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eTextWriterFields2 interface
    // <kao2.0051E183> (constructor)
    // <kao2.0051E240> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_TEXTWRITERFIELDS2_TYPEINFO
    (
        E_TEXTWRITERFIELDS2_ID,
        "eTextWriterFields2",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eTextWriterFields2;
        }
    );

    TypeInfo* eTextWriterFields2::getType() const
    {
        return &E_TEXTWRITERFIELDS2_TYPEINFO;
    }

    eTextWriterFields2::eTextWriterFields2()
    : Gadget()
    {}

    eTextWriterFields2::~eTextWriterFields2()
    {}


    ////////////////////////////////////////////////////////////////
    // eTextWriterFields2: cloning the object
    ////////////////////////////////////////////////////////////////

    void eTextWriterFields2::createFromOtherObject(const eTextWriterFields2 &other)
    {}

    eTextWriterFields2::eTextWriterFields2(const eTextWriterFields2 &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eTextWriterFields2& eTextWriterFields2::operator = (const eTextWriterFields2 &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eTextWriterFields2::cloneFromMe() const
    {
        return new eTextWriterFields2(*this);
    }

}
