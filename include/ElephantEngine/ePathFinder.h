#ifndef H_KAO2AR_PATHFINDER
#define H_KAO2AR_PATHFINDER

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{
    class eGroundTest;
    class eNPCMap;

    ////////////////////////////////////////////////////////////////
    // ePathFinder interface
    // <kao2.005CE320> (vptr)
    ////////////////////////////////////////////////////////////////

    class ePathFinder : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/ int32_t points_Count;
            /*[0x14]*/ int32_t points_MaxLength;
            /*[0x18]*/ ePoint3* points;

            /*[0x1C]*/ eRefCounter* unknown_1C; // "eAStar"

            /*[0x20]*/ eNPCMap* map;

            /*[0x24]*/ uint8_t unknown_24;

            /*[0x28]*/ eGroundTest* unknown_28;

            /*[0x2C]*/ int32_t unknown_2C;
            /*[0x30]*/ int32_t unknown_30;
            /*[0x34]*/ int32_t unknown_34;
            /*[0x38]*/

        /*** Methods ***/

        public:

            ePathFinder();
            ~ePathFinder();

        private:

            void createFromOtherObject(const ePathFinder &other);

        public:

            ePathFinder(const ePathFinder &other);
            ePathFinder& operator = (const ePathFinder &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            /* << Gadget >> */

            eString getDefaultGadgetName() const override;
    };


    ////////////////////////////////////////////////////////////////
    // ePathFinder TypeInfo
    // <kao2.00427220> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_PATHFINDER_ID = 0xF0012020;

    extern TypeInfo E_PATHFINDER_TYPEINFO;

}

#endif
