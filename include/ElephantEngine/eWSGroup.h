#ifndef H_KAO2AR_WSGROUP
#define H_KAO2AR_WSGROUP

#include <ElephantEngine/eGroup.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eWSGroup interface
    // <kao2.005D1728> (vptr)
    ////////////////////////////////////////////////////////////////

    class eWSGroup : public eGroup
    {
        /*** Properties ***/

        protected:

            /*[0x48]*/ //// (???)
            /*[0x4C]*/ uint32_t unknown_4C;

        /*** Methods ***/

        public:

            eWSGroup();
            ~eWSGroup();

        private:

            void createFromOtherObject(const eWSGroup &other);

        public:

            eWSGroup(const eWSGroup &other);
            eWSGroup& operator = (const eWSGroup &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
            void serialize(Archive &ar) override;
    };


    ////////////////////////////////////////////////////////////////
    // eWSGroup TypeInfo
    // <kao2.0049AF90> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_WSGROUP_ID = 0x00000754;

    extern TypeInfo E_WSGROUP_TYPEINFO;

}

#endif
