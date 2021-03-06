#include <ElephantEngine/eTargetGenerator.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eTargetGenerator interface
    // <kao2.005A4AE0> (constructor)
    // <kao2.005A4B50> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_TARGETGENERATOR_TYPEINFO
    (
        E_TARGETGENERATOR_ID,
        "eTargetGenerator",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eTargetGenerator;
        }
    );

    const TypeInfo* eTargetGenerator::getType() const
    {
        return &E_TARGETGENERATOR_TYPEINFO;
    }

    eTargetGenerator::eTargetGenerator()
    : Gadget()
    {}

    eTargetGenerator::~eTargetGenerator()
    {}


    ////////////////////////////////////////////////////////////////
    // eTargetGenerator: cloning the object
    ////////////////////////////////////////////////////////////////

    void eTargetGenerator::createFromOtherObject(const eTargetGenerator &other)
    {}

    eTargetGenerator::eTargetGenerator(const eTargetGenerator &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eTargetGenerator& eTargetGenerator::operator = (const eTargetGenerator &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eTargetGenerator::cloneFromMe() const
    {
        return new eTargetGenerator(*this);
    }

}
