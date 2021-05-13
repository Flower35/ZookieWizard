#ifndef H_KAO2AR_GROUNDTEST
#define H_KAO2AR_GROUNDTEST

#include <ElephantEngine/eNode.h>

namespace ZookieWizard
{
    class eCylinderShape;

    ////////////////////////////////////////////////////////////////
    // eGroundTest interface
    // <kao2.005D2790> (vptr)
    ////////////////////////////////////////////////////////////////

    class eGroundTest : public eNode
    {
        /*** Properties ***/

        protected:

            /*[0x3C]*/ eCylinderShape* unknown_3C;

        /*** Methods ***/

        public:

            eGroundTest(eString s, float x, float y);
            ~eGroundTest();

        private:

            void createFromOtherObject(const eGroundTest &other);

        public:

            eGroundTest(const eGroundTest &other);
            eGroundTest& operator = (const eGroundTest &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;
    };


    ////////////////////////////////////////////////////////////////
    // eGroundTest TypeInfo
    // <kao2.004CDA60> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_GROUNDTEST_ID = 0x8888FFFF;

    extern TypeInfo E_GROUNDTEST_TYPEINFO;

}

#endif
