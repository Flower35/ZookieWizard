#include <kao2engine/eXRefProxy.h>
#include <kao2ar/Archive.h>

#include <kao2engine/eXRefTarget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eXRefProxy interface
    // <kao2.004AD360> (constructor)
    // <kao2.004AD4F0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_XREFPROXY_TYPEINFO
    (
        E_XREFPROXY_ID,
        "eXRefProxy",
        &E_NODE_TYPEINFO,
        []() -> eObject*
        {
            return new eXRefProxy(nullptr);
        }
    );

    TypeInfo* eXRefProxy::getType()
    {
        return &E_XREFPROXY_TYPEINFO;
    }

    eXRefProxy::eXRefProxy(eXRefTarget* x)
    : eNode()
    {
        if (nullptr != target)
        {
            target->decRef();
        }

        target = x;

        if (nullptr != target)
        {
            target->incRef();
        }
    }

    eXRefProxy::~eXRefProxy() {}


    ////////////////////////////////////////////////////////////////
    // eXRefProxy serialization
    // <kao2.004AD600>
    ////////////////////////////////////////////////////////////////
    void eXRefProxy::serialize(Archive &ar)
    {
        eNode::serialize(ar);

        /* [0x3C] target link */
        ar.serialize((eObject**)&target, &E_XREFTARGET_TYPEINFO);
    }


    ////////////////////////////////////////////////////////////////
    // eXRefProxy: render in scene
    ////////////////////////////////////////////////////////////////
    void eXRefProxy::renderObject(eAnimate* anim, int32_t draw_flags, eSRP &parent_srp)
    {
        if (nullptr != target)
        {
            target->renderObject(anim, draw_flags, parent_srp);
        }
    }


    ////////////////////////////////////////////////////////////////
    // eXRefProxy: return target (used with eProxy)
    ////////////////////////////////////////////////////////////////
    eXRefTarget* eXRefProxy::getXRefTarget()
    {
        return target;
    }

}
