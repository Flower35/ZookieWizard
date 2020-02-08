#include <kao2engine/eSpider.h>
#include <kao2ar/Archive.h>

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

    eSpider::~eSpider() {}

}
