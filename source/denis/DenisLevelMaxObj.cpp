#include <denis/DenisLevelMaxObj.h>

#include <denis/DenisLevelWObj.h>

#include <kao2engine/eProxy.h>

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


    ////////////////////////////////////////////////////////////////
    // World Object Proxy: convert from Kao1 to Kao2
    ////////////////////////////////////////////////////////////////

    void DenisLevelMaxObj::convertToKao2(int32_t maxobj_id, eGroup* parent_group, DenisLevelWObj &wobj) const
    {
        char bufor[16];
        eString test_str;

        eProxy* test_proxy;
        eSRP srp;

        float test_angles[3];

        /********************************/
        /* Create proxy */

        test_proxy = new eProxy();
        test_proxy->incRef();

        test_proxy->setCategory(5);

        test_str = wobj.name;
        test_str += ".ar";
        test_proxy->setTargetName(test_str);

        sprintf_s(bufor, 16, "GeoProxy%02d", maxobj_id);
        test_proxy->setName(bufor);

        /********************************/
        /* "eNode" flags: visibility + (0x00010000) model already loaded */

        test_proxy->setFlags(0x30010009);

        /********************************/
        /* Create "eTriMesh" with prepared colors */

        wobj.mesh.convertToKao2(test_proxy, vertexColors);

        /********************************/
        /* Apply Rotation, Scale and Translation */
        /* (level map was rotated and inverted!) */
        /* Left-handed to Right-handed coords: [X][Y][Z] -> [X][Z][Y] */

        srp.pos.x = position.x;
        srp.pos.y = position.z;
        srp.pos.z = position.y;

        /* [X][Y][Z] rotation order */

        rotation.toEulerAngles
        (
            false,
            test_angles[0],
            test_angles[1],
            test_angles[2]
        );

        /* Left-handed to Right-handed angles: [X][Y][Z] -> [X][Z][Y] */
        /* For some reason, Quaternions in Kao2 work only when I reverse [i][j][k] */
        /* So either use inverse Quaternions [^(-1)] or transposed rotation matrix */

        srp.rot.fromEulerAngles
        (
            true,
            test_angles[0],
            test_angles[2],
            test_angles[1]
        );

        srp.scale = scale;

        test_proxy->setXForm(srp);

        /********************************/
        /* Append this object */

        if (nullptr != parent_group)
        {
            parent_group->appendChild(test_proxy);
        }

        test_proxy->decRef();
    }

}
