#ifndef H_KAO2AR_ALBOX
#define H_KAO2AR_ALBOX

#include <kao2engine/eRefCounter.h>

#include <kao2ar/AxisList.h>

#include <kao2ar/Collection.h>

namespace ZookieWizard
{
    class eScene;
    class eNode;
    class eALBox;

    ////////////////////////////////////////////////////////////////
    // eALBox interface
    ////////////////////////////////////////////////////////////////

    class eALBox : public eRefCounter
    {
        /*** Properties ***/

        protected:

            /*[0x08]*/ eScene* myScene;
            /*[0x0C]*/ eNode* parentNode;

            /*[0x10-0x6F]*/ AxisList axis_list[3][2];

            /*[0x70]*/ int32_t seriesCount;
            /*[0x74]*/ int32_t seriesMaxLength;
            /*[0x78]*/ uint8_t* series;

            /*[0x7C]*/ int32_t collisionEntryId;

            /*[0x80-0x88]*/ Collection<ArFunctions::serialize_eRefCounter> unknown_80;

            /*[0x8C]*/ uint8_t unknown_8C;
            // 0x00 = "STATIC"
            // 0x01 = "INTERACTIVE"
            // 0x02 = "BULLET"
            // 0x03 = "ENTRY"

        /*** Methods ***/

        protected:

            bool function_004AAB60() const;
            void function_004A9CC0();
            void function_004A99C0();
            void function_004A9C80();
            void function_004A9870();
            uint8_t function_004A9830(eALBox* other) const;
            bool function_004AA540(eALBox* other) const;
            uint8_t function_004AA4F0(eALBox* other) const;
            void function_004A9FF0(eNode* arg1, int8_t arg2) const;

            /*[vptr]+0x24]*/ void function_004AA560(eALBox* other);
            /*[vptr]+0x28]*/ void function_004AA750(eALBox* other);

        public:

            eALBox();
            ~eALBox();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            int32_t getCollisionId() const;
            AxisList* getAxisList(int32_t row, int32_t column) const;
            uint8_t* getSeriesPointer() const;

            void createAxisListEntry(eNode* parent, float* boxBound);

            void function_004A9F40(eALBox* other, uint8_t row_id);
    };


    ////////////////////////////////////////////////////////////////
    // eALBox TypeInfo
    // <kao2.004AAD80> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_ALBOX_ID = 0x01231325;

    extern TypeInfo E_ALBOX_TYPEINFO;

}

#endif
