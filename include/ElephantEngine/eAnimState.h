#ifndef H_KAO2AR_ANIMSTATE
#define H_KAO2AR_ANIMSTATE

#include <ElephantEngine/eRefCounter.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eAnimState interface
    // <kao2.005D21DC> (vptr)
    ////////////////////////////////////////////////////////////////

    class eAnimState : public eRefCounter
    {
        /*** Properties ***/

        protected:

            /*[0x08]*/ int32_t aID;
            /*[0x0C]*/ float unknown_0C;
            /*[0x10]*/ float time;
            /*[0x14]*/ float unknown_14;
            /*[0x18]*/ float citt;
            /*[0x1C]*/ float pitt;
            /*[0x20]*/ float cott;
            /*[0x24]*/ float pott;
            /*[0x28]*/ float bt;
            /*[0x2C]*/ float bs;
            /*[0x30]*/ float w;
            /*[0x34]*/ float startFrame;
            /*[0x38]*/ float endFrame;
            /*[0x3C]*/ int32_t loopType;
            /*[0x40]*/ float bef;
            /*[0x44]*/ float bet;

        /*** Methods ***/

        public:

            eAnimState();
            ~eAnimState();

        private:

            void createFromOtherObject(const eAnimState &other);

        public:

            eAnimState(const eAnimState &other);
            eAnimState& operator = (const eAnimState &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            /* << eAnimState >> */

            float getTime() const;
            void setTime(float current_time);

            int getAnimId() const;
            void setAnimId(int32_t current_anim_id);

            float getStartFrame() const;
            void setStartFrame(float new_value);

            float getEndFrame() const;
            void setEndFrame(float new_value);

            int32_t getLoopType() const;
            void setLoopType(int32_t new_value);

    };


    ////////////////////////////////////////////////////////////////
    // eAnimState TypeInfo
    // <kao2.004B6820> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_ANIMSTATE_ID = 0xAC000001;

    extern TypeInfo E_ANIMSTATE_TYPEINFO;

}

#endif
