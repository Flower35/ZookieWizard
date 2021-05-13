#ifndef H_KAO2AR_COLLISIONMESH
#define H_KAO2AR_COLLISIONMESH

#include <ElephantEngine/eCollision.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCollisionMesh interface
    // <kao2.005D8230>
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

        private:

            void createFromOtherObject(const eCollisionMesh &other);

        public:

            eCollisionMesh(const eCollisionMesh &other);
            eCollisionMesh& operator = (const eCollisionMesh &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eCollisionMesh TypeInfo
    // <kao2.00599600> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_COLLISIONMESH_ID = 0x0002FC03;

    extern TypeInfo E_COLLISIONMESH_TYPEINFO;

}

#endif
