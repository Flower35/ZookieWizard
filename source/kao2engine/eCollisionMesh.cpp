#include <kao2engine/eCollisionMesh.h>
#include <kao2ar/Archive.h>

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

    TypeInfo* eCollisionMesh::getType()
    {
        return &E_COLLISIONMESH_TYPEINFO;
    }

    eCollisionMesh::eCollisionMesh()
    : eCollision()
    {}

    eCollisionMesh::~eCollisionMesh() {}

}
