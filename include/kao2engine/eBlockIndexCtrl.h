#ifndef H_KAO2AR_BLOCKINDEXCTRL
#define H_KAO2AR_BLOCKINDEXCTRL

#include <kao2engine/eRefCounter.h>

namespace ZookieWizard
{
    ////////////////////////////////////////////////////////////////
    // Block Index Structure
    ////////////////////////////////////////////////////////////////

    struct BlockIndexBase
    {
        /*** Properties ***/

        public:

            /*[0x00]*/ int32_t aID;
            /*[0x04]*/ int32_t unknown_04;
            /*[0x08]*/ float startFrame;
            /*[0x0C]*/ float endFrame;
            /*[0x10]*/ int unknown_10;

        /*** Methods ***/

        public:

            BlockIndexBase();

            void serializeBlockIndex(Archive &ar);
    };

    ////////////////////////////////////////////////////////////////
    // eBlockIndexCtrl interface
    // <kao2.005D2500> (vptr)
    ////////////////////////////////////////////////////////////////

    class eBlockIndexCtrl : public eRefCounter
    {
        /*** Properties ***/

        protected:

            /*[0x08]*/ int32_t blocksCount;
            /*[0x0C]*/ int32_t blocksMaxLength;
            /*[0x10]*/ BlockIndexBase* blocks;

        /*** Methods ***/

        public:

            eBlockIndexCtrl();
            ~eBlockIndexCtrl();

        private:

            void createFromOtherObject(const eBlockIndexCtrl &other);

        public:

            eBlockIndexCtrl(const eBlockIndexCtrl &other);
            eBlockIndexCtrl& operator = (const eBlockIndexCtrl &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;
    };


    ////////////////////////////////////////////////////////////////
    // eBlockIndexCtrl TypeInfo
    // <kao2.004BD4E0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_BLOCKINDEXCTRL_ID = 0x7007;

    extern TypeInfo E_BLOCKINDEXCTRL_TYPEINFO;

}

#endif
