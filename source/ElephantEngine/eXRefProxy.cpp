#include <ElephantEngine/eXRefProxy.h>
#include <ElephantBase/Archive.h>
#include <ElephantBase/eDrawContext.h>

#include <ElephantEngine/eXRefTarget.h>

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
        target = x;

        if (nullptr != target)
        {
            target->incRef();
        }

        unsetFlags(0x0400);
        setFlags(0x10000100);
    }

    eXRefProxy::~eXRefProxy()
    {
        target->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // eXRefProxy: cloning the object
    ////////////////////////////////////////////////////////////////

    void eXRefProxy::createFromOtherObject(const eXRefProxy &other)
    {
        target = other.target;

        if (nullptr != target)
        {
            target->incRef();
        }
    }

    eXRefProxy::eXRefProxy(const eXRefProxy &other)
    : eNode(other)
    {
        createFromOtherObject(other);
    }

    eXRefProxy& eXRefProxy::operator = (const eXRefProxy &other)
    {
        if ((&other) != this)
        {
            eNode::operator = (other);

            /****************/

            target->decRef();

            /****************/

            createFromOtherObject(other);(other);
        }

        return (*this);
    }

    eObject* eXRefProxy::cloneFromMe() const
    {
        return new eXRefProxy(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eXRefProxy: serialization
    // <kao2.004AD600>
    ////////////////////////////////////////////////////////////////
    void eXRefProxy::serialize(Archive &ar)
    {
        eNode::serialize(ar);

        /* [0x3C] target link */
        /* (changed to normal `eRefCounter` serialization for better memory management) */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&target, &E_XREFTARGET_TYPEINFO);
    }


    ////////////////////////////////////////////////////////////////
    // eXRefProxy: update DrawPass flags from children nodes
    ////////////////////////////////////////////////////////////////
    void eXRefProxy::updateDrawPassFlags(uint32_t* parent_flags)
    {
        flags &= (~ 0x70000000);

        if (nullptr != target)
        {
            eNode* local_scene = (eNode*)target->getLocalScene();

            if (nullptr != local_scene)
            {
                local_scene->updateDrawPassFlags(&flags);
            }
        }

        eNode::updateDrawPassFlags(parent_flags);
    }


    ////////////////////////////////////////////////////////////////
    // eXRefProxy: render this node
    ////////////////////////////////////////////////////////////////
    void eXRefProxy::renderNode(eDrawContext &draw_context) const
    {
        if (nullptr != target)
        {
            target->renderXRefScene(draw_context);
        }
    }


    ////////////////////////////////////////////////////////////////
    // eXRefProxy: return target (used with eProxy)
    ////////////////////////////////////////////////////////////////
    eXRefTarget* eXRefProxy::getXRefTarget() const
    {
        return target;
    }

}
