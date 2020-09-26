#ifndef H_KAO2AR_SNOWBOARDORIENTATION
#define H_KAO2AR_SNOWBOARDORIENTATION

#include <kao2engine/eBasePhysics.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSnowboardOrientation interface
    // <kao2.005D3260> (vptr)
    ////////////////////////////////////////////////////////////////

    class eSnowboardOrientation : public eBasePhysics
    {
        /*** Properties ***/

        protected:

            /*(...)*/
            /*[0x0194]*/

        /*** Methods ***/

        public:

            eSnowboardOrientation();
            ~eSnowboardOrientation();

        private:

            void createFromOtherObject(const eSnowboardOrientation &other);

        public:

            eSnowboardOrientation(const eSnowboardOrientation &other);
            eSnowboardOrientation& operator = (const eSnowboardOrientation &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eSnowboardOrientation TypeInfo
    // <kao2.004E1110> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SNOWBOARDORIENTATION_ID = 0x3B950C41;

    extern TypeInfo E_SNOWBOARDORIENTATION_TYPEINFO;

}

#endif
