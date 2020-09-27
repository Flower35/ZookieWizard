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

        public:

            /*[0x04]*/ eNode* nodeTarget;
            /*[0x08]*/ eString message;
            /*[0x0C]*/ eCameraZonePacket* cameraPacket;
            /*[0x10]*/ int32_t unknown_10;
            /*[0x14]*/ uint8_t unknown_14;
            /*[0x15]*/ uint8_t unknown_15;
            /*[0x18]*/ eString actorName;

        /*** Methods ***/

        public:

            eActionBase();
            ~eActionBase();

        private:

            void createFromOtherObject(const eActionBase &other);

        public:

            eActionBase(const eActionBase &other);
            eActionBase& operator = (const eActionBase &other);

            void serializeAction(Archive &ar);
    };


    ////////////////////////////////////////////////////////////////
    // eActionTable interface
    // <kao2.005D1860> (vptr)
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

        private:

            void createFromOtherObject(const eActionTable &other);

        public:

            eActionTable(const eActionTable &other);
            eActionTable& operator = (const eActionTable &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            void writeStructureToTextFile(FileOperator &file, int32_t indentation, bool group_written) const override;

            /* << eActionTable >> */

            int32_t getActionsCount() const;

            void deleteIthAction(int32_t i);
            void findAndDeleteActionsWithNode(const eNode* target);

            void clearActions();
            void addAction(eActionBase &new_action);
    };


    ////////////////////////////////////////////////////////////////
    // eActionTable TypeInfo
    // <kao2.004AF940> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_ACTIONTABLE_ID = 0xFC00;

    extern TypeInfo E_ACTIONTABLE_TYPEINFO;

}

#endif
