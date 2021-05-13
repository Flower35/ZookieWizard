#include <ElephantEngine/ePointEmiter.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePointEmiter interface
    // <kao2.005522D0> (constructor)
    // <kao2.005523A0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_POINTEMITER_TYPEINFO
    (
        E_POINTEMITER_ID,
        "ePointEmiter",
        &E_PARTICLEEMITER_TYPEINFO,
        []() -> eObject*
        {
            return new ePointEmiter;
        }
    );

    const TypeInfo* ePointEmiter::getType() const
    {
        return &E_POINTEMITER_TYPEINFO;
    }

    ePointEmiter::ePointEmiter()
    : eParticleEmiter()
    {
        /*[0x0054]*/ unknown_0054 = 360.0f;
        /*[0x0050]*/ unknown_0050 = 5.0f;
    }

    ePointEmiter::~ePointEmiter()
    {}


    ////////////////////////////////////////////////////////////////
    // ePointEmiter: cloning the object
    ////////////////////////////////////////////////////////////////

    void ePointEmiter::createFromOtherObject(const ePointEmiter &other)
    {}

    ePointEmiter::ePointEmiter(const ePointEmiter &other)
    : eParticleEmiter(other)
    {
        createFromOtherObject(other);
    }

    ePointEmiter& ePointEmiter::operator = (const ePointEmiter &other)
    {
        if ((&other) != this)
        {
            eParticleEmiter::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* ePointEmiter::cloneFromMe() const
    {
        return new ePointEmiter(*this);
    }

}
