#ifndef H_KAO2AR_TRACK
#define H_KAO2AR_TRACK

#include <kao2engine/eRefCounter.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eTrack interface
    // <kao2.005CF7C8> (vptr)
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

        private:

            void createFromOtherObject(const eTrack &other);

        public:

            eTrack(const eTrack &other);
            eTrack& operator = (const eTrack &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            eString getStringRepresentation() const override;
            eString getLogPrintMessage() const override;

            /* << eTrack >> */

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
    // <kao2.004B5F50> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_TRACK_ID = 0xAC000000;

    extern TypeInfo E_TRACK_TYPEINFO;

}

#endif
