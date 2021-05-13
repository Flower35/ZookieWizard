#include <ElephantEngine/eSndEmiterOmni.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSndEmiterOmni interface
    // <kao2.0056C6D0> (constructor)
    // <kao2.0056C7E0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SNDEMITEROMNI_TYPEINFO
    (
        E_SNDEMITEROMNI_ID,
        "eSndEmiterOmni",
        &E_SNDEMITER_TYPEINFO,
        []() -> eObject*
        {
            return new eSndEmiterOmni;
        }
    );

    const TypeInfo* eSndEmiterOmni::getType() const
    {
        return &E_SNDEMITEROMNI_TYPEINFO;
    }

    eSndEmiterOmni::eSndEmiterOmni()
    : eSndEmiter()
    {
        /*[0xC8]*/ unknown_C8 = 1.0f;
        /*[0xCC]*/ unknown_CC = 1.0f;
    }

    eSndEmiterOmni::~eSndEmiterOmni()
    {}


    ////////////////////////////////////////////////////////////////
    // eSndEmiterOmni: cloning the object
    ////////////////////////////////////////////////////////////////

    void eSndEmiterOmni::createFromOtherObject(const eSndEmiterOmni &other)
    {
        unknown_C8 = other.unknown_C8;
        unknown_CC = other.unknown_CC;
    }

    eSndEmiterOmni::eSndEmiterOmni(const eSndEmiterOmni &other)
    : eSndEmiter(other)
    {
        createFromOtherObject(other);
    }

    eSndEmiterOmni& eSndEmiterOmni::operator = (const eSndEmiterOmni &other)
    {
        if ((&other) != this)
        {
            eSndEmiter::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eSndEmiterOmni::cloneFromMe() const
    {
        return new eSndEmiterOmni(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eSndEmiterOmni: serialization
    // <kao2.0056C600>
    ////////////////////////////////////////////////////////////////
    void eSndEmiterOmni::serialize(Archive &ar)
    {
        eSndEmiter::serialize(ar);

        /* [0xC8] unknown */
        ar.readOrWrite(&unknown_C8, 0x04);

        /* [0xCC] unknown */
        ar.readOrWrite(&unknown_CC, 0x04);
    }

}
