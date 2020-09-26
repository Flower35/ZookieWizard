#include <kao2engine/eSndEmiter.h>
#include <kao2ar/Archive.h>

#include <kao2engine/eSoundCtrl.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSndEmiter interface
    // <kao2.????????> (constructor)
    // <kao2.00569FF0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SNDEMITER_TYPEINFO
    (
        E_SNDEMITER_ID,
        "eSndEmiter",
        &E_TRANSFORM_TYPEINFO,
        []() -> eObject*
        {
            return nullptr;
        }
    );

    TypeInfo* eSndEmiter::getType() const
    {
        return &E_SNDEMITER_TYPEINFO;
    }

    eSndEmiter::eSndEmiter()
    : eTransform()
    {}

    eSndEmiter::~eSndEmiter()
    {}


    ////////////////////////////////////////////////////////////////
    // eSndEmiter: cloning the object
    ////////////////////////////////////////////////////////////////

    void eSndEmiter::createFromOtherObject(const eSndEmiter &other)
    {
        controllers = other.controllers;
    }

    eSndEmiter::eSndEmiter(const eSndEmiter &other)
    : eTransform(other)
    {
        createFromOtherObject(other);
    }

    eSndEmiter& eSndEmiter::operator = (const eSndEmiter &other)
    {
        if ((&other) != this)
        {
            eTransform::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eSndEmiter::cloneFromMe() const
    {
        return nullptr;
    }


    ////////////////////////////////////////////////////////////////
    // eSndEmiter: serialization
    // <kao2.0056A830>
    ////////////////////////////////////////////////////////////////
    void eSndEmiter::serialize(Archive &ar)
    {
        int32_t i = 0;

        eTransform::serialize(ar);

        /* Sound controllers group */
        controllers.serialize(ar, &E_SOUNDCTRL_TYPEINFO);

        /* Something deprecated */
        ar.readOrWrite(&i, 0x04);
        if (0 != i)
        {
            throw ErrorMessage
            (
                "eSndEmiter::serialize():\n" \
                "ar.version() no longer supporter. THIS SHOULD NEVER HAPPEN."
            );
        }
    }

}
