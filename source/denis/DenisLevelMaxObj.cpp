#include <denis/DenisLevelMaxObj.h>

#include <denis/DenisLevelWObj.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // World Object Proxy: constructor
    ////////////////////////////////////////////////////////////////

    DenisLevelMaxObj::DenisLevelMaxObj()
    {
        std::memset(name, 0x00, 32);
        index = 0;

        scale = 1.0f;

        dummy_A = 0;
        flags = 0;
        damage = 0;
        dummy_B = 0;
        dummy_C = 0;
        dummy_D = 0;

        vertexColors = nullptr;
    }


    ////////////////////////////////////////////////////////////////
    // World Object Proxy: destructor
    ////////////////////////////////////////////////////////////////

    DenisLevelMaxObj::~DenisLevelMaxObj()
    {
        if (nullptr != vertexColors)
        {
            delete[](vertexColors);
        }
    }


    ////////////////////////////////////////////////////////////////
    // World Object Proxy: serialization
    ////////////////////////////////////////////////////////////////

    void DenisLevelMaxObj::serialize(DenisFileOperator &file, DenisLevelWObj* wobj, int32_t wobj_count)
    {
        int32_t i;
        int32_t verticesCount;

        /* Proxy name */

        file.readOrWrite(name, 0x20);

        /* World Object ID (and get vertex count) */

        file.readOrWrite(&index, 0x04);

        if ((index < 0) || (index > wobj_count))
        {
            throw ErrorMessage
            (
                "Max mesh \"%s\": WOBJ index out of range!"
            );
        }

        verticesCount = wobj[index].vertexCount;

        /* Position, rotation, scale */

        position.serialize(file);

        file.readOrWrite(&scale, 0x04);

        rotation.serialize(file);

        /* Unknown values */

        file.readOrWrite(&dummy_A, 0x02);
        file.readOrWrite(&flags, 0x04);
        file.readOrWrite(&damage, 0x04);
        file.readOrWrite(&dummy_B, 0x04);
        file.readOrWrite(&dummy_C, 0x04);
        file.readOrWrite(&dummy_D, 0x04);

        /* Vertex colors */

        if (file.isInReadMode())
        {
            vertexColors = new DenisColor [verticesCount];
        }

        for (i = 0; i < verticesCount; i++)
        {
            vertexColors[i].serialize(file);
        }
    }

}
