#include <kao2engine/eLeafCtrl.h>
#include <kao2ar/Archive.h>

#include <kao2ar/eAnimate.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eLeafCtrl interfaces
    // <kao2.004A2D50> (constructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_LEAFCTRL_FLOAT_TYPEINFO
    (
        E_LEAFCTRL_FLOAT_ID,
        "eLeafCtrl<eFloatKey>",
        &E_CTRL_FLOAT_TYPEINFO,
        []() -> eObject*
        {
            return new eLeafCtrl<float>;
        }
    );

    TypeInfo* eLeafCtrl<float>::getType() const
    {
        return &E_LEAFCTRL_FLOAT_TYPEINFO;
    }

    TypeInfo E_LEAFCTRL_EPOINT3_TYPEINFO
    (
        E_LEAFCTRL_EPOINT3_ID,
        "eLeafCtrl<ePoint3Key>",
        &E_CTRL_EPOINT3_TYPEINFO,
        []() -> eObject*
        {
            return new eLeafCtrl<ePoint3>;
        }
    );

    TypeInfo* eLeafCtrl<ePoint3>::getType() const
    {
        return &E_LEAFCTRL_EPOINT3_TYPEINFO;
    }

    TypeInfo E_LEAFCTRL_EQUAT_TYPEINFO
    (
        E_LEAFCTRL_EQUAT_ID,
        "eLeafCtrl<eRotationKey>",
        &E_CTRL_EQUAT_TYPEINFO,
        []() -> eObject*
        {
            return new eLeafCtrl<eQuat>;
        }
    );

    TypeInfo* eLeafCtrl<eQuat>::getType() const
    {
        return &E_LEAFCTRL_EQUAT_TYPEINFO;
    }

    template <typename T>
    eLeafCtrl<T>::eLeafCtrl()
    : eCtrl<T>()
    {
        /*[0x10]*/ keysCount = 0;
        /*[0x14]*/ keysMaxLength = 0;
        /*[0x18]*/ keys = nullptr;

        /*[0x08]*/ unknown_08 = 0;
        /*[0x0C]*/ unknown_0C = 0;
    }

    template <typename T>
    eLeafCtrl<T>::~eLeafCtrl()
    {
        if (nullptr != keys)
        {
            delete[](keys);
        }
    }


    ////////////////////////////////////////////////////////////////
    // eKeyBase: serialize
    // <kao2.004A5400>: "eFloatKey"
    // <kao2.004A5370>: "ePoint3Key"
    // <kao2.004A52A0>: "eRotationKey"
    ////////////////////////////////////////////////////////////////
    template <typename T>
    void eKeyBase<T>::serializeKey(Archive &ar)
    {
        ar.readOrWrite(&time, 0x04);

        ar.readOrWrite(&(data[0]), sizeof(T));
        ar.readOrWrite(&(data[1]), sizeof(T));
        ar.readOrWrite(&(data[2]), sizeof(T));
    }


    ////////////////////////////////////////////////////////////////
    // eLeafCtrl: animation function
    // Find the best keyframe ID for given time
    // <kao2.004A0630>: "eFloatKey"
    // <kao2.004A06D0>: "ePoint3Key"
    // <kao2.004A0680>: "eRotationKey"
    ////////////////////////////////////////////////////////////////
    template <typename T>
    int eLeafCtrl<T>::getKeyframeId(float time) const
    {
        int i = 0;
        int j = keysCount - 1;
        int k;

        if (j >= 1)
        {
            do
            {
                k = (i + j + 1) / 2;

                if (keys[k].time == time)
                {
                    return k;
                }
                else if (keys[k].time < time)
                {
                    i = k;
                }
                else
                {
                    j = k - 1;
                }
            }
            while (i < j);
        }

        return i;
    }


    ////////////////////////////////////////////////////////////////
    // eLeafCtrl: animation function
    // Interpolate between keyframes
    // "LERP" for "float" and "ePoint3"
    // "SLERP" for "eQuat"
    ////////////////////////////////////////////////////////////////

    float eLeafCtrl<float>::interpolate(float ratio, float &first, float &second, float &other) const
    {
        float result = (first * (1.0f - ratio)) + (second * ratio);

        return (result + other);
    }

    ePoint3 eLeafCtrl<ePoint3>::interpolate(float ratio, ePoint3 &first, ePoint3 &second, ePoint3 &other) const
    {
        /* <kao2.004A0500> */

        ePoint3 result = (first * (1.0f - ratio)) + (second * ratio);

        return (result + other);
    }

    eQuat eLeafCtrl<eQuat>::interpolate(float ratio, eQuat &first, eQuat &second, eQuat &other) const
    {
        /* <kao2.004A4741> */

        eQuat result = (first * (1.0f - ratio)) + (second * ratio);

        result = result + other;

        result.normalize();

        return result;
    }


    ////////////////////////////////////////////////////////////////
    // eLeafCtrl: animation function
    // [[vptr]+0x28] Modify [scale/rotation/position] based on current time
    // <kao2.004A2ED0>: "eFloatKey"
    // <kao2.004A3770>: "ePoint3Key"
    // <kao2.004A4280>: "eRotationKey"
    ////////////////////////////////////////////////////////////////
    template <typename T>
    void eLeafCtrl<T>::ctrlApplyTransform(T* e, float time) const
    {
        T test = {0};

        if (nullptr != e)
        {
            if (0 == keysCount)
            {
                (*e) = defaultKeyframeValue;

                return;
            }
            else if (1 == keysCount)
            {
                (*e) = keys[0].data[0];

                return;
            }
            else
            {
                switch ((time > keys[0].time) ? unknown_0C : unknown_08)
                {
                    case 0:
                    {
                        if (time <= keys[0].time)
                        {
                            (*e) = keys[0].data[0];

                            return;
                        }
                        else if (time >= keys[keysCount - 1].time)
                        {
                            (*e) = keys[keysCount - 1].data[0];

                            return;
                        }

                        break;
                    }

                    case 1:
                    case 2:
                    {
                        float x = keys[keysCount - 1].time - keys[0].time;
                        float y = time - keys[0].time;

                        float w = fmod(y, x);

                        if (w < 0)
                        {
                            w += x;
                        }

                        time = w + keys[0].time;

                        break;
                    }

                    case 3:
                    {
                        if (time >= keys[keysCount - 1].time)
                        {
                            (*e) = keys[keysCount - 1].data[0];

                            return;
                        }

                        float x = keys[keysCount - 1].time - keys[0].time;
                        float y = time - keys[0].time;
                        float z = x + x;

                        float w = fmod(y, z);

                        if (w < 0)
                        {
                            w += z;
                        }

                        if (w > x)
                        {
                            w = z - w;
                        }

                        time = w + keys[0].time;

                        break;
                    }

                    case 4:
                    {
                        /* (--dsp--) <kao2.004A303E> */

                        break;
                    }

                    case 5:
                    {
                        float x = keys[keysCount - 1].time - keys[0].time;
                        float y = time - keys[0].time;

                        float z = floor(y / x);
                        float w = fmod(y, x);

                        if (w < 0)
                        {
                            w += x;
                        }

                        time = w + keys[0].time;

                        test = (keys[keysCount - 1].data[0] - keys[0].data[0]) * z;

                        break;
                    }
                }

                int id = getKeyframeId(time);

                float ratio = (time - keys[id].time) / (keys[id + 1].time - keys[id].time);

                (*e) = interpolate(ratio, keys[id].data[0], keys[id + 1].data[0], test);
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eLeafCtrl serialization
    // <kao2.004A31B0>: "eFloatKey"
    // <kao2.004A3B50>: "ePoint3Key"
    // <kao2.004A47D0>: "eRotationKey"
    ////////////////////////////////////////////////////////////////
    template <typename T>
    void eLeafCtrl<T>::serialize(Archive &ar)
    {
        int32_t i;

        /* Unknown identifiers */

        ar.readOrWrite(&unknown_08, 0x04);

        ar.readOrWrite(&unknown_0C, 0x04);

        /* Keys group */

        if (ar.isInReadMode())
        {
            ar.readOrWrite(&keysMaxLength, 0x04);

            keys = new eKeyBase<T> [keysMaxLength];

            for (i = 0; i < keysMaxLength; i++)
            {
                keys[i].serializeKey(ar);

                keysCount = (i+1);
            }
        }
        else
        {
            ar.readOrWrite(&keysCount, 0x04);

            for (i = 0; i < keysCount; i++)
            {
                keys[i].serializeKey(ar);
            }
        }

        /* Possibly a default key */
        /* "eFloatKey": [0x1C] (4 bytes) */
        /* "ePoint3Key": [0x1C] [0x20] [0x24] (12 bytes) */
        /* "eRotationKey": [0x1C] [0x20] [0x24] [0x28] (16 bytes) */

        ar.readOrWrite(&defaultKeyframeValue, sizeof(T));
    }


    ////////////////////////////////////////////////////////////////
    // eLeafCtrl: set static keyframes for fun
    ////////////////////////////////////////////////////////////////
    template <typename T>
    void eLeafCtrl<T>::ctrlSetStaticKeyframe(T &new_value, int32_t param)
    {
        if (0x01 == param)
        {
            clearLeafKeys();

            defaultKeyframeValue = new_value;
        }
    }


    ////////////////////////////////////////////////////////////////
    // eLeafCtrl: clear keyframes for specific animation
    ////////////////////////////////////////////////////////////////
    template <typename T>
    void eLeafCtrl<T>::ctrlClearKeyframes(int anim_id)
    {
        clearLeafKeys();
    }


    ////////////////////////////////////////////////////////////////
    // eLeafCtrl: update specific animation
    ////////////////////////////////////////////////////////////////
    template <typename T>
    void eLeafCtrl<T>::ctrlAddKeyframe(int anim_id, float new_time, T &new_data, int param)
    {
        addLeafKey(new_time, new_data);
    }


    ////////////////////////////////////////////////////////////////
    // eLeafCtrl: set default value (used when there are no keys)
    ////////////////////////////////////////////////////////////////
    template <typename T>
    void eLeafCtrl<T>::setDefaultValue(T new_value)
    {
        defaultKeyframeValue = new_value;
    }


    ////////////////////////////////////////////////////////////////
    // eLeafCtrl: clear all leaf keys
    ////////////////////////////////////////////////////////////////
    template <typename T>
    void eLeafCtrl<T>::clearLeafKeys()
    {
        keysCount = 0;
        keysMaxLength = 0;

        if (nullptr != keys)
        {
            delete[](keys);
            keys = nullptr;
        }
    }


    ////////////////////////////////////////////////////////////////
    // eLeafCtrl: add a new leaf key
    ////////////////////////////////////////////////////////////////
    template <typename T>
    void eLeafCtrl<T>::addLeafKey(float new_time, T new_data)
    {
        if ((keysCount + 1) >= keysMaxLength)
        {
            eKeyBase<T>* dummy_keys = new eKeyBase<T> [keysMaxLength + 1];

            if (nullptr != keys)
            {
                for (int i = 0; i < keysCount; i++)
                {
                    dummy_keys[i] = keys[i];
                }

                delete[](keys);
            }

            keys = dummy_keys;

            keysMaxLength++;
        }

        /* Find the right index based on the passed keyframe number */

        int b = (-1);

        for (int a = 0; (b < 0) && (a < keysCount); a++)
        {
            if (keys[a].time > new_time)
            {
                b = a;
            }
        }

        if (b > 0)
        {
            for (int a = keysCount - 1; a >= b; a--)
            {
                keys[a + 1] = keys[a];
            }
        }
        else
        {
            b = keysCount;
        }

        keys[b].time = new_time;
        keys[b].data[0] = new_data;

        keysCount++;
    }


    ////////////////////////////////////////////////////////////////
    // Explicit templates
    ////////////////////////////////////////////////////////////////

    template class eLeafCtrl<float>;

    template class eLeafCtrl<ePoint3>;

    template class eLeafCtrl<eQuat>;

}
