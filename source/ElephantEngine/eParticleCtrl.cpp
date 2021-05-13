#include <ElephantEngine/eParticleCtrl.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eParticleCtrl interface
    // <kao2.004306A0> (constructor)
    // <kao2.00430740> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_PARTICLECTRL_TYPEINFO
    (
        E_PARTICLECTRL_ID,
        "eParticleCtrl",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eParticleCtrl;
        }
    );

    const TypeInfo* eParticleCtrl::getType() const
    {
        return &E_PARTICLECTRL_TYPEINFO;
    }

    eParticleCtrl::eParticleCtrl()
    : Gadget()
    {}

    eParticleCtrl::~eParticleCtrl()
    {}


    ////////////////////////////////////////////////////////////////
    // eParticleCtrl: cloning the object
    ////////////////////////////////////////////////////////////////

    void eParticleCtrl::createFromOtherObject(const eParticleCtrl &other)
    {}

    eParticleCtrl::eParticleCtrl(const eParticleCtrl &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eParticleCtrl& eParticleCtrl::operator = (const eParticleCtrl &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eParticleCtrl::cloneFromMe() const
    {
        return new eParticleCtrl(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eParticleCtrl: serialization
    // <kao2.00430C40>
    ////////////////////////////////////////////////////////////////
    void eParticleCtrl::serialize(Archive &ar)
    {
        /* (NOTE: GADGET FUNCTION IS NOT CALLED) */

        if (ar.isInReadMode())
        {
            name = getDefaultGadgetName();
        }
    }


    ////////////////////////////////////////////////////////////////
    // eParticleCtrl: get default name (scripting shenanigans)
    ////////////////////////////////////////////////////////////////
    eString eParticleCtrl::getDefaultGadgetName() const
    {
        return "prt";
    }

}
