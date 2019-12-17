#ifndef H_KAO2_AXISLIST
#define H_KAO2_AXISLIST

#include <kao2ar/kao2ar.h>

namespace ZookieWizard
{
    class eALBox;

    ////////////////////////////////////////////////////////////////
    // 
    ////////////////////////////////////////////////////////////////

    struct AxisList
    {
        /*** Properties ***/

            /*[0x00]*/ AxisList* previous;
            /*[0x04]*/ AxisList* next;
            /*[0x08]*/ void* unknown_08;
            /*[0x0C]*/ int16_t unknown_0C;
            /*[0x0E]*/ bool unknown_0E;
            /*[0x0F]*/ int8_t unknown_0F;

            int32_t unknown_00_id;
            int32_t unknown_04_id;

        /*** Methods ***/

            AxisList();
            ~AxisList();

            void serialize(Archive &ar);
            void serializePointer(Archive &ar);

            void setPointersFromCollisionManager_A(eALBox** group, AxisList* arg2, AxisList* arg3);
            AxisList* getPointerFromCollisionManager_B(eALBox** group, AxisList* arg2, AxisList* arg3, int32_t arg4);
            void function_004BCF30(AxisList arg1[2]);
            void function_004BADA0(AxisList* arg1);
    };

    namespace ArFunctions
    {
        void generate_AxisList_pointers(AxisList** pointer, int32_t arg2, int32_t arg3);
        void destroy_AxisList_pointers(AxisList** pointer, int32_t arg2, int32_t arg3);
    }

}

#endif
