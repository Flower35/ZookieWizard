#ifndef H_KAO2AR_TRACK
#define H_KAO2AR_TRACK

#include <kao2engine/eRefCounter.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eTrack interface
    ////////////////////////////////////////////////////////////////

    class eTrack : public eRefCounter
    {

        /*** Properties ***/

        protected:

            /*[0x08]*/ eString name;
            /*[0x0C]*/ float startFrame;
            /*[0x10]*/ float endFrame;
            /*[0x14]*/ int32_t loopType;

        /*** Methods ***/

        public:

            eTrack();
            ~eTrack();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            eString getStringRepresentation() const override;
            eString getLogPrintMessage() const override;

            void setName(eString new_name);

            float getStartFrame() const;
            void setStartFrame(float new_value);

            float getEndFrame() const;
            void setEndFrame(float new_value);

            int32_t getLoopType() const;
            void setLoopType(int32_t new_value);

    };


    ////////////////////////////////////////////////////////////////
    // eTrack TypeInfo
    // <kao2.0x004B5F80> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_TRACK_ID = 0xAC000000;

    extern TypeInfo E_TRACK_TYPEINFO;

}

#endif
