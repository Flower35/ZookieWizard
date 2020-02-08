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
            /*[0x14]*/ int loopType;

        /*** Methods ***/

        public:

            eTrack();
            ~eTrack();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            eString getStringRepresentation() const override;
            eString getLogPrintMessage() const override;

            float getStartFrame() const;
            float getEndFrame() const;

    };


    ////////////////////////////////////////////////////////////////
    // eTrack TypeInfo
    // <kao2.0x004B5F80> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_TRACK_ID = 0xAC000000;

    extern TypeInfo E_TRACK_TYPEINFO;

}

#endif
