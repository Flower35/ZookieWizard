#include <ElephantEngine/eLightBlinker.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eLightBlinker interface
    // <kao2.00529435> (constructor)
    // <kao2.005294E0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_LIGHTBLINKER_TYPEINFO
    (
        E_LIGHTBLINKER_ID,
        "eLightBlinker",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eLightBlinker;
        }
    );

    const TypeInfo* eLightBlinker::getType() const
    {
        return &E_LIGHTBLINKER_TYPEINFO;
    }

    eLightBlinker::eLightBlinker()
    : Gadget()
    {}

    eLightBlinker::~eLightBlinker()
    {}


    ////////////////////////////////////////////////////////////////
    // eLightBlinker: cloning the object
    ////////////////////////////////////////////////////////////////

    void eLightBlinker::createFromOtherObject(const eLightBlinker &other)
    {}

    eLightBlinker::eLightBlinker(const eLightBlinker &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eLightBlinker& eLightBlinker::operator = (const eLightBlinker &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eLightBlinker::cloneFromMe() const
    {
        return new eLightBlinker(*this);
    }

}
