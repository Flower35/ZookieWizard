#ifndef H_KAO2AR_AMBIENTLIGHT
#define H_KAO2AR_AMBIENTLIGHT

#include <ElephantEngine/eLight.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eAmbientLight interface
    // <kao2.005E10B8> (vptr)
    ////////////////////////////////////////////////////////////////

    class eAmbientLight : public eLight
    {
        /*** Methods ***/

        public:

            eAmbientLight();
            ~eAmbientLight();

        private:

            void createFromOtherObject(const eAmbientLight &other);

        public:

            eAmbientLight(const eAmbientLight &other);
            eAmbientLight& operator = (const eAmbientLight &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;

            /* << eLight >> */

            /*[[vptr]+0x74]*/ void bindLight(int32_t light_id) const override;
    };


    ////////////////////////////////////////////////////////////////
    // eAmbientLight TypeInfo
    // <kao2.005AE640> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_AMBIENTLIGHT_ID = 0x03454503;

    extern TypeInfo E_AMBIENTLIGHT_TYPEINFO;

}

#endif
