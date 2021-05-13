#include <ElephantEngine/eTextWriter.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eTextWriter interface
    // <kao2.0041D690> (constructor)
    // <kao2.0041D790> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_TEXTWRITER_TYPEINFO
    (
        E_TEXTWRITER_ID,
        "eTextWriter",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eTextWriter;
        }
    );

    const TypeInfo* eTextWriter::getType() const
    {
        return &E_TEXTWRITER_TYPEINFO;
    }

    eTextWriter::eTextWriter()
    : Gadget()
    {}

    eTextWriter::~eTextWriter()
    {}


    ////////////////////////////////////////////////////////////////
    // eTextWriter: cloning the object
    ////////////////////////////////////////////////////////////////

    void eTextWriter::createFromOtherObject(const eTextWriter &other)
    {}

    eTextWriter::eTextWriter(const eTextWriter &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eTextWriter& eTextWriter::operator = (const eTextWriter &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eTextWriter::cloneFromMe() const
    {
        return new eTextWriter(*this);
    }

}
