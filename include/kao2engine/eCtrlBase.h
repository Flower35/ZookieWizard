#ifndef H_KAO2AR_CTRLBASE
#define H_KAO2AR_CTRLBASE

#include <kao2engine/eRefCounter.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCtrlBase interface
    // <kao2.005D1A60> (vptr)
    ////////////////////////////////////////////////////////////////

    class eCtrlBase : public eRefCounter
    {
        /*** Methods ***/

        public:

            eCtrlBase();
            ~eCtrlBase();

        private:

            void createFromOtherObject(const eCtrlBase &other);

        public:

            eCtrlBase(const eCtrlBase &other);
            eCtrlBase& operator = (const eCtrlBase &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eCtrlBase TypeInfo
    // <kao2.004A0730> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_CTRLBASE_ID = 0x9001;

    extern TypeInfo E_CTRLBASE_TYPEINFO;

}

#endif
