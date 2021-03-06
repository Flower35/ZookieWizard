#include <ElephantEngine/eCollisionMesh.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCollisionMesh interface
    // <kao2.005996C0> (constructor)
    // <kao2.00599730> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_COLLISIONMESH_TYPEINFO
    (
        E_COLLISIONMESH_ID,
        "eCollisionMesh",
        &E_COLLISION_TYPEINFO,
        []() -> eObject*
        {
            return new eCollisionMesh;
        }
    );

    const TypeInfo* eCollisionMesh::getType() const
    {
        return &E_COLLISIONMESH_TYPEINFO;
    }

    eCollisionMesh::eCollisionMesh()
    : eCollision()
    {}

    eCollisionMesh::~eCollisionMesh()
    {}


    ////////////////////////////////////////////////////////////////
    // eCollisionMesh: cloning the object
    ////////////////////////////////////////////////////////////////

    void eCollisionMesh::createFromOtherObject(const eCollisionMesh &other)
    {}

    eCollisionMesh::eCollisionMesh(const eCollisionMesh &other)
    : eCollision(other)
    {
        createFromOtherObject(other);
    }

    eCollisionMesh& eCollisionMesh::operator = (const eCollisionMesh &other)
    {
        if ((&other) != this)
        {
            eCollision::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eCollisionMesh::cloneFromMe() const
    {
        return new eCollisionMesh(*this);
    }

}
