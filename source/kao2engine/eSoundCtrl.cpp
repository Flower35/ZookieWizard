#include <kao2engine/eSoundCtrl.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSoundCtrl interface
    // <kao2.0056D699> (constructor)
    // <kao2.0056D720> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SOUNDCTRL_TYPEINFO
    (
        E_SOUNDCTRL_ID,
        "eSoundCtrl",
        &E_CTRLBASE_TYPEINFO,
        []() -> eObject*
        {
            return new eSoundCtrl;
        }
    );

    TypeInfo* eSoundCtrl::getType() const
    {
        return &E_SOUNDCTRL_TYPEINFO;
    }

    eSoundCtrl::eSoundCtrl()
    : eCtrlBase()
    {
        /*[0x18]*/ keysCount = 0;
        /*[0x1C]*/ keysMaxLength = 0;
        /*[0x20]*/ keys = nullptr;
    }

    eSoundCtrl::~eSoundCtrl()
    {
        if (nullptr != keys)
        {
            delete[](keys);
        }
    }


    ////////////////////////////////////////////////////////////////
    // Sound Key Structure
    // <kao2.0056D300> (counstructor)
    // <kao2.0056D320> (destructor)
    // <kao2.0056C200> (serialization)
    ////////////////////////////////////////////////////////////////

    eSoundKeyBase::eSoundKeyBase()
    {
        time = 0;
        volume = 1.0f;
        unknown_0C = false;
    }

    void eSoundKeyBase::serializeSoundKey(Archive &ar)
    {
        /* Time */
        ar.readOrWrite(&time, 0x04);

        /* Sound file name */
        ar.serializeString(sampleName);

        /* Volume */
        ar.readOrWrite(&volume, 0x04);

        /* [0x0C] unknown */
        ar.readOrWrite(&unknown_0C, 0x01);
    }


    ////////////////////////////////////////////////////////////////
    // eSoundCtrl serialization
    // <kao2.0056D000>
    ////////////////////////////////////////////////////////////////
    void eSoundCtrl::serialize(Archive &ar)
    {
        int32_t i;

        /* [0x08] unknown */
        ar.readOrWrite(&(unknown_08[0]), 0x04);
        ar.readOrWrite(&(unknown_08[1]), 0x04);
        ar.readOrWrite(&(unknown_08[2]), 0x04);
        ar.readOrWrite(&(unknown_08[3]), 0x04);

        /* Sound keys geoup */

        if (ar.isInReadMode())
        {
            if (nullptr != keys)
            {
                delete[](keys);
            }

            ar.readOrWrite(&keysMaxLength, 0x04);

            keys = new eSoundKeyBase [keysMaxLength];

            for (i = 0; i < keysMaxLength; i++)
            {
                keys[i].serializeSoundKey(ar);

                keysCount = (i+1);
            }
        }
        else
        {
            ar.readOrWrite(&keysCount, 0x04);

            for (i = 0; i < keysCount; i++)
            {
                keys[i].serializeSoundKey(ar);
            }
        }
    }

}
