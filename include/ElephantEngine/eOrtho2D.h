#ifndef H_KAO2AR_ORTHO2D
#define H_KAO2AR_ORTHO2D

#include <ElephantEngine/eGroup.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eOrtho2D interface
    // <kao2.005CD9C0> (vptr)
    ////////////////////////////////////////////////////////////////

    class eOrtho2D : public eGroup
    {
        /*** Properties ***/

        protected:

            /*[0x48]*/ //// float screenWidth;
            /*[0x4C]*/ //// float screenHeight;

        /*** Methods ***/

        public:

            eOrtho2D();
            ~eOrtho2D();

        private:

            void createFromOtherObject(const eOrtho2D &other);

        public:

            eOrtho2D(const eOrtho2D &other);
            eOrtho2D& operator = (const eOrtho2D &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eOrtho2D TypeInfo
    // <kao2.00542970> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_ORTHO2D_ID = 0x0000AACC;

    extern TypeInfo E_ORTHO2D_TYPEINFO;

}

#endif
