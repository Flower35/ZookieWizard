#include <denis/DenisLevelWObj.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // World Object Reference: constructor
    ////////////////////////////////////////////////////////////////

    DenisLevelWObj::DenisLevelWObj()
    {
        std::memset(name, 0x00, 32);

        vertexCount = 0;
    }


    ////////////////////////////////////////////////////////////////
    // World Object Reference: destructor
    ////////////////////////////////////////////////////////////////

    DenisLevelWObj::~DenisLevelWObj() {}


    ////////////////////////////////////////////////////////////////
    // World Object Reference: serialization
    ////////////////////////////////////////////////////////////////

    void DenisLevelWObj::serialize(DenisFileOperator &file)
    {
        /* Object name */

        file.readOrWrite(name, 0x20);

        /* Vertices count */

        file.readOrWrite(&vertexCount, 0x04);
    }


    ////////////////////////////////////////////////////////////////
    // World Object Reference: convert from Kao1 to Kao2
    ////////////////////////////////////////////////////////////////

    void DenisLevelWObj::loadMesh(DenisFileOperator &file)
    {
        /* Load object to validate vertices count */

        mesh.openAndSerialize(file, DENIS_ANIM_MESH_FILE_TYPE_OBJECT, name);

        if (0 != mesh.totalVertices)
        {
            if (mesh.totalVertices != vertexCount)
            {
                throw ErrorMessage
                (
                    "WOBJ \"%s\": invalid vertex count!"
                );
            }
        }

        /* Load texture */

        mesh.loadTexture(file, DENIS_ANIM_MESH_FILE_TYPE_OBJECT);
    }

}
