#ifndef H_KAO2AR_BOXZONE
#define H_KAO2AR_BOXZONE

#include <ElephantEngine/eZone.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eBoxZone interface
    // <kao2.005D1880> (vptr)
    ////////////////////////////////////////////////////////////////

    class eBoxZone : public eZone
    {
        /*** Methods ***/

        public:

            eBoxZone();
            ~eBoxZone();

        private:

            void createFromOtherObject(const eBoxZone &other);

        public:

            eBoxZone(const eBoxZone &other);
            eBoxZone& operator = (const eBoxZone &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            /* << eNode >> */

            void renderNode(eDrawContext &draw_context) const override;
    };


    ////////////////////////////////////////////////////////////////
    // eBoxZone TypeInfo
    // <kao2.0049E310> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_BOXZONE_ID = 0xFE02;

    extern TypeInfo E_BOXZONE_TYPEINFO;

}

#endif
