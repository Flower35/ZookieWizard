#ifndef H_KAO2AR_COLLISIONMESH
#define H_KAO2AR_COLLISIONMESH

#include <kao2engine/eCollision.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCollisionMesh interface
    ////////////////////////////////////////////////////////////////

    class eCollisionMesh : public eCollision
    {

        /*** Properties ***/

        protected:

            /*[0x18]*/
            /*[0x1C]*/
            /*[0x20]*/
            /*[0x24]*/
            /*[0x28]*/

        /*** Methods ***/

        public:

            eCollisionMesh();
            ~eCollisionMesh();

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eCollisionMesh TypeInfo
    // <kao2.00599630> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_COLLISIONMESH_ID = 0x0002FC03;

    extern TypeInfo E_COLLISIONMESH_TYPEINFO;

}

#endif
