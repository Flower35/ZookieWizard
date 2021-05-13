#include <ElephantEngine/eLevelChanger.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eLevelChanger interface
    // <kao2.00456EE0> (constructor)
    // <kao2.00456F50> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_LEVELCHANGER_TYPEINFO
    (
        E_LEVELCHANGER_ID,
        "eLevelChanger",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eLevelChanger;
        }
    );

    TypeInfo* eLevelChanger::getType() const
    {
        return &E_LEVELCHANGER_TYPEINFO;
    }

    eLevelChanger::eLevelChanger()
    : Gadget()
    {}

    eLevelChanger::~eLevelChanger()
    {}


    ////////////////////////////////////////////////////////////////
    // eLevelChanger: cloning the object
    ////////////////////////////////////////////////////////////////

    void eLevelChanger::createFromOtherObject(const eLevelChanger &other)
    {}

    eLevelChanger::eLevelChanger(const eLevelChanger &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eLevelChanger& eLevelChanger::operator = (const eLevelChanger &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eLevelChanger::cloneFromMe() const
    {
        return new eLevelChanger(*this);
    }

}
