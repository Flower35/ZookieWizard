#ifndef H_KAO2AR_GROUNDTEST
#define H_KAO2AR_GROUNDTEST

#include <kao2engine/eNode.h>

namespace ZookieWizard
{
    class eCylinderShape;

    ////////////////////////////////////////////////////////////////
    // eGroundTest interface
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

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eGroundTest TypeInfo
    // <kao2.004CDA90> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_GROUNDTEST_ID = 0x8888FFFF;

    extern TypeInfo E_GROUNDTEST_TYPEINFO;

}

#endif
