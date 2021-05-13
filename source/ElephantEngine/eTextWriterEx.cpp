#include <ElephantEngine/eTextWriterEx.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eTextWriterEx interface
    // <kao2.0045A1B0> (constructor)
    // <kao2.0045A240> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_TEXTWRITEREX_TYPEINFO
    (
        E_TEXTWRITEREX_ID,
        "eTextWriterEx",
        &E_TEXTWRITER_TYPEINFO,
        []() -> eObject*
        {
            return new eTextWriterEx;
        }
    );

    const TypeInfo* eTextWriterEx::getType() const
    {
        return &E_TEXTWRITEREX_TYPEINFO;
    }

    eTextWriterEx::eTextWriterEx()
    : eTextWriter()
    {}

    eTextWriterEx::~eTextWriterEx()
    {}


    ////////////////////////////////////////////////////////////////
    // eTextWriterEx: cloning the object
    ////////////////////////////////////////////////////////////////

    void eTextWriterEx::createFromOtherObject(const eTextWriterEx &other)
    {}

    eTextWriterEx::eTextWriterEx(const eTextWriterEx &other)
    : eTextWriter(other)
    {
        createFromOtherObject(other);
    }

    eTextWriterEx& eTextWriterEx::operator = (const eTextWriterEx &other)
    {
        if ((&other) != this)
        {
            eTextWriter::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eTextWriterEx::cloneFromMe() const
    {
        return new eTextWriterEx(*this);
    }

}
