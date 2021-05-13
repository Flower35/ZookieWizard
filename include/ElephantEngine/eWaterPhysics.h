#ifndef H_KAO2AR_WATERPHYSICS
#define H_KAO2AR_WATERPHYSICS

#include <ElephantEngine/ePhysics.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eWaterPhysics interface
    // <kao2.005D3EF0> (vptr)
    ////////////////////////////////////////////////////////////////

    class eWaterPhysics : public ePhysics
    {
        /*** Properties ***/

        protected:

            /*(...)*/
            /*[0x1218]*/

        /*** Methods ***/

        public:

            eWaterPhysics();
            ~eWaterPhysics();

        private:

            void createFromOtherObject(const eWaterPhysics &other);

        public:

            eWaterPhysics(const eWaterPhysics &other);
            eWaterPhysics& operator = (const eWaterPhysics &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eWaterPhysics TypeInfo
    // <kao2.004F6930> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_WATERPHYSICS_ID = 0x0002DF20;

    extern TypeInfo E_WATERPHYSICS_TYPEINFO;

}

#endif
