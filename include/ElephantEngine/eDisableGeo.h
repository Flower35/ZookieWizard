#ifndef H_KAO2AR_DISABLEGEO
#define H_KAO2AR_DISABLEGEO

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eDisableGeo interface
    // <kao2.005CEBA0> (vptr)
    ////////////////////////////////////////////////////////////////

    class eDisableGeo : public Gadget
    {
        /*** Methods ***/

        public:

            eDisableGeo();
            ~eDisableGeo();

        private:

            void createFromOtherObject(const eDisableGeo &other);

        public:

            eDisableGeo(const eDisableGeo &other);
            eDisableGeo& operator = (const eDisableGeo &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eDisableGeo TypeInfo
    // <kao2.004334D0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_DISABLEGEO_ID = 0x3AC241BB;

    extern TypeInfo E_DISABLEGEO_TYPEINFO;

}

#endif
