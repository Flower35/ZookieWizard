#ifndef H_KAO2AR_SNOWBOARDPHYSICS
#define H_KAO2AR_SNOWBOARDPHYSICS

#include <ElephantEngine/eBasePhysics.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSnowboardPhysics interface
    // <kao2.005D3390> (vptr)
    ////////////////////////////////////////////////////////////////

    class eSnowboardPhysics : public eBasePhysics
    {
        /*** Properties ***/

        protected:

            /*(...)*/
            /*[0x07EC]*/

        /*** Methods ***/

        public:

            eSnowboardPhysics();
            ~eSnowboardPhysics();

        private:

            void createFromOtherObject(const eSnowboardPhysics &other);

        public:

            eSnowboardPhysics(const eSnowboardPhysics &other);
            eSnowboardPhysics& operator = (const eSnowboardPhysics &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eSnowboardPhysics TypeInfo
    // <kao2.004E3310> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SNOWBOARDPHYSICS_ID = 0x3B950C40;

    extern TypeInfo E_SNOWBOARDPHYSICS_TYPEINFO;

}

#endif
