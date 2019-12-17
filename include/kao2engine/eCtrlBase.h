#ifndef H_KAO2AR_CTRLBASE
#define H_KAO2AR_CTRLBASE

#include <kao2engine/eRefCounter.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCtrlBase interface
    ////////////////////////////////////////////////////////////////

    class eCtrlBase : public eRefCounter
    {

        /*** Methods ***/

        public:

            eCtrlBase();
            ~eCtrlBase();

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eCtrlBase TypeInfo
    // <kao2.004A0760> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_CTRLBASE_ID = 0x9001;

    extern TypeInfo E_CTRLBASE_TYPEINFO;

}

#endif
