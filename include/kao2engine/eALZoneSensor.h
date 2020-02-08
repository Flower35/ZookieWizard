#ifndef H_KAO2AR_ALZONESENSOR
#define H_KAO2AR_ALZONESENSOR

#include <kao2engine/eALBox.h>

namespace ZookieWizard
{
    class eZone;

    ////////////////////////////////////////////////////////////////
    // eALZoneSensor interface
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

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eALZoneSensor TypeInfo
    // <kao2.0049D460> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_ALZONESENSOR_ID = 0xFE10;

    extern TypeInfo E_ALZONESENSOR_TYPEINFO;

}

#endif
