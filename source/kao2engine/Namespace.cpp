#include <kao2engine/Namespace.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Namespace interface
    // <kao2.0059D160> (constructor)
    // <kao2.0059D2B0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_NAMESPACE_TYPEINFO
    (
        E_NAMESPACE_ID,
        "Namespace",
        &E_STATE_TYPEINFO,
        []() -> eObject*
        {
            return new Namespace;
        }
    );

    TypeInfo* Namespace::getType() const
    {
        return &E_NAMESPACE_TYPEINFO;
    }

    Namespace::Namespace()
    : State("", nullptr)
    {
        /*[0x78]*/ unknown_0078 = nullptr;
        /*[0x80]*/ isPersistent = false;

        nodeRefNames_count = 0;
        nodeRefNames_maxLength = 0;
        nodeRefNames = nullptr;
    }

    Namespace::~Namespace()
    {
        if (nullptr != nodeRefNames)
        {
            delete[](nodeRefNames);
        }

        unknown_0078->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // Namespace serialization
    // <kao2.0059D3D0>
    ////////////////////////////////////////////////////////////////
    void Namespace::serialize(Archive &ar)
    {
        int32_t i;

        if (ar.getVersion() <= 0x88)
        {
            /* [0x78] unknown */
            ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&unknown_0078, &E_NAMESPACE_TYPEINFO);

            /* State */
            State::serialize(ar);

            /* [0x80] The "persistent" modifier */
            if (ar.getVersion() >= 0x7B)
            {
                ar.readOrWrite(&isPersistent, 0x01);
            }
            else
            {
                isPersistent = false;
            }
        }
        else if (ar.getVersion() >= 0x89)
        {
            State::serialize(ar);

            /* [0x78/0x7C] unknown */
            ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&unknown_0078, &E_NAMESPACE_TYPEINFO);

            /* [0x80/0x84] unknown */
            ar.readOrWrite(&isPersistent, 0x01);

            /* [0x88] unknown */
            ar.readOrWrite(&unknown_0088, 0x04);

            /* [0x8C] unknown */
            ar.readOrWrite(&unknown_008C, 0x04);

            /* [0x90] NodeRef names in Scene */

            if (ar.isInReadMode())
            {
                if (nullptr != nodeRefNames)
                {
                    delete[](nodeRefNames);
                    nodeRefNames = nullptr;

                    nodeRefNames_maxLength = 0;
                    nodeRefNames_count = 0;
                }

                ar.readOrWrite(&nodeRefNames_maxLength, 0x04);

                nodeRefNames = new eString [nodeRefNames_maxLength];

                for (i = 0; i < nodeRefNames_maxLength; i++)
                {
                    ar.serializeString(nodeRefNames[i]);

                    nodeRefNames_count = (i+1);
                }
            }
            else
            {
                ar.readOrWrite(&nodeRefNames_count, 0x04);

                for (i = 0; i < nodeRefNames_count; i++)
                {
                    ar.serializeString(nodeRefNames[i]);
                }
            }
        }
    }

}
