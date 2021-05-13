#include <ElephantEngine/eSpider.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSpider interface
    // <kao2.0043A180> (constructor)
    // <kao2.0043A210> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SPIDER_TYPEINFO
    (
        E_SPIDER_ID,
        "eSpider",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new eSpider;
        }
    );

    TypeInfo* eSpider::getType() const
    {
        return &E_SPIDER_TYPEINFO;
    }

    eSpider::eSpider()
    : Gadget()
    {}

    eSpider::~eSpider()
    {}


    ////////////////////////////////////////////////////////////////
    // eSpider: cloning the object
    ////////////////////////////////////////////////////////////////

    void eSpider::createFromOtherObject(const eSpider &other)
    {}

    eSpider::eSpider(const eSpider &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    eSpider& eSpider::operator = (const eSpider &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eSpider::cloneFromMe() const
    {
        return new eSpider(*this);
    }

}
