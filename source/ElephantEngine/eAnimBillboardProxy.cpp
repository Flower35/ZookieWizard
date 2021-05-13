#include <ElephantEngine/eAnimBillboardProxy.h>
#include <ElephantBase/Archive.h>

#include <ElephantEngine/eAnimBillboardTarget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eAnimBillboardProxy interface
    // <kao_tw.00477740> (constructor)
    // <kao_tw.00477870> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_ANIMBILLBOARDPROXY_TYPEINFO
    (
        E_ANIMBILLBOARDPROXY_ID,
        "eAnimBillboardProxy",
        &E_NODE_TYPEINFO,
        []() -> eObject*
        {
            return new eAnimBillboardProxy;
        }
    );

    const TypeInfo* eAnimBillboardProxy::getType() const
    {
        return &E_ANIMBILLBOARDPROXY_TYPEINFO;
    }

    eAnimBillboardProxy::eAnimBillboardProxy()
    : eNode()
    {
        target = nullptr;

        flags |= 0x10000000;
    }

    eAnimBillboardProxy::~eAnimBillboardProxy()
    {
        target->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // eAnimBillboardProxy: cloning the object
    ////////////////////////////////////////////////////////////////

    void eAnimBillboardProxy::createFromOtherObject(const eAnimBillboardProxy &other)
    {
        target = other.target;
        if (nullptr != target)
        {
            target->incRef();
        }
    }

    eAnimBillboardProxy::eAnimBillboardProxy(const eAnimBillboardProxy &other)
    : eNode(other)
    {
        createFromOtherObject(other);
    }

    eAnimBillboardProxy& eAnimBillboardProxy::operator = (const eAnimBillboardProxy &other)
    {
        if ((&other) != this)
        {
            eNode::operator = (other);

            /****************/

            target->decRef();

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eAnimBillboardProxy::cloneFromMe() const
    {
        return new eAnimBillboardProxy(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eAnimBillboardProxy: serialization
    // <kao_tw.004779C0>
    ////////////////////////////////////////////////////////////////
    void eAnimBillboardProxy::serialize(Archive &ar)
    {
        if (ar.getVersion() < 0x8B)
        {
            throw ErrorMessage
            (
                "eAnimBillboardProxy::serialize():\n" \
                "ar.version() 139 required!"
            );
        }

        eNode::serialize(ar);

        /* [0x40] Anim Billboard Target */

        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&target, &E_ANIMBILLBOARDTARGET_TYPEINFO);
    }

}
