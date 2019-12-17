#include <kao2engine/eGroundTest.h>
#include <kao2ar/Archive.h>

#include <kao2engine/eCylinderShape.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eGroundTest interface
    // <kao2.004CDB30> (constructor)
    // <kao2.004CDE40> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_GROUNDTEST_TYPEINFO
    (
        E_GROUNDTEST_ID,
        "eGroundTest",
        &E_NODE_TYPEINFO,
        []() -> eObject*
        {
            return new eGroundTest("ground test", 10.0f, 10.0f);
        }
    );

    TypeInfo* eGroundTest::getType()
    {
        return &E_GROUNDTEST_TYPEINFO;
    }

    eGroundTest::eGroundTest(eString s, float x, float y)
    : eNode()
    {
        unknown_3C = new eCylinderShape;
        unknown_3C->incRef();

        name = s;
    }

    eGroundTest::~eGroundTest() {}


    ////////////////////////////////////////////////////////////////
    // eGroundTest serialization
    // <kao2.004CE700>
    ////////////////////////////////////////////////////////////////
    void eGroundTest::serialize(Archive &ar)
    {
        eNode::serialize(ar);

        /* [0x3C] unknown */

        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&unknown_3C, &E_CYLINDERSHAPE_TYPEINFO);
    }

}
