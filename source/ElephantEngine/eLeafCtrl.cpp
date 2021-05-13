#include <ElephantEngine/eLeafCtrl.h>
#include <ElephantBase/Archive.h>

#include <ElephantBase/eAnimate.h>

namespace ZookieWizard
{
    const char* theLeafOoRT[KAO2_LEAFKEY_OORT_COUNT] =
    {
        "Constant", "Cycle", "Loop", "Ping Pong", "Linear", "Relative Repeat"
    };


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

    const TypeInfo* eLeafCtrl<float>::getType() const
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

    const TypeInfo* eLeafCtrl<ePoint3>::getType() const
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

    const TypeInfo* eLeafCtrl<eQuat>::getType() const
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

        /*[0x08]*/ outOfRangeTypeA = 0;
        /*[0x0C]*/ outOfRangeTypeB = 0;
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
    // eLeafCtrl: cloning the object
    ////////////////////////////////////////////////////////////////

    template <typename T>
    void eLeafCtrl<T>::createFromOtherObject(const eLeafCtrl<T> &other)
    {
        outOfRangeTypeA = other.outOfRangeTypeA;

        outOfRangeTypeB = other.outOfRangeTypeB;

        keysCount = other.keysCount;

        if (keysCount > 0)
        {
            keysMaxLength = keysCount;

            keys = new eKeyBase<T> [keysMaxLength];

            for (int32_t a = 0; a < keysMaxLength; a++)
            {
                keys[a] = other.keys[a];
            }
        }
        else
        {
            keysMaxLength = 0;
            keys = nullptr;
        }

        defaultKeyframeValue = other.defaultKeyframeValue;
    }

    template <typename T>
    eLeafCtrl<T>::eLeafCtrl(const eLeafCtrl<T> &other)
    : eCtrl<T>(other)
    {
        createFromOtherObject(other);
    }

