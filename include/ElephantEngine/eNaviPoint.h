#ifndef H_KAO2AR_NAVIPOINT
#define H_KAO2AR_NAVIPOINT

#include <ElephantEngine/eTransform.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eNaviPoint interface
    // <kao2.005D0358> (vptr)
    ////////////////////////////////////////////////////////////////

    class eNaviPoint : public eTransform
    {
        /*** Methods ***/

        public:

            eNaviPoint();
            ~eNaviPoint();

        private:

            void createFromOtherObject(const eNaviPoint &other);

        public:

            eNaviPoint(const eNaviPoint &other);
            eNaviPoint& operator = (const eNaviPoint &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eNaviPoint TypeInfo
    // <kao2.00429CC0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_NAVIPOINT_ID = 0xFACEFACE;

    extern TypeInfo E_NAVIPOINT_TYPEINFO;

}

#endif
