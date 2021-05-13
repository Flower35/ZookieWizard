#include <denis/DenisDisplayCommands.h>

#include <ElephantEngine/eGroup.h>
#include <ElephantEngine/eMaterial.h>
#include <ElephantEngine/eLeafCtrl.h>
#include <ElephantEngine/eTriMesh.h>
#include <ElephantEngine/eGeoSet.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Display Commands
    ////////////////////////////////////////////////////////////////

    DenisDisplayCommands::DenisDisplayCommands()
    {
        for (int i = 0; i < 2; i++)
        {
            bytesCount[i] = 0;
            texturesCount[i] = 0;
            unknownCount[i] = 0;
        }

        texturesCountTotal = 0;
        textures = nullptr;

        bytesCountTotal = 0;
        stream = nullptr;
        streamPointer = 0;
    }

    DenisDisplayCommands::~DenisDisplayCommands()
    {
        if (nullptr != stream)
        {
            delete[](stream);
        }

        if (nullptr != textures)
        {
            delete[](textures);
        }
    }

    void DenisDisplayCommands::serialize(DenisFileOperator &file)
    {
        int32_t i;

        for (i = 0; i < 2; i++)
        {
            file.readOrWrite(&(bytesCount[i]), 0x04);
            file.readOrWrite(&(texturesCount[i]), 0x04);
            file.readOrWrite(&(unknownCount[i]), 0x04);
        }

        if (file.isInReadMode())
        {
            bytesCountTotal = bytesCount[0] + bytesCount[1];
            texturesCountTotal = texturesCount[0] + texturesCount[1];

            if (nullptr != stream)
            {
                delete[](stream);
            }

            stream = new uint8_t [bytesCountTotal];
        }

        file.readOrWrite(stream, bytesCountTotal);

        if (file.isInReadMode())
        {
            /* Begin converting bytes-stream to display-structures */

            if (nullptr != textures)
            {
                delete[](textures);
            }

            textures = new DenisDisplayTexture [texturesCountTotal];

            for (i = 0; i < texturesCountTotal; i++)
            {
                textures[i].deserialize(*this);
            }
        }
    }

    void DenisDisplayCommands::read(void* ptr, int size)
    {
        if ((streamPointer + size) > bytesCountTotal)
        {
            throw ErrorMessage
            (
                "DenisDisplayCommands::read():\n" \
                "not enough bytes in stream! (THIS SHOULD NEVER HAPPEN)"
            );
        }

        std::memcpy(ptr, (stream + streamPointer), size);

        streamPointer += size;
    }


    ////////////////////////////////////////////////////////////////
    // Display Vertex
    ////////////////////////////////////////////////////////////////

    DenisDisplayVertex::DenisDisplayVertex()
    {
        index = 0;

        u = 0;
        v = 0;
    }

    void DenisDisplayVertex::deserialize(DenisDisplayCommands &cmd)
    {
        cmd.read(&index, 0x02);

        cmd.read(&u, 0x02);
        cmd.read(&v, 0x02);
    }


    ////////////////////////////////////////////////////////////////
    // Display Face
    ////////////////////////////////////////////////////////////////

    DenisDisplayFace::DenisDisplayFace()
    {
        verticesCount = 0;
        dummy = 0xFF;
        vertices = nullptr;
    }

    DenisDisplayFace::~DenisDisplayFace()
    {
        if (nullptr != vertices)
        {
            delete[](vertices);
        }
    }

    void DenisDisplayFace::deserialize(DenisDisplayCommands &cmd)
    {
        uint8_t i;

        cmd.read(&verticesCount, 0x01);

        cmd.read(&dummy, 0x01);

        vertices = new DenisDisplayVertex [verticesCount];

        for (i = 0; i < verticesCount; i++)
        {
            vertices[i].deserialize(cmd);
        }
    }


    ////////////////////////////////////////////////////////////////
    // Display Texture
    ////////////////////////////////////////////////////////////////

    DenisDisplayTexture::DenisDisplayTexture()
    {
        index = 0;
        facesCount = 0;
        transparency = 0;
        faces = nullptr;
    }

    DenisDisplayTexture::~DenisDisplayTexture()
    {
        if (nullptr != faces)
        {
            delete[](faces);
        }
    }

    void DenisDisplayTexture::deserialize(DenisDisplayCommands &cmd)
    {
        uint16_t i;
        uint16_t dummy;

        cmd.read(&index, 0x02);
        cmd.read(&dummy, 0x02);

        facesCount = dummy / 8;
        transparency = dummy % 8;

        faces = new DenisDisplayFace [facesCount];

        for (i = 0; i < facesCount; i++)
        {
            faces[i].deserialize(cmd);
        }
    }


    ////////////////////////////////////////////////////////////////
    // Display Commands: convert from Kao1 to Kao2
    ////////////////////////////////////////////////////////////////

    void DenisDisplayCommands::convertToKao2
    (
        eGroup* parent_group,
        int32_t materials_count,
        eMaterial** materials_list,
        int32_t vertices_count,
        const DenisGeoVertex* vertices,
        const char* name
    ) const
    {
        int32_t i, j, k, l, m, total_indices, total_vertices;
        ushort v1, v2, v3;
        ePoint4 e1, e2;

        eString trimesh_name;
        ePoint3 boundaries[2];

        eLeafCtrl<float>* test_visctrl = nullptr;
        eTriMesh* test_trimesh = nullptr;
        eGeoSet* test_geoset = nullptr;

        eGeoArray<ePoint4>* test_vertices_array = nullptr;
        eGeoArray<ePoint4>* test_normals_array = nullptr;
        eGeoArray<ushort>* test_indices_offsets = nullptr;
        eGeoArray<ushort>* test_indices_array = nullptr;
        eGeoArray<ePoint2>* test_uv_array = nullptr;
        eGeoArray<ePoint4>* test_colors_array = nullptr;

        ePoint4* test_vertices_data = nullptr;
        ePoint4* test_normals_data = nullptr;
        ushort* test_indices_offsets_data = nullptr;
        ushort* test_indices_array_data = nullptr;
        ePoint2* text_uv_data = nullptr;
        ePoint4* test_colors_data = nullptr;

        /********************************/
        /* Create new "eTriMesh" for every texture ID */

        for (i = 0; i < texturesCountTotal; i++)
        {
            test_trimesh = new eTriMesh();
            test_trimesh->incRef();

            trimesh_name = name;
            trimesh_name += " / ";

            if ((textures[i].index >= 0) && (textures[i].index < materials_count))
            {
                j = 4 * textures[i].index;

                if (i >= texturesCount[0])
                {
                    /* Use material with "2-sided" flag enabled */
                    j += 2;
                }

                if ((textures[i].transparency > 0) && (textures[i].transparency < 8))
                {
                    /* Use material with "TM_BLEND" flag enabled */
                    j++;

                    /* Set Node's static opacity */

                    test_visctrl = new eLeafCtrl<float>;
                    test_visctrl->incRef();

                    test_visctrl->setDefaultValue((8 - textures[i].transparency) / 8.0f);

                    test_trimesh->setVisCtrl(test_visctrl);
                    test_visctrl->decRef();

                    /* ("DrawPass #2" + "???" + "Enabled" + "Visible") node flags */

                    test_trimesh->setFlags(0x20000089);
                }
                else
                {
                    /* ("DrawPass #1" + "???" + "Enabled" + "Visible") node flags */

                    test_trimesh->setFlags(0x10000089);
                }

                trimesh_name += materials_list[j]->getStringRepresentation();

                test_trimesh->setMaterial(materials_list[j]);
            }
            else
            {
                trimesh_name += "!invisibleface";

                test_trimesh->setFlags(0x00010000);
                test_trimesh->unsetFlags(0x01);
            }

            test_trimesh->setName(trimesh_name);

            test_geoset = new eGeoSet();
            test_geoset->incRef();
            test_trimesh->setGeoset(test_geoset);

            /********************************/
            /* Calculate total number of indices */
            /* Each copied vertex will be represented by one face index */

            total_vertices = 0;
            total_indices = 0;

            for (j = 0; j < textures[i].facesCount; j++)
            {
                total_indices += textures[i].faces[j].verticesCount;
                total_vertices += textures[i].faces[j].verticesCount;

                if (0 == (textures[i].faces[j].verticesCount % 2))
                {
                    total_indices++;
                }
            }

            /********************************/
            /* Set-up arrays */

            test_geoset->setTwoIntegers(0x0F, total_vertices);

            test_vertices_data = new ePoint4 [total_vertices];
            test_normals_data = new ePoint4 [total_vertices];
            test_indices_offsets_data = new ushort [textures[i].facesCount];
            test_indices_array_data = new ushort [total_indices];
            text_uv_data = new ePoint2 [total_vertices];
            test_colors_data = new ePoint4 [total_vertices];

            test_vertices_array = new eGeoArray<ePoint4>();
            test_normals_array = new eGeoArray<ePoint4>;
            test_indices_offsets = new eGeoArray<ushort>();
            test_indices_array = new eGeoArray<ushort>();
            test_uv_array = new eGeoArray<ePoint2>;
            test_colors_array = new eGeoArray<ePoint4>();

            test_vertices_array->setup(total_vertices, test_vertices_data);
            test_normals_array->setup(total_vertices, test_normals_data);
            test_indices_offsets->setup(textures[i].facesCount, test_indices_offsets_data);
            test_indices_array->setup(total_indices, test_indices_array_data);
            test_uv_array->setup(total_vertices, text_uv_data);
            test_colors_array->setup(total_vertices, test_colors_data);

            test_geoset->setVerticesArray(test_vertices_array);
            test_geoset->setNormalsArray(test_normals_array);
            test_geoset->setIndicesOffsets(test_indices_offsets);
            test_geoset->setIndicesArray(test_indices_array);
            test_geoset->setTextureCoordsArray(test_uv_array);
            test_geoset->setColorsArray(test_colors_array);

            /********************************/
            /* Fill arrays: vertices, indices, UV mapping, colors */

            total_vertices = 0;
            total_indices = 0;

            for (j = 0; j < textures[i].facesCount; j++)
            {
                /* Reversing "TRIANGLE_STRIP" */

                if (0 == (textures[i].faces[j].verticesCount % 2))
                {
                    /* Clone last index to the first place to create "degenerate triangle" */

                    m = total_vertices + textures[i].faces[j].verticesCount - 1;

                    test_indices_array_data[total_indices] = m;
                }

                for (k = 0; k < textures[i].faces[j].verticesCount; k++)
                {
                    /* Write indices in reverse! (l = resulting index, m = source index) */

                    l = total_indices + textures[i].faces[j].verticesCount - 1 - k;
                    m = total_vertices + k;

                    if (0 == (textures[i].faces[j].verticesCount % 2))
                    {
                        /* First index for EVEN number of indices is already set */

                        l++;
                    }

                    test_indices_array_data[l] = m;

                    text_uv_data[m].u = (textures[i].faces[j].vertices[k].u / 256.0f);
                    text_uv_data[m].v = (textures[i].faces[j].vertices[k].v / 256.0f);

                    /* Rotate scene 90 degrees, so now [Z] is upwards instead of [Y] */
                    /* Flip scene from left-handed to right-handed (no minus in [Y] or [Z]) */

                    l = textures[i].faces[j].vertices[k].index;

                    test_vertices_data[m].x = vertices[l].v.x;
                    test_vertices_data[m].y = vertices[l].v.z;
                    test_vertices_data[m].z = vertices[l].v.y;
                    test_vertices_data[m].w = 1.0f;

                    test_normals_data[m] = {0, 0, 0, 0};

                    test_colors_data[m].x = (vertices[l].c.color_red / 255.0f);
                    test_colors_data[m].y = (vertices[l].c.color_green / 255.0f);
                    test_colors_data[m].z = (vertices[l].c.color_blue / 255.0f);
                    test_colors_data[m].w = 1.0f;
                }

                test_indices_offsets_data[j] = textures[i].faces[j].verticesCount;

                total_vertices += textures[i].faces[j].verticesCount;
                total_indices += textures[i].faces[j].verticesCount;

                if (0 == (textures[i].faces[j].verticesCount % 2))
                {
                    test_indices_offsets_data[j]++;

                    total_indices++;
                }
            }

            /********************************/
            /* Update vertex normals */

            for (j = 0; j < textures[i].facesCount; j++)
            {
                m = 0;

                for (k = 0; k < (test_indices_offsets_data[j] - 2); k++)
                {
                    v1 = test_indices_array_data[m + k];
                    v2 = test_indices_array_data[m + (k % 2) + 1];
                    v3 = test_indices_array_data[m + 2 - (k % 2)];

                    e1 = test_vertices_data[v3] - test_vertices_data[v1];
                    e2 = test_vertices_data[v2] - test_vertices_data[v1];

                    e1 = crossProduct(e1, e2);
                    e1.normalize();

                    test_normals_data[v1] += e1;
                    test_normals_data[v1].normalize();

                    test_normals_data[v2] += e1;
                    test_normals_data[v2].normalize();

                    test_normals_data[v3] += e1;
                    test_normals_data[v3].normalize();
                }

                m += test_indices_offsets_data[j];
            }

            /********************************/
            /* Calculate boundary box */

            calculateBoundaryBox(boundaries[0], boundaries[1], total_vertices, test_vertices_data, 0, nullptr);

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

            test_geoset->decRef();
            test_trimesh->decRef();
        }
    }

}
