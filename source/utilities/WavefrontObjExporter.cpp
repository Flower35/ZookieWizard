#include <utilities/WavefrontObjExporter.h>

#include <ElephantEngine/eTransform.h>
#include <ElephantEngine/eGroup.h>
#include <ElephantEngine/eTriMesh.h>
#include <ElephantEngine/eGeoSet.h>

#include <ElephantEngine/eMaterial.h>
#include <ElephantEngine/eMaterialState.h>
#include <ElephantEngine/eTexture.h>
#include <ElephantEngine/eBitmap.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // WavefrontObjExporter: constructor
    ////////////////////////////////////////////////////////////////
    WavefrontObjExporter::WavefrontObjExporter()
    {
        totalVertices = 0;
        totalNormals = 0;
        totalMappings = 0;

        materialsCount = 0;
        materialsMaxLength = 512;
        materials = new eMaterial* [materialsMaxLength];

        meshGroup = nullptr;
        meshTrimesh = nullptr;
    }


    ////////////////////////////////////////////////////////////////
    // WavefrontObjExporter: destructor
    ////////////////////////////////////////////////////////////////
    WavefrontObjExporter::~WavefrontObjExporter()
    {
        if (nullptr != materials)
        {
            delete[](materials);
        }

        myFiles[0].close();
        myFiles[1].close();
    }


    ////////////////////////////////////////////////////////////////
    // WavefrontObjExporter: open file and set working directory
    ////////////////////////////////////////////////////////////////
    bool WavefrontObjExporter::openObj(eString filename, eObject* target)
    {
        TypeInfo* test_typeinfo;
        char* text = filename.getText();

        if (nullptr == target)
        {
            throw ErrorMessage
            (
                "WavefrontObjExporter::openObj():\n" \
                "No object selected!"
            );

            return false;
        }

        test_typeinfo = target->getType();

        if (test_typeinfo->checkHierarchy(&E_GROUP_TYPEINFO))
        {
            meshGroup = (eGroup*)target;
        }
        else if ((&E_TRIMESH_TYPEINFO) == test_typeinfo)
        {
            meshTrimesh = (eTriMesh*)target;
        }
        else
        {
            throw ErrorMessage
            (
                "WavefrontObjExporter::openObj():\n" \
                "Selected object is not a \"eTriMesh\" nor \"eGroup\" type!"
            );

            return false;
        }

        if (!myFiles[0].open(text, (FILE_OPERATOR_MODE_BINARY)))
        {
            throw ErrorMessage
            (
                "WavefrontObjExporter::openObj():\n" \
                "Could not open file: \"%s\"",
                text
            );

            return false;
        }

        workingDirectory = filename.getPath();
        fileName = filename.getFilename(false);

        return true;
    }


    ////////////////////////////////////////////////////////////////
    // WavefrontObjExporter: open material library file
    ////////////////////////////////////////////////////////////////
    bool WavefrontObjExporter::openMtl()
    {
        eString name = workingDirectory + fileName + ".mtl";
        char* text = name.getText();

        if (!myFiles[1].open(text, (FILE_OPERATOR_MODE_BINARY)))
        {
            throw ErrorMessage
            (
                "WavefrontObjExporter::openMtl():\n" \
                "Could not open file: \"%s\"",
                text
            );

            return false;
        }

        return true;
    }


    ////////////////////////////////////////////////////////////////
    // WavefrontObjExporter: write new line
    ////////////////////////////////////////////////////////////////
    void WavefrontObjExporter::writeNewLine(int32_t which_file)
    {
        if ((which_file >= 0) && (which_file < 2))
        {
            myFiles[which_file] << "\n";
        }
    }


    ////////////////////////////////////////////////////////////////
    // WavefrontObjExporter: start exporting mesh
    ////////////////////////////////////////////////////////////////
    void WavefrontObjExporter::begin()
    {
        bool uses_mtl = false;

        eMatrix4x4 default_matrix;

        std::time_t current_time;
        std::tm time_info;
        char time_bufor[32];

        /********************************/
        /* Get current time and date */

        std::time(&current_time);
        localtime_s(&time_info, &current_time);

        std::strftime(time_bufor, 32, "%c", &time_info);

        /********************************/
        /* Write simple comment in header */

        myFiles[0] << "# " << (
            (nullptr != meshGroup) ? meshGroup->getStringRepresentation() : (
                (nullptr != meshTrimesh) ? meshTrimesh->getStringRepresentation() : ""
            )
        );
        writeNewLine(0);

        myFiles[0] << "# Exported with ZookieWizard at " << time_bufor;
        writeNewLine(0);
        writeNewLine(0);

        /********************************/
        /* Get material info */

        if (nullptr != meshGroup)
        {
            uses_mtl = writeMaterialInfoFromGroup(meshGroup, false);
        }
        else if (nullptr != meshTrimesh)
        {
            uses_mtl = writeMaterialInfo(meshTrimesh, false);
        }
        else
        {
            uses_mtl = false;
        }

        if (uses_mtl)
        {
            myFiles[1].close();

            myFiles[0] << "mtllib " << fileName << ".mtl";
            writeNewLine(0);
            writeNewLine(0);
        }

        /********************************/
        /* Vertices, texture mapping, triangles */

        if (nullptr != meshGroup)
        {
            writeModelDataFromGroup(meshGroup, default_matrix);
        }
        else if (nullptr != meshTrimesh)
        {
            writeModelData(meshTrimesh, default_matrix);
        }

        myFiles[0].close();
    }


    ////////////////////////////////////////////////////////////////
    // WavefrontObjExporter: write texturing info recursively
    ////////////////////////////////////////////////////////////////
    bool WavefrontObjExporter::writeMaterialInfoFromGroup(eGroup* current_group, bool file_opened)
    {
        int i;
        bool result = file_opened;
        eNode* child_node;
        TypeInfo* test_typeinfo;

        if (nullptr == current_group)
        {
            return result;
        }

        for (i = 0; i < current_group->getNodesCount(); i++)
        {
            child_node = (eNode*)current_group->getIthChild(i);

            test_typeinfo = child_node->getType();

            if (test_typeinfo->checkHierarchy(&E_GROUP_TYPEINFO))
            {
                result |= writeMaterialInfoFromGroup((eGroup*)child_node, result);
            }
            else if ((&E_TRIMESH_TYPEINFO) == test_typeinfo)
            {
                result |= writeMaterialInfo((eTriMesh*)child_node, result);
            }
        }

        return result;
    }


    ////////////////////////////////////////////////////////////////
    // WavefrontObjExporter: write texturing info
    ////////////////////////////////////////////////////////////////
    bool WavefrontObjExporter::writeMaterialInfo(eTriMesh* current_trimesh, bool file_opened)
    {
        int i;

        eMaterial* test_material;
        eMaterialState* test_mtl_state;

        eTexture* test_texture;
        eBitmap* test_bitmap;

        char bufor[128];
        float color[3];

        /* Check if model uses any material */

        if (nullptr == current_trimesh)
        {
            return false;
        }

        if (nullptr != (test_material = current_trimesh->getMaterial()))
        {
            if (false == file_opened)
            {
                if (false == openMtl())
                {
                    return false;
                }
            }

            /* Checking if material was already described and exported */

            for (i = 0; i < materialsCount; i++)
            {
                if (materials[i] == test_material)
                {
                    return true;
                }
            }

            if (materialsCount >= materialsMaxLength)
            {
                throw ErrorMessage
                (
                    "WavefrontObjExporter::writeMaterialInfo():\n" \
                    "too many materials! Please increase \"materialsMaxCount\"."
                );

                return false;
            }

            materials[materialsCount] = test_material;
            materialsCount++;

            sprintf_s(bufor, 128, "newmtl material_%d", materialsCount);
            writeNewLine(1);
            myFiles[1] << bufor;
            writeNewLine(1);

            test_mtl_state = test_material->getMaterialState();

            if (nullptr != test_mtl_state)
            {
                test_mtl_state->getAmbientColor(color);
                sprintf_s(bufor, 128, "Ka %f %f %f", color[0], color[1], color[2]);

                myFiles[1] << bufor;
                writeNewLine(1);

                test_mtl_state->getDiffuseColor(color);
                sprintf_s(bufor, 128, "Kd %f %f %f", color[0], color[1], color[2]);

                myFiles[1] << bufor;
                writeNewLine(1);

                test_mtl_state->getSpecularColor(color);
                sprintf_s(bufor, 128, "Ks %f %f %f", color[0], color[1], color[2]);

                myFiles[1] << bufor;
                writeNewLine(1);
            }

            test_texture = test_material->getIthTexture(0);

            if (nullptr != test_texture)
            {
                test_bitmap = test_texture->getBitmap();

                if (nullptr != test_bitmap)
                {
                    sprintf_s(bufor, 128, "map_Kd %s", test_bitmap->getPath().getText());

                    myFiles[1] << bufor;
                    writeNewLine(1);

                    /* Actually export the image to hard drive */
                    try
                    {
                        test_bitmap->exportImageFile(workingDirectory);
                    }
                    catch (ErrorMessage &err)
                    {
                        err.display();
                    }
                }
            }
        }

        return true;
    }


    ////////////////////////////////////////////////////////////////
    // WavefrontObjExporter: write model data recursively
    ////////////////////////////////////////////////////////////////
    void WavefrontObjExporter::writeModelDataFromGroup(eGroup* current_group, eMatrix4x4 &parent_matrix)
    {
        int i;
        eNode* child_node;
        TypeInfo* test_typeinfo;

        eTransform* dummy_xform;
        eMatrix4x4 current_matrix = parent_matrix;

        if (nullptr == current_group)
        {
            return;
        }

        if (current_group->getType()->checkHierarchy(&E_TRANSFORM_TYPEINFO))
        {
            dummy_xform = (eTransform*)current_group;

            current_matrix = current_matrix * dummy_xform->getXForm(false).getMatrix();
        }

        for (i = 0; i < current_group->getNodesCount(); i++)
        {
            child_node = (eNode*)current_group->getIthChild(i);

            test_typeinfo = child_node->getType();

            if (test_typeinfo->checkHierarchy(&E_GROUP_TYPEINFO))
            {
                writeModelDataFromGroup((eGroup*)child_node, current_matrix);
            }
            else if ((&E_TRIMESH_TYPEINFO) == test_typeinfo)
            {
                writeModelData((eTriMesh*)child_node, current_matrix);
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // WavefrontObjExporter: write model data
    ////////////////////////////////////////////////////////////////
    void WavefrontObjExporter::writeModelData(eTriMesh* current_trimesh, eMatrix4x4 &parent_matrix)
    {
        int32_t a, b, c;
        int32_t f[3];
        char bufor[128];

        int32_t total_indices = 0;
        int32_t array_length[3];
        ePoint4* array_data4[2] = {nullptr, nullptr};
        ePoint2* array_data2 = nullptr;

        eGeoArray<ePoint4>* vertices = nullptr;
        eGeoArray<ePoint4>* colors = nullptr;
        eGeoArray<ePoint4>* normals = nullptr;
        eGeoArray<ePoint2>* mapping = nullptr;
        eGeoArray<ushort>* indices_offsets = nullptr;
        eGeoArray<ushort>* indices = nullptr;

        eGeoSet* geo = nullptr;

        ePoint4 dummy_vertex;
        eMaterial* dummy_material;

        /********************************/
        /* Get GeoSet */

        if (nullptr == current_trimesh)
        {
            return;
        }

        geo = current_trimesh->getGeoset();

        if (nullptr != geo)
        {
            /********************************/
            /* Get required data */

            vertices = geo->getVerticesArray();
            colors = geo->getColorsArray();
            normals = geo->getNormalsArray();
            mapping = geo->getTextureCoordsArray();
            indices_offsets = geo->getIndicesOffsets();
            indices = geo->getIndicesArray();

            /********************************/
            /* Write vertices */
            /* (converting [X][Y][Z] to [X][Z][-Y]) */

            if (nullptr != vertices)
            {
                array_length[0] = vertices->getLength();
                array_data4[0] = vertices->getData();

                if (nullptr != colors)
                {
                    if (colors->getLength() == array_length[0])
                    {
                        array_data4[1] = colors->getData();
                    }
                }

                for (a = 0; a < array_length[0]; a++)
                {
                    dummy_vertex = parent_matrix * array_data4[0][a];

                    if (nullptr != array_data4[1])
                    {
                        sprintf_s
                        (
                            bufor, 128, "v %f %f %f %f %f %f",
                            dummy_vertex.x,
                            dummy_vertex.z,
                            (- dummy_vertex.y),
                            array_data4[1][a].x,
                            array_data4[1][a].y,
                            array_data4[1][a].z
                        );
                    }
                    else
                    {
                        sprintf_s
                        (
                            bufor, 128, "v %f %f %f",
                            dummy_vertex.x,
                            dummy_vertex.z,
                            (- dummy_vertex.y)
                        );
                    }

                    myFiles[0] << bufor;
                    writeNewLine(0);
                }

                writeNewLine(0);
            }
            else
            {
                array_length[0] = 0;
            }

            /********************************/
            /* Write vertex normals */

            if (nullptr != normals)
            {
                array_length[1] = normals->getLength();
                array_data4[0] = normals->getData();

                for (a = 0; a < array_length[1]; a++)
                {
                    sprintf_s
                    (
                        bufor, 128, "vn %f %f %f",
                        array_data4[0][a].x,
                        array_data4[0][a].z,
                        (- array_data4[0][a].y)
                    );

                    myFiles[0] << bufor;
                    writeNewLine(0);
                }

                writeNewLine(0);
            }
            else
            {
                array_length[1] = 0;
            }

            /********************************/
            /* Write UV mapping */

            if (nullptr != mapping)
            {
                array_length[2] = mapping->getLength();
                array_data2 = mapping->getData();

                for (a = 0; a < array_length[2]; a++)
                {
                    sprintf_s
                    (
                        bufor, 128, "vt %f %f",
                        array_data2[a].u,
                        (1.0f - array_data2[a].v)
                    );

                    myFiles[0] << bufor;
                    writeNewLine(0);
                }

                writeNewLine(0);
            }
            else
            {
                array_length[2] = 0;
            }

            /********************************/
            /* Write faces */

            /* Set OBJ group name as trimesh name */

            myFiles[0] << "o " << current_trimesh->getStringRepresentation();
            writeNewLine(0);

            /* Get material name */

            if (nullptr != (dummy_material = current_trimesh->getMaterial()))
            {
                c = 0;

                for (a = 0; (!c) && (a < materialsCount); a++)
                {
                    if (dummy_material == materials[a])
                    {
                        c = 1 + a;
                    }
                }

                if (c > 0)
                {
                    sprintf_s(bufor, 128, "usemtl material_%d", c);
                    myFiles[0] << bufor;
                    writeNewLine(0);
                }
            }

            /* Checking order of parameters */

            c = 0;

            if (nullptr != vertices)
            {
                c |= (0x01 << 0);
            }

            if (nullptr != mapping)
            {
                c |= (0x01 << 1);
            }

            if (nullptr != normals)
            {
                c |= (0x01 << 2);
            }

            /* Saving indices */

            if (nullptr != indices_offsets)
            {
                if (nullptr != indices)
                {
                    for (a = 0; a < indices_offsets->getLength(); a++)
                    {
                        for (b = 0; b < (indices_offsets->getData()[a] - 2); b++)
                        {
                            f[0] = indices->getData()[total_indices + b];

                            f[1] = indices->getData()[total_indices + b + 1 + (b % 2)];

                            f[2] = indices->getData()[total_indices + b + 2 - (b % 2)];

                            writeFace(c, f);
                        }

                        total_indices += indices_offsets->getData()[a];
                    }

                    writeNewLine(0);
                }
            }
            else if (nullptr != indices)
            {
                for (a = 0; a < indices->getLength() - 2; a += 3)
                {
                    f[0] = indices->getData()[a];
                    f[1] = indices->getData()[a + 1];
                    f[2] = indices->getData()[a + 2];

                    writeFace(c, f);
                }

                writeNewLine(0);
            }

        }

        /********************************/
        /* Update totals */

        totalVertices += array_length[0];
        totalNormals += array_length[1];
        totalMappings += array_length[2];
    }


    ////////////////////////////////////////////////////////////////
    // WavefrontObjExporter: write one face based on availabe params
    ////////////////////////////////////////////////////////////////
    void WavefrontObjExporter::writeFace(int32_t params, int32_t index[3])
    {
        char bufor[128];

        index[0]++;
        index[1]++;
        index[2]++;

        switch (params)
        {
            case 0x01: // only "v"
            {
                sprintf_s
                (
                    bufor, 128, "f %d %d %d",
                    index[0] + totalVertices,
                    index[1] + totalVertices,
                    index[2] + totalVertices
                );

                break;
            }

            case 0x03: // "v" + "vt"
            {
                sprintf_s
                (
                    bufor, 128, "f %d/%d %d/%d %d/%d",
                    index[0] + totalVertices, index[0] + totalMappings,
                    index[1] + totalVertices, index[1] + totalMappings,
                    index[2] + totalVertices, index[2] + totalMappings
                );

                break;
            }

            case 0x05: // "v" + "vn"
            {
                sprintf_s
                (
                    bufor, 128, "f %d//%d %d//%d %d//%d",
                    index[0] + totalVertices, index[0] + totalNormals,
                    index[1] + totalVertices, index[1] + totalNormals,
                    index[2] + totalVertices, index[2] + totalNormals
                );

                break;
            }

            case 0x07: // "v" + "vt" + "vn"
            {
                sprintf_s
                (
                    bufor, 128, "f %d/%d/%d %d/%d/%d %d/%d/%d",
                    index[0] + totalVertices, index[0] + totalMappings, index[0] + totalNormals,
                    index[1] + totalVertices, index[1] + totalMappings, index[1] + totalNormals,
                    index[2] + totalVertices, index[2] + totalMappings, index[2] + totalNormals
                );

                break;
            }

            default:
            {
                sprintf_s(bufor, 128, "");
            }
        }

        myFiles[0] << bufor;
        writeNewLine(0);
    }

}
