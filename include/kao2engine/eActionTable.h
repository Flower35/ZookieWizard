#ifndef H_KAO2AR_ACTIONTABLE
#define H_KAO2AR_ACTIONTABLE

#include <kao2engine/eRefCounter.h>

namespace ZookieWizard
{
    class eNode;
    class eCameraZonePacket;

    ////////////////////////////////////////////////////////////////
    // Action Struct
    ////////////////////////////////////////////////////////////////

    struct eActionBase
    {
        /*** Properties ***/

            /*[0x04]*/ eNode* nodeTarget;
            /*[0x08]*/ eString message;
            /*[0x0C]*/ eCameraZonePacket* cameraPacket;
            /*[0x10]*/ int32_t unknown_10;
            /*[0x14]*/ uint8_t unknown_14;
            /*[0x15]*/ uint8_t unknown_15;
            /*[0x18]*/ eString actorName;

        /*** Methods ***/

            eActionBase();
            ~eActionBase();

            eActionBase& operator = (const eActionBase &otherAction);

            void serializeAction(Archive &ar);
    };


    ////////////////////////////////////////////////////////////////
    // eActionTable interface
    ////////////////////////////////////////////////////////////////

    class eActionTable : public eRefCounter
    {

        /*** Properties ***/

        protected:

            /*[0x08]*/ int32_t actionsCount;
            /*[0x0C]*/ int32_t actionsMaxLength;
            /*[0x10]*/ eActionBase* actions;

        /*** Methods ***/

        public:

            eActionTable();
            ~eActionTable();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            void deleteIthAction(int32_t i);
            void findAndDeleteActionsWithNode(const eNode* target);
    };


    ////////////////////////////////////////////////////////////////
    // eActionTable TypeInfo
    // <kao2.004AF970> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_ACTIONTABLE_ID = 0xFC00;

    extern TypeInfo E_ACTIONTABLE_TYPEINFO;

}

#endif
