#include <kao2engine/eAnimState.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eAnimState interface
    // <kao2.004B6150> (constructor)
    // <kao2.004B6210> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_ANIMSTATE_TYPEINFO
    (
        E_ANIMSTATE_ID,
        "eAnimState",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return new eAnimState;
        }
    );

    TypeInfo* eAnimState::getType() const
    {
        return &E_ANIMSTATE_TYPEINFO;
    }

    eAnimState::eAnimState()
    : eRefCounter()
    {
        /*[0x0C]*/ unknown0C = 1.0f;
        /*[0x30]*/ w = 1.0f;

        /*[0x08]*/ aID = 0;
        /*[0x2C]*/ bs = 0;
        /*[0x28]*/ bt = 0;
        /*[0x44]*/ bet = 0;
        /*[0x40]*/ bef = 0;
        /*[0x10]*/ time = 0;
        /*[0x14]*/ unknown14 = 0;
        /*[0x18]*/ citt = 0;
        /*[0x1C]*/ pitt = 0;
        /*[0x20]*/ cott = 0;
        /*[0x24]*/ pott = 0;

        /*[0x34]*/ startFrame = 0;
        /*[0x38]*/ endFrame = 0;
        /*[0x3C]*/ loopType = loopTypeEnum::REPEAT;
    }

    eAnimState::~eAnimState() {}


    ////////////////////////////////////////////////////////////////
    // eAnimState serialization
    // <kao2.004B6040>
    ////////////////////////////////////////////////////////////////
    void eAnimState::serialize(Archive &ar)
    {
        ar.readOrWrite(&aID, 0x04);
        ar.readOrWrite(&unknown0C, 0x04);
        ar.readOrWrite(&time, 0x04);
        ar.readOrWrite(&citt, 0x04);
        ar.readOrWrite(&pitt, 0x04);
        ar.readOrWrite(&bt, 0x04);
        ar.readOrWrite(&bs, 0x04);
        ar.readOrWrite(&w, 0x04);
        ar.readOrWrite(&loopType, 0x04);

        ar.readOrWrite(&startFrame, 0x04);
        ar.readOrWrite(&endFrame, 0x04);

        ar.readOrWrite(&unknown14, 0x04);

        ar.readOrWrite(&cott, 0x04);
        ar.readOrWrite(&pott, 0x04);
        ar.readOrWrite(&bef, 0x04);
        ar.readOrWrite(&bet, 0x04);
    }


    ////////////////////////////////////////////////////////////////
    // eAnimState: get or set the time for animations
    ////////////////////////////////////////////////////////////////

    float eAnimState::getTime() const
    {
        return citt;
    }

    void eAnimState::setTime(float current_time)
    {
        citt = current_time;
    }


    ////////////////////////////////////////////////////////////////
    // eAnimState: get or set the animation ID
    ////////////////////////////////////////////////////////////////

    int eAnimState::getAnimId() const
    {
        return aID;
    }

    void eAnimState::setAnimId(int32_t current_anim_id)
    {
        aID = current_anim_id;
    }


    ////////////////////////////////////////////////////////////////
    // eAnimState: get or set the first keyframe number
    ////////////////////////////////////////////////////////////////

    float eAnimState::getStartFrame() const
    {
        return startFrame;
    }

    void eAnimState::setStartFrame(float new_value)
    {
        startFrame = new_value;
    }


    ////////////////////////////////////////////////////////////////
    // eAnimState: get or set the number of keyframes
    ////////////////////////////////////////////////////////////////

    float eAnimState::getEndFrame() const
    {
        return endFrame;
    }

    void eAnimState::setEndFrame(float new_value)
    {
        endFrame = new_value;
    }


    ////////////////////////////////////////////////////////////////
    // eAnimState: get or set the looping type
    ////////////////////////////////////////////////////////////////

    int32_t eAnimState::getLoopType() const
    {
        return loopType;
    }

    void eAnimState::setLoopType(int32_t new_value)
    {
        loopType = new_value;
    }

}
