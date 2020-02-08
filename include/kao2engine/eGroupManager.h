#ifndef H_KAO2AR_GROUPMANAGER
#define H_KAO2AR_GROUPMANAGER

#include <kao2engine/eRefCounter.h>

namespace ZookieWizard
{
    class eGroup;

    ////////////////////////////////////////////////////////////////
    // eGroupManager interface
    // <kao2.005CE100> (vptr)
    ////////////////////////////////////////////////////////////////

    class eGroupManager : public eRefCounter
    {

        /*** Properties ***/

        protected:

            /*[0x08]*/ int32_t groupsCount;
            /*[0x0C]*/ int32_t groupsMaxLength;
            /*[0x10]*/ eGroup** groups;

            /*[0x14]*/
            /*[0x18]*/
            /*[0x1C]*/

        /*** Methods ***/

        public:

            eGroupManager();
            ~eGroupManager();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eGroupManager TypeInfo
    // <kao2.0042C930> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_GROUPMANAGER_ID = 0x00FA9283;

    extern TypeInfo E_GROUPMANAGER_TYPEINFO;

}

#endif
