#include <kao2engine/eTrack.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eTrack interface
    // <kao2.004B5FB9> (constructor)
    // <kao2.004493D0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_TRACK_TYPEINFO
    (
        E_TRACK_ID,
        "eTrack",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return new eTrack;
        }
    );

    TypeInfo* eTrack::getType() const
    {
        return &E_TRACK_TYPEINFO;
    }

    eTrack::eTrack()
    : eRefCounter()
    {
        /*[0x0C]*/ startFrame = 0;
        /*[0x10]*/ endFrame = 0;
        /*[0x14]*/ loopType = loopTypeEnum::SINGLE;
    }

    eTrack::~eTrack() {}


    ////////////////////////////////////////////////////////////////
    // eTrack serialization
    // <kao2.004B5D50>
    ////////////////////////////////////////////////////////////////
    void eTrack::serialize(Archive &ar)
    {
        /* Nazwa animacji */
        ar.serializeString(name);

        /* Klatka pocz¹tkowa i klatka koñcowa */
        ar.readOrWrite(&startFrame, 0x04);
        ar.readOrWrite(&endFrame, 0x04);

        /* Rodzaj zapêtlania animacji */
        ar.readOrWrite(&loopType, 0x04);

        /* --dodatek-- Archiwa nigdy nie posiada³y tej wersji */
        if (ar.getVersion() < 0x7D)
        {
            throw ErrorMessage
            (
                "eTrack::serialize():\n" \
                "ar.version() 125 required!"
            );
        }
    }


    ////////////////////////////////////////////////////////////////
    // eTrack: get `Log.print()` message
    ////////////////////////////////////////////////////////////////
    eString eTrack::getLogPrintMessage() const
    {
        eString result = eObject::getLogPrintMessage();

        result += "\n - \"";
        result += name;
        result += "\"";

        return result;
    }


    ////////////////////////////////////////////////////////////////
    // eTrack: get or set the track name
    ////////////////////////////////////////////////////////////////

    eString eTrack::getStringRepresentation() const
    {
        return name;
    }

    void eTrack::setName(eString new_name)
    {
        name = new_name;
    }


    ////////////////////////////////////////////////////////////////
    // eTrack: get or set the first keyframe number
    ////////////////////////////////////////////////////////////////

    float eTrack::getStartFrame() const
    {
        return startFrame;
    }

    void eTrack::setStartFrame(float new_value)
    {
        startFrame = new_value;
    }


    ////////////////////////////////////////////////////////////////
    // eTrack: get or set the number of keyframes
    ////////////////////////////////////////////////////////////////

    float eTrack::getEndFrame() const
    {
        return endFrame;
    }

    void eTrack::setEndFrame(float new_value)
    {
        endFrame = new_value;
    }


    ////////////////////////////////////////////////////////////////
    // eTrack: get or set the looping type
    ////////////////////////////////////////////////////////////////

    int32_t eTrack::getLoopType() const
    {
        return loopType;
    }

    void eTrack::setLoopType(int32_t new_value)
    {
        loopType = new_value;
    }

}
