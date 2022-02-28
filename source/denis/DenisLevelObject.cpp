#include <denis/DenisLevelObject.h>
#include <denis/DenisLevelTrack.h>

#include <ElephantEngine/eGroup.h>
#include <ElephantEngine/eMaterial.h>
#include <ElephantEngine/eGeoArray.h>

#include <ElephantEngine/eTriMesh.h>
#include <ElephantEngine/eGeoSet.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Level Object: constructor
    ////////////////////////////////////////////////////////////////

    DenisLevelObject::DenisLevelObject()
    {
        std::memset(name, 0x00, 32);

        flags = 0x0F;
        dummy_04 = 0;

        vertexCount = 0;
        faces1sidedCount = 0;
        faces2sidedCount = 0;

        dummy_34 = (-1);
        dummy_38 = 0;
        dummy_3C = 0;

        vertices = nullptr;
        faces = nullptr;

        tracksCount = 0;
        tracks = nullptr;

        unknownWordsCount = 0;
        unknownWords = nullptr;
    }


    ////////////////////////////////////////////////////////////////
    // Level Object: destructor
    ////////////////////////////////////////////////////////////////

    DenisLevelObject::~DenisLevelObject()
    {
        if (nullptr != vertices)
        {
            delete[](vertices);
        }

        if (nullptr != faces)
        {
            delete[](faces);
        }

        if (nullptr != tracks)
        {
            delete[](tracks);
        }

        if (nullptr != unknownWords)
        {
            delete[](unknownWords);
        }
    }


    ////////////////////////////////////////////////////////////////
    // Level Object: serialization
    ////////////////////////////////////////////////////////////////

    void DenisLevelObject::serialize(DenisFileOperator &file, int32_t current_type)
    {
        int32_t i;

        /* Flags */

        file.readOrWrite(&flags, 0x04);

        /* Dummy (4 bytes) */

        file.readOrWrite(&dummy_04, 0x04);

        /* Number of vertices */

        file.readOrWrite(&vertexCount, 0x04);

        /* 1-sided faces and 2-sided faces */

        file.readOrWrite(&faces1sidedCount, 0x04);
        file.readOrWrite(&faces2sidedCount, 0x04);

        /* Object name */

        file.readOrWrite(name, 32);

        /* unknown values */

        file.readOrWrite(&dummy_34, 0x04);
        file.readOrWrite(&dummy_38, 0x04);
        file.readOrWrite(&dummy_3C, 0x04);

        /* Boundary box */

        boundBox.serialize(file);

        /* Vertices (position and color) */

        if (file.isInReadMode())
        {
            vertices = new DenisGeoVertex [vertexCount];
        }

        for (i = 0; i < vertexCount; i++)
        {
            vertices[i].serialize(file);
        }

        /* Collision faces */

        if (file.isInReadMode())
        {
            faces = new DenisGeoFace [faces1sidedCount + faces2sidedCount];
        }

        for (i = 0; i < (faces1sidedCount + faces2sidedCount); i++)
        {
            faces[i].serialize(file);
        }

        /* Tracks for moving objects */

        if (DENIS_LEVEL_OBJECT_TYPE_MOVING == current_type)
        {
            i = *(int32_t*)"KEYS";

            file.readOrWrite(&i, 0x04);

            if (file.isInReadMode())
            {
                if (*(int32_t*)"KEYS" != i)
                {
                    throw ErrorMessage
                    (
                        "level object \"%s\": invalid keys magic.",
                        name
                    );
                }
            }

            if (file.isInReadMode())
            {
                if (nullptr != tracks)
                {
                    delete[](tracks);
                    tracksCount = 0;
                }
            }

            file.readOrWrite(&tracksCount, 0x04);

            if (file.isInReadMode())
            {
                if (tracksCount <= 0)
                {
                    throw ErrorMessage
                    (
                        "level object \"%s\": no tracks...",
                        name
                    );
                }

                tracks = new DenisLevelTrack [tracksCount];
            }

            for (i = 0; i < tracksCount; i++)
            {
                tracks[i].serialize(file);
            }
        }

        /* Unknown WORDS (must be at least one) */

        file.readOrWrite(&unknownWordsCount, 0x04);

        if (file.isInReadMode())
        {
            unknownWords = new int16_t [unknownWordsCount];
        }

        file.readOrWrite(unknownWords, (0x02 * unknownWordsCount));

        /* Display commands */

        displayCommands.serialize(file);
    }


    ////////////////////////////////////////////////////////////////
    // Level Object: convert from Kao1 to Kao2
    ////////////////////////////////////////////////////////////////

    void DenisLevelObject::convertToKao2
    (
        int32_t object_type,
        int32_t object_id,
        eGroup* parent_group,
        int32_t materials_count,
        eMaterial** materials_list,
        eMaterial** collision_materials
    )
    {
        char bufor[32];
        eString group_name;
        eGroup* test_group = nullptr;

        /********************************/
        /* Make a group of meshes */

        sprintf_s(bufor, 32, "%d:%d:", object_type, object_id);

        group_name = bufor;
        group_name += name;

        test_group = new eGroup();
        test_group->incRef();

        test_group->setName(group_name);

        /* ("DrawPass #1 and #2" + "???" + "Enabled" + "Visible") node flags */

        test_group->setFlags(0x30000089);

        /********************************/
        /* Convert collision surfaces */

        convertCollisionToKao2(test_group, collision_materials);

        /********************************/
        /* Convert display commands */

        displayCommands.convertToKao2
        (
            test_group,
            materials_count,
            materials_list,
            vertexCount,
            vertices,
            name
        );

        /********************************/
        /* Append this object */

        if (nullptr != parent_group)
        {
            parent_group->appendChild(test_group);
        }

        test_group->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // Level Object: convert collision surfaces from Kao1 to Kao2
    ////////////////////////////////////////////////////////////////

    void DenisLevelObject::convertCollisionToKao2(eGroup* object_group, eMaterial** collision_materials) const
    {
        int32_t i, j, k, l, total_indices, total_vertices;
        ushort v1, v2, v3, v4;
        eString trimesh_name;
        ePoint3 boundaries[2];

        eTriMesh* test_trimesh = nullptr;
        eGeoSet* test_geoset = nullptr;

        eGeoArray<ePoint4>* test_vertices_array = nullptr;
        eGeoArray<ushort>* test_indices_array = nullptr;

        ePoint4* test_vertices_data = nullptr;
        ushort* test_indices_array_data = nullptr;

        uint8_t* which_face_to_use = nullptr;
        uint16_t* which_vertices_to_use = nullptr;
        uint8_t collision_types[16];

        /********************************/
        /* Structures for optimisation */

        which_face_to_use = new uint8_t [faces1sidedCount + faces2sidedCount];
        which_vertices_to_use = new uint16_t [vertexCount];

        collision_types[0x00] = 0; // "normal" -> "normal"
        collision_types[0x01] = 1; // "ice" -> "ice"
        collision_types[0x02] = 0; // ??? -> "normal"
        collision_types[0x03] = 0; // "vehicle" -> "normal"
        collision_types[0x04] = 0; // ??? -> "normal"
        collision_types[0x05] = 1; // "slide down" -> "ice"
        collision_types[0x06] = 2; // "giraffe water" -> "giraffe water"
        collision_types[0x07] = 0; // ??? -> "normal"
        collision_types[0x08] = 0; // ??? -> "normal"
        collision_types[0x09] = 3; // "hurt lava" -> "hurt lava"
        collision_types[0x0A] = 0; // ??? -> "normal"
        collision_types[0x0B] = 0; // ??? -> "normal"
        collision_types[0x0C] = 0; // ??? -> "normal"
        collision_types[0x0D] = 0; // ??? -> "normal"
        collision_types[0x0E] = 0; // ??? -> "normal"
        collision_types[0x0F] = 0; // ??? -> "normal"

        /********************************/
        /* Create new "eTriMesh" for every collision type (if exists) */

        for (i = 0; i < 4; i++)
        {
            total_vertices = 0;
            total_indices = 0;

            std::memset(which_face_to_use, 0, sizeof(uint8_t) * (faces1sidedCount + faces2sidedCount));
            std::memset(which_vertices_to_use, (-1), sizeof(uint16_t) * vertexCount);

            for (j = 0; j < (faces1sidedCount + faces2sidedCount); j++)
            {
                k = 0;

                if (i == collision_types[(faces[j].collisionType / 4) & 0x0F])
                {
                    k = 1 + ((faces[j].collisionType / 64) % 2);
                }

                if (0 != k)
                {
                    for (l = 0; l < (k + 2); l++)
                    {
                        if (0xFFFF == which_vertices_to_use[faces[j].index[l]])
                        {
                            which_vertices_to_use[faces[j].index[l]] = total_vertices;
                            total_vertices++;
                        }
                    }

                    total_indices += (3 * k);

                    which_face_to_use[j] = k;
                }
            }

            if (total_vertices > 0)
            {
                test_trimesh = new eTriMesh();
                test_trimesh->incRef();

                trimesh_name = name;
                trimesh_name += " / collision";
                test_trimesh->setName(trimesh_name);

                test_trimesh->setMaterial(collision_materials[i]);

                test_trimesh->setFlags(0x0001208C);
                test_trimesh->unsetFlags(0x01);

                test_geoset = new eGeoSet();
                test_geoset->incRef();
                test_trimesh->setGeoset(test_geoset);

                /********************************/
                /* Set-up arrays */

                test_geoset->setTwoIntegers(0x0F, total_vertices);

                test_vertices_data = new ePoint4 [total_vertices];
                test_vertices_array = new eGeoArray<ePoint4>();
                test_vertices_array->setup(total_vertices, test_vertices_data);
                test_geoset->setVerticesArray(0, test_vertices_array);

                test_indices_array_data = new ushort [total_indices];
                test_indices_array = new eGeoArray<ushort>();
                test_indices_array->setup(total_indices, test_indices_array_data);
                test_geoset->setIndicesArray(test_indices_array);

                test_geoset->setTextureCoordsArray(0, nullptr);

                /********************************/
                /* Fill vertices array and indices array, update normals */

                total_indices = 0;

                for (j = 0; j < vertexCount; j++)
                {
                    k = which_vertices_to_use[j];

                    if (0xFFFF != k)
                    {
                        test_vertices_data[k].x = vertices[j].v.x;
                        test_vertices_data[k].y = vertices[j].v.z;
                        test_vertices_data[k].z = vertices[j].v.y;
                        test_vertices_data[k].w = 1.0f;
                    }
                }

                for (j = 0; j < (faces1sidedCount + faces2sidedCount); j++)
                {
                    k = which_face_to_use[j];

                    if (1 == k)
                    {
                        v1 = which_vertices_to_use[faces[j].index[2]];
                        v2 = which_vertices_to_use[faces[j].index[1]];
                        v3 = which_vertices_to_use[faces[j].index[0]];

                        test_indices_array_data[total_indices + 0] = v1;
                        test_indices_array_data[total_indices + 1] = v2;
                        test_indices_array_data[total_indices + 2] = v3;

                        total_indices += 3;
                    }
                    else if (2 == k)
                    {
                        v1 = which_vertices_to_use[faces[j].index[2]];
                        v2 = which_vertices_to_use[faces[j].index[1]];
                        v3 = which_vertices_to_use[faces[j].index[0]];
                        v4 = which_vertices_to_use[faces[j].index[3]];

                        test_indices_array_data[total_indices + 0] = v1;
                        test_indices_array_data[total_indices + 1] = v2;
                        test_indices_array_data[total_indices + 2] = v3;
                        test_indices_array_data[total_indices + 3] = v1;
                        test_indices_array_data[total_indices + 4] = v3;
                        test_indices_array_data[total_indices + 5] = v4;

                        total_indices += 6;
                    }
                }

                /********************************/
                /* Calculate boundary box */

                calculateBoundaryBox(boundaries[0], boundaries[1], total_vertices, test_vertices_data, 0, nullptr);

                test_trimesh->setBoundaryBox(boundaries[0], boundaries[1]);

                /********************************/
                /* Update "eGroup" */

                if (nullptr != object_group)
                {
                    object_group->appendChild(test_trimesh);
                }

                /********************************/
                /* Create "eALBox" and try to create "AABB tree" */

                test_trimesh->createCollisionEntry();

                try
                {
                    test_geoset->buildAabbTree(trimesh_name);
                }
                catch (ErrorMessage &err)
                {
                    err.display();
                }

                /********************************/
                /* View result in editor's window :) */

                test_geoset->prepareForDrawing();

                test_geoset->decRef();
                test_trimesh->decRef();
            }
        }

        /********************************/
        /* Destroy helpers */

        if (nullptr != which_vertices_to_use)
        {
            delete[](which_vertices_to_use);
        }

        if (nullptr != which_face_to_use)
        {
            delete[](which_face_to_use);
        }
    }

}
