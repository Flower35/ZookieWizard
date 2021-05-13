#include <ElephantEngine/eSndEmiterBox.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSndEmiterBox interface
    // <kao2.005AEAB0> (constructor)
    // <kao2.005AEB80> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SNDEMITERBOX_TYPEINFO
    (
        E_SNDEMITERBOX_ID,
        "eSndEmiterBox",
        &E_SNDEMITER_TYPEINFO,
        []() -> eObject*
        {
            return new eSndEmiterBox;
        }
    );

    TypeInfo* eSndEmiterBox::getType() const
    {
        return &E_SNDEMITERBOX_TYPEINFO;
    }

    eSndEmiterBox::eSndEmiterBox()
    : eSndEmiter()
    {
        /*[0xC8]*/ boxBoundMin.x = 1.0f;
        /*[0xCC]*/ boxBoundMin.y = 1.0f;
        /*[0xD0]*/ boxBoundMin.z = 1.0f;

        /*[0xD4]*/ boxBoundMax.x = 2.0f;
        /*[0xD8]*/ boxBoundMax.y = 2.0f;
        /*[0xDC]*/ boxBoundMax.z = 2.0f;
    }

    eSndEmiterBox::~eSndEmiterBox()
    {}


    ////////////////////////////////////////////////////////////////
    // eSndEmiterBox: cloning the object
    ////////////////////////////////////////////////////////////////

    void eSndEmiterBox::createFromOtherObject(const eSndEmiterBox &other)
    {
        boxBoundMin = other.boxBoundMin;
        boxBoundMax = other.boxBoundMax;
    }

    eSndEmiterBox::eSndEmiterBox(const eSndEmiterBox &other)
    : eSndEmiter(other)
    {
        createFromOtherObject(other);
    }

    eSndEmiterBox& eSndEmiterBox::operator = (const eSndEmiterBox &other)
    {
        if ((&other) != this)
        {
            eSndEmiter::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eSndEmiterBox::cloneFromMe() const
    {
        return new eSndEmiterBox(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eSndEmiterBox: serialization
    // <kao2.005AE750>
    ////////////////////////////////////////////////////////////////
    void eSndEmiterBox::serialize(Archive &ar)
    {
        eSndEmiter::serialize(ar);

        boxBoundMin.serialize(ar);
        boxBoundMax.serialize(ar);
    }

}
