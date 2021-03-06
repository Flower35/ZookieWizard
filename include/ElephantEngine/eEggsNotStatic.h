#ifndef H_KAO2AR_EGGSNOTSTATIC
#define H_KAO2AR_EGGSNOTSTATIC

#include <ElephantEngine/eEggsFactory.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eEggsNotStatic interface
    // <kao2.005D4658> (vptr)
    ////////////////////////////////////////////////////////////////

    class eEggsNotStatic : public eEggsFactory
    {
        /*** Methods ***/

        public:

            eEggsNotStatic();
            ~eEggsNotStatic();

        private:

            void createFromOtherObject(const eEggsNotStatic &other);

        public:

            eEggsNotStatic(const eEggsNotStatic &other);
            eEggsNotStatic& operator = (const eEggsNotStatic &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eEggsNotStatic TypeInfo
    // <kao2.00506970> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_EGGSNOTSTATIC_ID = 0x3BF54C40;

    extern TypeInfo E_EGGSNOTSTATIC_TYPEINFO;

}

#endif
