#include <ElephantEngine/eGroundTest.h>
#include <ElephantBase/Archive.h>

#include <ElephantEngine/eCylinderShape.h>

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

    TypeInfo* eGroundTest::getType() const
    {
        return &E_GROUNDTEST_TYPEINFO;
    }

    eGroundTest::eGroundTest(eString s, float x, float y)
    : eNode()
    {
        unknown_3C = new eCylinderShape(x, y);
        unknown_3C->incRef();

        name = s;
    }

    eGroundTest::~eGroundTest()
    {}


    ////////////////////////////////////////////////////////////////
    // eGroundTest: cloning the object
    ////////////////////////////////////////////////////////////////

    void eGroundTest::createFromOtherObject(const eGroundTest &other)
    {
        unknown_3C = other.unknown_3C;
        if (nullptr != unknown_3C)
        {
            unknown_3C->incRef();
        }
    }

    eGroundTest::eGroundTest(const eGroundTest &other)
    : eNode(other)
    {
        createFromOtherObject(other);
    }

    eGroundTest& eGroundTest::operator = (const eGroundTest &other)
    {
        if ((&other) != this)
        {
            eNode::operator = (other);

            /****************/

            unknown_3C->decRef();

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eGroundTest::cloneFromMe() const
    {
        return new eGroundTest(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eGroundTest: serialization
    // <kao2.004CE700>
    ////////////////////////////////////////////////////////////////
    void eGroundTest::serialize(Archive &ar)
    {
        eNode::serialize(ar);

        /* [0x3C] unknown */

        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&unknown_3C, &E_CYLINDERSHAPE_TYPEINFO);
    }

}
