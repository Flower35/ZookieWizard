#include <ElephantEngine/eOrtho2D.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eOrtho2D interface
    // <kao2.00542E71> (constructor)
    // <kao2.00409870> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_ORTHO2D_TYPEINFO
    (
        E_ORTHO2D_ID,
        "eOrtho2D",
        &E_GROUP_TYPEINFO,
        []() -> eObject*
        {
            return new eOrtho2D;
        }
    );

    const TypeInfo* eOrtho2D::getType() const
    {
        return &E_ORTHO2D_TYPEINFO;
    }

    eOrtho2D::eOrtho2D()
    : eGroup()
    {
        /* [Kao2] */
        //// screenWidth = 640.0f
        //// screenHeight = 448.0f

        /* [KaoTW] */
        //// screenWidth = 597.333333f;
        //// screenHeight = 448.0f;
    }

    eOrtho2D::~eOrtho2D()
    {}


    ////////////////////////////////////////////////////////////////
    // eOrtho2D: cloning the object
    ////////////////////////////////////////////////////////////////

    void eOrtho2D::createFromOtherObject(const eOrtho2D &other)
    {
        //// screenWidth = other.screenWidth;
        //// screenHeight = other.screenHeight;
    }

    eOrtho2D::eOrtho2D(const eOrtho2D &other)
    : eGroup(other)
    {
        createFromOtherObject(other);
    }

    eOrtho2D& eOrtho2D::operator = (const eOrtho2D &other)
    {
        if ((&other) != this)
        {
            eGroup::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eOrtho2D::cloneFromMe() const
    {
        return new eOrtho2D(*this);
    }

}
