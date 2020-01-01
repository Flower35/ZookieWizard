#include <denis/DenisAnimmesh.h>
#include <kao2ar/kao2ar.h>

#include <kao2engine/eGroup.h>
#include <kao2engine/eMaterial.h>
#include <kao2engine/eTexture.h>
#include <kao2engine/eBitmap.h>
#include <kao2engine/eTriMesh.h>
#include <kao2engine/eGeoSet.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Anim Mesh: Display Vertex
    ////////////////////////////////////////////////////////////////

    DenisAnimmeshDisplayVertex::DenisAnimmeshDisplayVertex()
    {
        index = 0;

        u = 0;
        v = 0;
    }

    void DenisAnimmeshDisplayVertex::serialize(DenisFileOperator &file)
    {
        file.readOrWrite(&index, 0x02);

        file.readOrWrite(&u, 0x01);
        file.readOrWrite(&v, 0x01);
    }


    ////////////////////////////////////////////////////////////////
    // Anim Mesh: Display Command
    ////////////////////////////////////////////////////////////////

    DenisAnimmeshDisplayCommand::DenisAnimmeshDisplayCommand()
    {
        indicesCount = 0;
        transparency = 0;
        triangleStrips = false;
        indices = nullptr;
    }

    DenisAnimmeshDisplayCommand::~DenisAnimmeshDisplayCommand()
    {
        if (nullptr != indices)
        {
            delete[](indices);
            indices = nullptr;
        }
    }

    void DenisAnimmeshDisplayCommand::serialize(DenisFileOperator &file)
    {
        uint8_t i;
        int8_t dummy;

        if (file.isInReadMode())
        {
            file.readOrWrite(&dummy, 0x01);

            if (dummy < 0)
            {
                indicesCount = (-dummy);
                triangleStrips = true;
            }
            else
            {
                indicesCount = dummy;
                triangleStrips = false;
            }
        }
        else
        {
            dummy = triangleStrips ? (-indicesCount) : indicesCount;

            file.readOrWrite(&dummy, 0x01);
        }

        file.readOrWrite(&transparency, 0x01);

        if (file.isInReadMode())
        {
            indices = new DenisAnimmeshDisplayVertex [indicesCount];
        }

        for (i = 0; i < indicesCount; i++)
        {
            indices[i].serialize(file);
        }
    }


    ////////////////////////////////////////////////////////////////
    // Anim Mesh: Generate Vertices for rendering
    ////////////////////////////////////////////////////////////////

    void DenisAnimmesh::generateVertices(int32_t anim_id, int32_t frame)
    {
        int32_t i, j, k;

        ePoint4 point;
        eMatrix4x4 matrix[2];
        float angles[3];

        DenisAnimmeshMotion* test_anim;
        DenisAnimmeshKeyframe* test_keyframe;
        DenisVertex* test_vertices;

        if ((anim_id < 0) || (anim_id >= motionsCount))
        {
            return;
        }

        test_anim = &(motions[anim_id]);

        if ((frame < 0) || (frame >= test_anim->keyframesCount))
        {
            frame = 0;
        }

        for (i = 0; i < objectsCount; i++)
        {
            if (objects[i].verticesCount > 0)
            {
                test_keyframe = &(keyframes[test_anim->firstKeyframeId + frame][i]);
                test_vertices = &(vertices[objects[i].firstVertexId]);

                /* angles are stored in [X][Y][Z] order */

                test_keyframe->rotation.toEulerAngles(true, angles[0], angles[1], angles[2]);

                /* [Z][Y][X] matrix multiplication order */

                matrix[0].identity();

                matrix[1].setRotationZ(angles[2]);
                matrix[0] = matrix[0] * matrix[1];

                matrix[1].setRotationY(angles[1]);
                matrix[0] = matrix[0] * matrix[1];

                matrix[1].setRotationX(angles[0]);
                matrix[0] = matrix[0] * matrix[1];

                j = test_keyframe->groupId;

                if ((j < 0) || (j >= objects[i].groupsCount))
                {
                    j = 0;
                }

                for (k = 0; k < objects[i].verticesCount; k++)
                {
                    point.x = objects[i].vertices[j][k].x;
                    point.y = objects[i].vertices[j][k].y;
                    point.z = objects[i].vertices[j][k].z;
                    point.w = 1.0f;

                    point = matrix[0] * point;

                    if (0x80 == test_keyframe->coordMode)
                    {
                        test_vertices[k].x = test_keyframe->translation.x - point.x;
                        test_vertices[k].y = test_keyframe->translation.y - point.y;
                        test_vertices[k].z = test_keyframe->translation.z - point.z;
                    }
                    else
                    {
                        test_vertices[k].x = point.x + test_keyframe->translation.x;
                        test_vertices[k].y = point.y + test_keyframe->translation.y;
                        test_vertices[k].z = point.z + test_keyframe->translation.z;
                    }
                }
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // Anim Mesh: load texture
    ////////////////////////////////////////////////////////////////

    void DenisAnimmesh::loadTexture(DenisFileOperator &file, int32_t filetype)
    {
        eTexture* test_texture = nullptr;
        eBitmap* test_bitmap = nullptr;

        eString bitmap_path;

        /********************************/
        /* Create bitmap, texture, then material */

        unloadTexture();

        switch (filetype)
        {
            case DENIS_ANIM_MESH_FILE_TYPE_OBJECT:
            {
                bitmap_path = "objects/";

                break;
            }

            case DENIS_ANIM_MESH_FILE_TYPE_ENEMY:
            {
                bitmap_path = "charact/";

                break;
            }

            default:
            {
                return;
            }
        }

        bitmap_path += modelName;
        bitmap_path += "/texture.bmp";

        test_bitmap = new eBitmap();
        test_bitmap->incRef();

        test_bitmap->setPath(bitmap_path);

        try
        {
            test_bitmap->loadFromFile(file.workingDirectory);
            test_bitmap->generateTexture();
        }
        catch (ErrorMessage &e)
        {
            e.display();
        }

        test_texture = new eTexture(test_bitmap);
        test_texture->incRef();

        test_bitmap->decRef();

        material = new eMaterial(test_texture);
        material->incRef();

        test_texture->decRef();

        material->setName("texture");
        
        /* (--dsp--) "2-sided" */
        material->setMaterialFlags(0x01);
    }


    ////////////////////////////////////////////////////////////////
    // Anim Mesh: unload texture
    ////////////////////////////////////////////////////////////////

    void DenisAnimmesh::unloadTexture()
    {
        if (nullptr != material)
        {
            material->decRef();
            material = nullptr;
        }
    }


    ////////////////////////////////////////////////////////////////
    // Anim Mesh: convert from Kao1 to Kao2
    ////////////////////////////////////////////////////////////////

    void DenisAnimmesh::convertToKao2(eGroup* parent_group, DenisColor* maxobj_colors)
    {
        int32_t j, k, l, m, total_indices, total_vertices, total_offsets;
        eString trimesh_name;
        ePoint3 boundaries[2];

        eTriMesh* test_trimesh = nullptr;
        eGeoSet* test_geoset = nullptr;

        eGeoArray<ePoint4>* test_vertices_array = nullptr;
        eGeoArray<ushort>* test_indices_offsets = nullptr;
        eGeoArray<ushort>* test_indices_array = nullptr;
        eGeoArray<ePoint2>* test_uv_array = nullptr;
        eGeoArray<ePoint4>* test_colors_array = nullptr;

        ePoint4* test_vertices_data = nullptr;
        ushort* test_indices_offsets_data = nullptr;
        ushort* test_indices_array_data = nullptr;
        ePoint2* text_uv_data = nullptr;
        ePoint4* test_colors_data = nullptr;

        /********************************/
        /* Calculate vertices positions for the first keyframe */

        generateVertices(0, 0);

        /********************************/
        /* Create "eTriMesh" and "eGeoSet" objects */

        test_trimesh = new eTriMesh();

        trimesh_name = modelName;
        trimesh_name += " / ";
        trimesh_name += material->getStringRepresentation();

        test_trimesh->setMaterial(material);
        test_trimesh->setName(trimesh_name);

        test_geoset = new eGeoSet();
        test_trimesh->setGeoSet(test_geoset);

        /* Trying out different "eNode" flags combinations */
        test_trimesh->setFlags(0x70000009); // 0x10000009

        /********************************/
        /* Calculate total number of indices */

        total_vertices = 0;
        total_indices = 0;
        total_offsets = 0;

        for (j = 0; j < commandsCount[3]; j++)
        {
            total_vertices += commands[j].indicesCount;

            if (commands[j].triangleStrips)
            {
                total_indices += commands[j].indicesCount;

                total_offsets++;
            }
            else
            {
                /* Series of "TRIANGLE_FAN" indices will be converted to separate triangles */

                if (commands[j].indicesCount >= 3)
                {
                    total_indices += ((commands[j].indicesCount - 2) * 3);

                    total_offsets += (commands[j].indicesCount - 2);
                }
            }
        }
        
        /********************************/
        /* Set-up arrays */

        test_geoset->setTwoIntegers(0x0F, total_vertices);

        test_vertices_data = new ePoint4 [total_vertices];
        test_indices_offsets_data = new ushort [total_offsets];
        test_indices_array_data = new ushort [total_indices];
        text_uv_data = new ePoint2 [total_vertices];
        test_colors_data = new ePoint4 [total_vertices];

        test_vertices_array = new eGeoArray<ePoint4>();
        test_indices_offsets = new eGeoArray<ushort>();
        test_indices_array = new eGeoArray<ushort>();
        test_uv_array = new eGeoArray<ePoint2>;
        test_colors_array = new eGeoArray<ePoint4>();

        test_vertices_array->setup(total_vertices, test_vertices_data);
        test_indices_offsets->setup(total_offsets, test_indices_offsets_data);
        test_indices_array->setup(total_indices, test_indices_array_data);
        test_uv_array->setup(total_vertices, text_uv_data);
        test_colors_array->setup(total_vertices, test_colors_data);

        test_geoset->setVerticesArray(test_vertices_array);
        test_geoset->setIndicesOffsets(test_indices_offsets);
        test_geoset->setIndicesArray(test_indices_array);
        test_geoset->setTextureCoordsArray(test_uv_array);
        test_geoset->setColorsArray(test_colors_array);

        /********************************/
        /* Fill arrays: vertices, indices, UV mapping, colors */

        /* [x:X][y:Z][z:Y] -- Kao1 flips last two coordinates */
        /* [x:X][y:Z][z:-Y] -- flip from left-handed to right-handed */
        /* [x:X][y:Y][z:Z] -- rotation arount X-axis (Y-up to Z-up) */

        total_vertices = 0;
        total_indices = 0;
        total_offsets = 0;

        for (j = 0; j < commandsCount[3]; j++)
        {
            if (commands[j].triangleStrips)
            {
                /* "TRIANGLE_STRIP" */

                for (k = 0; k < commands[j].indicesCount; k++)
                {
                    l = total_indices + k;
                    m = total_vertices + k;

                    test_indices_array_data[l] = m;

                    /* "TRIANGLE_STRIP" - copying vertices */

                    text_uv_data[m].u = (commands[j].indices[k].u / 256.0f);
                    text_uv_data[m].v = (commands[j].indices[k].v / 256.0f);

                    l = commands[j].indices[k].index;

                    test_vertices_data[m].x = vertices[l].x;
                    test_vertices_data[m].y = vertices[l].y;
                    test_vertices_data[m].z = vertices[l].z;
                    test_vertices_data[m].w = 1.0f;

                    test_colors_data[m].x = (maxobj_colors[l].color_red / 255.0f);
                    test_colors_data[m].y = (maxobj_colors[l].color_green / 255.0f);
                    test_colors_data[m].z = (maxobj_colors[l].color_blue / 255.0f);
                    test_colors_data[m].w = (commands[j].transparency / 255.0f);
                }

                test_indices_offsets_data[total_offsets] = commands[j].indicesCount;
                total_offsets++;

                total_vertices += commands[j].indicesCount;
                total_indices += commands[j].indicesCount;
            }
            else
            {
                /* "TRIANGLE_FAN" - creating individual triangles */

                for (k = 0; k < (commands[j].indicesCount - 2); k++)
                {
                    test_indices_array_data[total_indices + 0] = total_vertices;
                    test_indices_array_data[total_indices + 1] = total_vertices + k + 1;
                    test_indices_array_data[total_indices + 2] = total_vertices + k + 2;

                    total_indices += 3;

                    test_indices_offsets_data[total_offsets] = 3;
                    total_offsets++;
                }

                /* "TRIANGLE_FAN" - copying vertices */

                for (k = 0; k < commands[j].indicesCount; k++)
                {
                    m = total_vertices + k;
                    l = commands[j].indices[k].index;

                    text_uv_data[m].u = (commands[j].indices[k].u / 256.0f);
                    text_uv_data[m].v = (commands[j].indices[k].v / 256.0f);

                    test_vertices_data[m].x = vertices[l].x;
                    test_vertices_data[m].y = vertices[l].y;
                    test_vertices_data[m].z = vertices[l].z;
                    test_vertices_data[m].w = 1.0f;

                    test_colors_data[m].x = (maxobj_colors[l].color_red / 255.0f);
                    test_colors_data[m].y = (maxobj_colors[l].color_green / 255.0f);
                    test_colors_data[m].z = (maxobj_colors[l].color_blue / 255.0f);
                    test_colors_data[m].w = (commands[j].transparency / 255.0f);
                }

                total_vertices += commands[j].indicesCount;
            }
        }

        /********************************/
        /* Calculate boundary box */

        for (k = 0; k < 2; k++)
        {
            boundaries[k].x = test_vertices_data[0].x;
            boundaries[k].y = test_vertices_data[0].y;
            boundaries[k].z = test_vertices_data[0].z;
        }

        for (k = 1; k < total_vertices; k++)
        {
            if (test_vertices_data[k].x < boundaries[0].x)
            {
                boundaries[0].x = test_vertices_data[k].x;
            }

            if (test_vertices_data[k].y < boundaries[0].y)
            {
                boundaries[0].y = test_vertices_data[k].y;
            }

            if (test_vertices_data[k].z < boundaries[0].z)
            {
                boundaries[0].z = test_vertices_data[k].z;
            }

            if (test_vertices_data[k].x > boundaries[1].x)
            {
                boundaries[1].x = test_vertices_data[k].x;
            }

            if (test_vertices_data[k].y > boundaries[1].y)
            {
                boundaries[1].y = test_vertices_data[k].y;
            }

            if (test_vertices_data[k].z > boundaries[1].z)
            {
                boundaries[1].z = test_vertices_data[k].z;
            }
        }

        test_trimesh->setBoundaryBox(boundaries[0], boundaries[1]);

        /********************************/
        /* Update "eGroup" */

        if (nullptr != parent_group)
        {
            parent_group->appendChild(test_trimesh);
        }

        /********************************/
        /* View result in editor's window :) */

        test_geoset->prepareForDrawing();
    }

}
