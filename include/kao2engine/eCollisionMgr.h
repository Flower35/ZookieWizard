#ifndef H_KAO2AR_COLLISIONMGR
#define H_KAO2AR_COLLISIONMGR

#include <kao2ar/eObject.h>

#include <kao2engine/eALBox.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCollisionMgr interface
    // <kao2.005D1688> (vptr)
    ////////////////////////////////////////////////////////////////

    class eCollisionMgr : public eObject
    {
        /*** Properties ***/

        protected:

            /*[0x04]*/ int32_t seriesA_Count;
            /*[0x08]*/ int32_t seriesA_MaxLength;
            /*[0x0C]*/ int32_t* seriesA;

            /*[0x10]*/ int32_t unknown_10;

            /*[0x14]*/ AxisList* unknown_14;
            /*[0x18]*/ AxisList* unknown_18;
            /*[0x1C]*/ AxisList* unknown_1C;
            /*[0x20]*/ AxisList* unknown_20;
            /*[0x24]*/ AxisList* unknown_24;
            /*[0x28]*/ AxisList* unknown_28;

            /*[0x2C]*/ int32_t seriesB_Count;
            /*[0x30]*/ int32_t seriesB_MaxLength;
            /*[0x34]*/ eALBox** seriesB;

            bool debug_AlreadyDestroyed;


        /*** Methods ***/

        public:

            eCollisionMgr();
            ~eCollisionMgr();

        private:

            void createFromOtherObject(const eCollisionMgr &other);

        public:

            eCollisionMgr(const eCollisionMgr &other);
            eCollisionMgr& operator = (const eCollisionMgr &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            /* << eCollisionMgr >> */

            void prepare_ALBox_links();
            int32_t function_004993D0(int8_t arg1);
            void function_00499390(AxisList arg1[3][2]);
            void function_004994E0(int32_t offset);

            void save_ALBox(int32_t offset, eALBox* pointer);
            int32_t get_ALBoxes_array_size() const;
            eALBox** get_ALBoxes_array() const;

            void insertNewItem_seriesA(int32_t item);
            void insertNewItem_seriesB(eALBox* item);

            void reset();

        private:

            /* << eCollisionMgr >> */

            void clearNewCollisionMgr();
    };


    ////////////////////////////////////////////////////////////////
    // eCollisionMgr TypeInfo
    // <kao2.0049A030> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_COLLISIONMGR_ID = 0x0C700000;

    extern TypeInfo E_COLLISIONMGR_TYPEINFO;

}

#endif
