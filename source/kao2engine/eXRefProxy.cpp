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

    TypeInfo* eXRefProxy::getType() const
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
    // eXRefProxy: delete "eXRefTarget" links after destroying "eXRefManager"
    ////////////////////////////////////////////////////////////////
    bool eXRefProxy::deleteXRefTargets()
    {
        target = nullptr;

        /* Notify parent "eGroup" */

        return true;
    }


    ////////////////////////////////////////////////////////////////
    // eXRefProxy: render in scene
    ////////////////////////////////////////////////////////////////
    bool eXRefProxy::renderObject(int32_t draw_flags, eAnimate* anim, eSRP &parent_srp, int32_t marked_id)
    {
        if (false == eNode::renderObject(draw_flags, anim, parent_srp, marked_id))
        {
            return false;
        }

        if (nullptr != target)
        {
            target->renderObject(draw_flags, anim, parent_srp, marked_id);
        }

        return true;
    }


    ////////////////////////////////////////////////////////////////
    // eXRefProxy: return target (used with eProxy)
    ////////////////////////////////////////////////////////////////
    eXRefTarget* eXRefProxy::getXRefTarget() const
    {
        return target;
    }

}
