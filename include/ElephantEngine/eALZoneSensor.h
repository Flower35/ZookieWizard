#ifndef H_KAO2AR_ALZONESENSOR
#define H_KAO2AR_ALZONESENSOR

#include <ElephantEngine/eALBox.h>

namespace ZookieWizard
{
    class eZone;

    ////////////////////////////////////////////////////////////////
    // eALZoneSensor interface
    // <kao2.005D17B0> (vptr)
    ////////////////////////////////////////////////////////////////

    class eALZoneSensor : public eALBox
    {
        /*** Properties ***/

        protected:

            /*[0x90]*/ eString sensorName;

        /*** Methods ***/

        public:

            eALZoneSensor();
            eALZoneSensor(eZone* zone, float* boxBound);
            ~eALZoneSensor();

        private:

            void createFromOtherObject(const eALZoneSensor &other);

        public:

            eALZoneSensor(const eALZoneSensor &other);
            eALZoneSensor& operator = (const eALZoneSensor &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
            void serialize(Archive &ar) override;
    };


    ////////////////////////////////////////////////////////////////
    // eALZoneSensor TypeInfo
    // <kao2.0049D430> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_ALZONESENSOR_ID = 0xFE10;

    extern TypeInfo E_ALZONESENSOR_TYPEINFO;

}

#endif
