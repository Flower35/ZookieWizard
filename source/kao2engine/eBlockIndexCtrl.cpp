#include <kao2engine/eBlockIndexCtrl.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eBlockIndexCtrl interface
    // <kao2.004BD549> (constructor)
    // <kao2.004BD5E0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_BLOCKINDEXCTRL_TYPEINFO
    (
        E_BLOCKINDEXCTRL_ID,
        "eBlockIndexCtrl",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return new eBlockIndexCtrl;
        }
    );

    TypeInfo* eBlockIndexCtrl::getType() const
    {
        return &E_BLOCKINDEXCTRL_TYPEINFO;
    }

    eBlockIndexCtrl::eBlockIndexCtrl()
    : eRefCounter()
    {
        /*[0x08]*/ blocksCount = 0;
        /*[0x0C]*/ blocksMaxLength = 0;
        /*[0x10]*/ blocks = nullptr;
    }

    eBlockIndexCtrl::~eBlockIndexCtrl()
    {
        if (nullptr != blocks)
        {
            delete[](blocks);
        }
    }


    ////////////////////////////////////////////////////////////////
    // Block Index Structure
    // <kao2.004BD1E0> (serialization)
    ////////////////////////////////////////////////////////////////

    BlockIndexBase::BlockIndexBase()
    {
        /*[0x00]*/ aID = 0;
        /*[0x04]*/ unknown_04 = 0;
        /*[0x08]*/ startFrame = 0;
        /*[0x0C]*/ endFrame = 1.0f;
        /*[0x10]*/ unknown_10 = 0;
    }

    void BlockIndexBase::serializeBlockIndex(Archive &ar)
    {
        ar.readOrWrite(&aID, 0x04);
        ar.readOrWrite(&unknown_04, 0x04);
        ar.readOrWrite(&startFrame, 0x04);
        ar.readOrWrite(&endFrame, 0x04);
        ar.readOrWrite(&unknown_10, 0x04);
    }


    ////////////////////////////////////////////////////////////////
    // eBlockIndexCtrl serialization
    // <kao2.004BD350>
    ////////////////////////////////////////////////////////////////
    void eBlockIndexCtrl::serialize(Archive &ar)
    {
        int32_t i;

        if (ar.isInReadMode())
        {
            if (nullptr != blocks)
            {
                delete[](blocks);
            }

            ar.readOrWrite(&blocksMaxLength, 0x04);

            blocks = new BlockIndexBase [blocksMaxLength];

            for (i = 0; i < blocksMaxLength; i++)
            {
                blocks[i].serializeBlockIndex(ar);

                blocksCount = (i+1);
            }
        }
        else
        {
            ar.readOrWrite(&blocksCount, 0x04);

            for (i = 0; i < blocksCount; i++)
            {
                blocks[i].serializeBlockIndex(ar);
            }
        }
    }

}
