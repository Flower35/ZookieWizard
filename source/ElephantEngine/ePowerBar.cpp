#include <ElephantEngine/ePowerBar.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePowerBar interface
    // <kao2.00453BC0> (constructor)
    // <kao2.00453C60> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_POWERBAR_TYPEINFO
    (
        E_POWERBAR_ID,
        "ePowerBar",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new ePowerBar;
        }
    );

    TypeInfo* ePowerBar::getType() const
    {
        return &E_POWERBAR_TYPEINFO;
    }

    ePowerBar::ePowerBar()
    : Gadget()
    {}

    ePowerBar::~ePowerBar()
    {}


    ////////////////////////////////////////////////////////////////
    // ePowerBar: cloning the object
    ////////////////////////////////////////////////////////////////

    void ePowerBar::createFromOtherObject(const ePowerBar &other)
    {}

    ePowerBar::ePowerBar(const ePowerBar &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    ePowerBar& ePowerBar::operator = (const ePowerBar &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* ePowerBar::cloneFromMe() const
    {
        return new ePowerBar(*this);
    }

}
