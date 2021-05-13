#include <ElephantEngine/ePlaszczka.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePlaszczka interface
    // <kao2.0044DB54> (constructor)
    // <kao2.0044DBD0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_PLASZCZKA_TYPEINFO
    (
        E_PLASZCZKA_ID,
        "ePlaszczka",
        &E_WALK_TYPEINFO,
        []() -> eObject*
        {
            return new ePlaszczka;
        }
    );

    TypeInfo* ePlaszczka::getType() const
    {
        return &E_PLASZCZKA_TYPEINFO;
    }

    ePlaszczka::ePlaszczka()
    : eWalk()
    {}

    ePlaszczka::~ePlaszczka()
    {}


    ////////////////////////////////////////////////////////////////
    // ePlaszczka: cloning the object
    ////////////////////////////////////////////////////////////////

    void ePlaszczka::createFromOtherObject(const ePlaszczka &other)
    {}

    ePlaszczka::ePlaszczka(const ePlaszczka &other)
    : eWalk(other)
    {
        createFromOtherObject(other);
    }

    ePlaszczka& ePlaszczka::operator = (const ePlaszczka &other)
    {
        if ((&other) != this)
        {
            eWalk::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* ePlaszczka::cloneFromMe() const
    {
        return new ePlaszczka(*this);
    }

}
