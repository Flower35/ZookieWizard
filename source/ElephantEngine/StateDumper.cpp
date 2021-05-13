#include <ElephantEngine/StateDumper.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // StateDumper interface
    // <kao2.005AFFB1> (constructor)
    // <kao2.005B0020> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_STATEDUMPER_TYPEINFO
    (
        E_STATEDUMPER_ID,
        "StateDumper",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new StateDumper;
        }
    );

    TypeInfo* StateDumper::getType() const
    {
        return &E_STATEDUMPER_TYPEINFO;
    }

    StateDumper::StateDumper()
    : Gadget()
    {}

    StateDumper::~StateDumper()
    {}


    ////////////////////////////////////////////////////////////////
    // StateDumper: cloning the object
    ////////////////////////////////////////////////////////////////

    void StateDumper::createFromOtherObject(const StateDumper &other)
    {}

    StateDumper::StateDumper(const StateDumper &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    StateDumper& StateDumper::operator = (const StateDumper &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* StateDumper::cloneFromMe() const
    {
        return new StateDumper(*this);
    }

}
