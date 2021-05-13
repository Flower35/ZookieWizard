#include <ElephantEngine/eString2.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eString2 interface
    // <kao2.0058AB73> (constructor)
    // <kao2.0048D2A0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_STRING2_TYPEINFO
    (
        E_STRING2_ID,
        "eString2",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return new eString2;
        }
    );

    const TypeInfo* eString2::getType() const
    {
        return &E_STRING2_TYPEINFO;
    }

    eString2::eString2()
    : eRefCounter()
    {}

    eString2::~eString2() {}


    ////////////////////////////////////////////////////////////////
    // eString2 serialization
    // <kao2.0048D1F0>
    ////////////////////////////////////////////////////////////////
    void eString2::serialize(Archive &ar)
    {
        ar.serializeString(str);
    }


    ////////////////////////////////////////////////////////////////
    // eString2: get textual representation
    ////////////////////////////////////////////////////////////////
    eString eString2::getStringRepresentation() const
    {
        eString result;

        result += "\"";
        result += str;
        result += "\"";

        return result;
    }

}