    template <typename T>
    eLeafCtrl<T>& eLeafCtrl<T>::operator = (const eLeafCtrl<T> &other)
    {
        if ((&other) != this)
        {
            eCtrl<T>::operator = (other);

            /****************/

            if (nullptr != keys)
            {
                delete[](keys);
            }

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    template <typename T>
    eObject* eLeafCtrl<T>::cloneFromMe() const
    {
        return new eLeafCtrl<T>(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eKeyBase: serialization
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
    // eLeafCtrl: serialization
    // <kao2.004A31B0>: "eFloatKey"
    // <kao2.004A3B50>: "ePoint3Key"
    // <kao2.004A47D0>: "eRotationKey"
    ////////////////////////////////////////////////////////////////
    template <typename T>
    void eLeafCtrl<T>::serialize(Archive &ar)
    {
        int32_t i;

        /* "Parameter Curve Out-of-Range Types" */

        ar.readOrWrite(&outOfRangeTypeA, 0x04);

        ar.readOrWrite(&outOfRangeTypeB, 0x04);

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
                switch ((time > keys[0].time) ? outOfRangeTypeB : outOfRangeTypeA)
                {
                    case 0: // "Constant"
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

                    case 1: // "Cycle"
                    case 2: // "Loop"
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

                    case 3: // "Ping Pong"
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

                    case 4: // "Linear"
                    {
                        /* (--TODO--) <kao2.004A303E> */

                        break;
                    }

                    case 5: // "Relative Repeat"
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
    void eLeafCtrl<T>::ctrlClearKeyframes(int32_t anim_id)
    {
        clearLeafKeys();
    }


    ////////////////////////////////////////////////////////////////
    // eLeafCtrl: set loop type
    ////////////////////////////////////////////////////////////////
    template <typename T>
    void eLeafCtrl<T>::ctrlSetLoopType(int32_t anim_id, int32_t loop_type, int32_t param)
    {
        if (0x01 == param)
        {
            if (loop_type < 0)
            {
                loop_type = 0;
            }
            else if (loop_type > 5)
            {
                loop_type = 5;
            }

            outOfRangeTypeB = outOfRangeTypeA = loop_type;
        }
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
    // eLeafCtrl: get or set the default value (used when there are no keys)
    ////////////////////////////////////////////////////////////////

    template <typename T>
    T eLeafCtrl<T>::getDefaultValue() const
    {
        return defaultKeyframeValue;
    }

    template <typename T>
    void eLeafCtrl<T>::setDefaultValue(T new_value)
    {
        defaultKeyframeValue = new_value;
    }


    ////////////////////////////////////////////////////////////////
    // eLeafCtrl: get "Out of Range Type"
    ////////////////////////////////////////////////////////////////

    template <typename T>
    int32_t eLeafCtrl<T>::getLeafLoopType(int32_t zero_if_a_otheriwse_b) const
    {
        return (0 == zero_if_a_otheriwse_b) ? outOfRangeTypeA : outOfRangeTypeB;
    }


    ////////////////////////////////////////////////////////////////
    // eLeafCtrl: get the number of leaf keys
    ////////////////////////////////////////////////////////////////
    template <typename T>
    int32_t eLeafCtrl<T>::getLeafKeysCount() const
    {
        return keysCount;
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
    // eLeafCtrl: get the time and data of some key (if it exists)
    ////////////////////////////////////////////////////////////////
    template <typename T>
    bool eLeafCtrl<T>::getIthLeafKey(int32_t id, float &returned_time, T &returned_data)
    {
        if ((id >= 0) && (id < keysCount))
        {
            returned_time = keys[id].time;
            returned_data = keys[id].data[0];

            return true;
        }

        return false;
    }


    ////////////////////////////////////////////////////////////////
    // eLeafCtrl: add a new leaf key
    // (returns the ID of the inserted key)
    ////////////////////////////////////////////////////////////////
    template <typename T>
    int32_t eLeafCtrl<T>::addLeafKey(float new_time, T new_data)
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

        if (b >= 0)
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

        recalculateInterpolationData();

        return b;
    }


    ////////////////////////////////////////////////////////////////
    // eLeafCtrl: remove some leaf key
    ////////////////////////////////////////////////////////////////
    template <typename T>
    bool eLeafCtrl<T>::removeIthLeafKey(int32_t id)
    {
        if ((id >= 0) && (id < keysCount))
        {
            for (int a = id + 1; a < keysCount; a++)
            {
                keys[a - 1] = keys[a];
            }

            keysCount--;

            return true;
        }

        return false;
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
    // Prepare data for cubic interpolations
    ////////////////////////////////////////////////////////////////

    void eLeafCtrl<float>::recalculateInterpolationData()
    {
        if (keysCount >= 1)
        {
            /* No keyframe before the first key */
            keys[0].data[1] = {0};

            /* No keyframe after the last key */
            keys[keysCount - 1].data[2] = {0};

            for (int32_t a = 0; a < (keysCount - 1); a++)
            {
                float control_point = keys[a + 1].data[0] - keys[a].data[0];

                keys[a].data[2] = control_point;
                keys[a + 1].data[1] = control_point;
            }
        }
    }

    void eLeafCtrl<ePoint3>::recalculateInterpolationData()
    {
        if (keysCount >= 1)
        {
            /* No keyframe before the first key */
            keys[0].data[1] = {0};

            /* No keyframe after the last key */
            keys[keysCount - 1].data[2] = {0};

            for (int32_t a = 0; a < (keysCount - 1); a++)
            {
                ePoint3 control_point = keys[a + 1].data[0] - keys[a].data[0];

                keys[a].data[2] = control_point;
                keys[a + 1].data[1] = control_point;
            }
        }
    }

    void eLeafCtrl<eQuat>::recalculateInterpolationData()
    {
        if (keysCount >= 1)
        {
            /* No keyframe before the first key */
            keys[0].data[1] = {0};

            /* No keyframe after the last key */
            keys[keysCount - 1].data[2] = {0};

            for (int32_t a = 0; a < (keysCount - 1); a++)
            {
                eQuat control_point_A = keys[a].data[0];
                eQuat control_point_B = keys[a + 1].data[0];
                eQuat control_point_C = ((control_point_A * 2.0f) + control_point_B) * (1.0f / 3);
                eQuat control_point_D = (control_point_B + control_point_C) * 0.5f;

                keys[a].data[2] = control_point_C;
                keys[a + 1].data[1] = control_point_D;
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // Explicit templates
    ////////////////////////////////////////////////////////////////

    template class eLeafCtrl<float>;

    template class eLeafCtrl<ePoint3>;

    template class eLeafCtrl<eQuat>;

}
