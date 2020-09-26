#ifndef H_KAO2_AXISLIST
#define H_KAO2_AXISLIST

#include <kao2ar/kao2ar.h>

namespace ZookieWizard
{
    class eALBox;

    ////////////////////////////////////////////////////////////////
    // AXIS LIST STRUCTURE for "eALBox"
    ////////////////////////////////////////////////////////////////

    struct AxisList
    {
        /*** Properties ***/

        public:

            /*[0x00]*/ AxisList* previous;
            /*[0x04]*/ AxisList* next;
            /*[0x08]*/ float coordLimit;
            /*[0x0C]*/ int16_t alboxEntryId;
            /*[0x0E]*/ int8_t columnId;
            /*[0x0F]*/ int8_t rowId;

            int32_t tempPreviousId;
            int32_t tempNextId;

        /*** Methods ***/

        public:

            AxisList();
            ~AxisList();

        private:

            void createFromOtherObject(const AxisList &other);

        public:

            AxisList(const AxisList &other);
            AxisList& operator = (const AxisList &other);

            /* << AxisList >> */

            void serialize(Archive &ar);
            void serializePointer(Archive &ar) const;

            void setPointersFromCollisionManager_A(eALBox** group, AxisList* arg2, AxisList* arg3);
            AxisList* getPointerFromCollisionManager_B(eALBox** group, AxisList* arg2, AxisList* arg3, int32_t arg4) const;
            void function_004BCF30(AxisList arg1[2]) const;
            void function_004BADA0(AxisList* arg1) const;

        private:

            void clearNewAxisList();
    };

    namespace ArFunctions
    {
        void generate_AxisList_pointers(AxisList** pointer, int32_t arg2, int32_t arg3);
        void destroy_AxisList_pointers(AxisList** pointer, int32_t arg2, int32_t arg3);
    }

}

#endif
