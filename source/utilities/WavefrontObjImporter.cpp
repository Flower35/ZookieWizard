#include <utilities/WavefrontObjImporter.h>

#include <kao2engine/eGroup.h>
#include <kao2engine/eTriMesh.h>
#include <kao2engine/eGeoSet.h>

#include <kao2engine/eMaterial.h>
#include <kao2engine/eMaterialState.h>
#include <kao2engine/eTexture.h>
#include <kao2engine/eBitmap.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // WavefrontObjImporter structures
    ////////////////////////////////////////////////////////////////

    WavefrontObjImporterFace::WavefrontObjImporterFace()
    {
        material_id = (-1);
        v_id[0] = 0;
        vt_id[0] = 0;
        vn_id[0] = 0;
    }

    WavefrontObjImporterMaterial::WavefrontObjImporterMaterial()
    {
        material = nullptr;
    }

    WavefrontObjImporterMaterial::~WavefrontObjImporterMaterial()
    {
        if (nullptr != material)
        {
            material->decRef();
        }
    }


    ////////////////////////////////////////////////////////////////
    // WavefrontObjImporter: constructor
    ////////////////////////////////////////////////////////////////
    WavefrontObjImporter::WavefrontObjImporter()
    {
        parentGroup = nullptr;

        objVertices = nullptr;
        objVerticesCount = 0;
        objVerticesMaxLength = 0;

        objMapping = nullptr;
        objMappingCount = 0;
        objMappingMaxLength = 0;

        objNormals = nullptr;
        objNormalsCount = 0;
        objNormalsMaxLength = 0;

        objFaces = nullptr;
        objFacesCount = 0;
        objFacesMaxLength = 0;

        objMaterials = nullptr;
        objMaterialsCount = 0;
        objMaterialsMaxLength = 0;

        referencedVertices = nullptr;
    }


    ////////////////////////////////////////////////////////////////
    // WavefrontObjImporter: destructor
    ////////////////////////////////////////////////////////////////
    WavefrontObjImporter::~WavefrontObjImporter()
    {
        myFiles[0].close();
        myFiles[1].close();

        if (nullptr != objVertices)
        {
            delete[](objVertices);
            objVertices = nullptr;
        }

        if (nullptr != objMapping)
        {
            delete[](objMapping);
            objMapping = nullptr;
        }

        if (nullptr != objNormals)
        {
            delete[](objNormals);
            objNormals = nullptr;
        }

        if (nullptr != objFaces)
        {
            delete[](objFaces);
            objFaces = nullptr;
        }

        if (nullptr != objMaterials)
        {
            delete[](objMaterials);
            objMaterials = nullptr;
        }

        if (nullptr != referencedVertices)
        {
            delete[](referencedVertices);
            referencedVertices = nullptr;
        }
    }


    ////////////////////////////////////////////////////////////////
    // WavefrontObjImporter: open file and set working directory
    ////////////////////////////////////////////////////////////////
    bool WavefrontObjImporter::openObj(eString filename, eGroup* target)
    {
        int32_t i, j;
        char* text = filename.getText();

        if (false == target->getType()->checkHierarchy(&E_GROUP_TYPEINFO))
        {
            throw ErrorMessage
            (
                "WavefrontObjImporter::open():\n" \
                "Selected object is not a \"eGroup\" type!"
            );

            return false;
        }

        parentGroup = target;

        if (!myFiles[0].open(text, (FILE_OPERATOR_MODE_READ | FILE_OPERATOR_MODE_BINARY)))
        {
            throw ErrorMessage
            (
                "WavefrontObjImporter::openObj():\n" \
                "Could not open file: \"%s\"",
                text
            );

            return false;
        }

        j = (-1);

        for (i = filename.getLength() - 1; i >= 0; i--)
        {
            switch (text[i])
            {
                case '.':
                {
                    j = i;

                    break;
                }

                case '/':
                case '\\':
                {
                    workingDirectory = filename.getSubstring(0, (i + 1));

                    if (j < 0)
                    {
                        fileName = filename.getSubstring((i + 1));
                    }
                    else
                    {
                        fileName = filename.getSubstring((i + 1), (j - i - 1));
                    }

                    return true;
                }
            }
        }

        return true;
    }


    ////////////////////////////////////////////////////////////////
    // WavefrontObjImporter: open material library file
    ////////////////////////////////////////////////////////////////
    bool WavefrontObjImporter::openMtl(eString filename)
    {
        eString name = workingDirectory + filename;
        char* text = name.getText();

        if (!myFiles[1].open(text, (FILE_OPERATOR_MODE_READ | FILE_OPERATOR_MODE_BINARY)))
        {
            throw ErrorMessage
            (
                "WavefrontObjImporter::openMtl():\n" \
                "Could not open file: \"%s\"",
                text
            );

            return false;
        }

        return true;
    }


    ////////////////////////////////////////////////////////////////
    // WavefrontObjImporter: expand arrays
    ////////////////////////////////////////////////////////////////

    void WavefrontObjImporter::appendVertices(ePoint3* element, int32_t slots)
    {
        int32_t i;
        ePoint3* temp;

        if ((objVerticesCount + slots) > objVerticesMaxLength)
        {
            temp = new ePoint3 [objVerticesCount + slots];

            if (nullptr != objVertices)
            {
                for (i = 0; i < objVerticesCount; i++)
                {
                    temp[i] = objVertices[i];
                }

                delete[](objVertices);
            }

            objVertices = temp;
            objVerticesMaxLength = (objVerticesCount + slots);
        }

        if (1 == slots)
        {
            objVertices[objVerticesCount] = *element;
            objVerticesCount++;
        }
    }

    void WavefrontObjImporter::appendMapping(ePoint2* element, int32_t slots)
    {
        int32_t i;
        ePoint2* temp;

        if ((objMappingCount + slots) > objMappingMaxLength)
        {
            temp = new ePoint2 [objMappingCount + slots];

            if (nullptr != objMapping)
            {
                for (i = 0; i < objMappingCount; i++)
                {
                    temp[i] = objMapping[i];
                }

                delete[](objMapping);
            }

            objMapping = temp;
            objMappingMaxLength = (objMappingCount + slots);
        }

        if (1 == slots)
        {
            objMapping[objMappingCount] = *element;
            objMappingCount++;
        }
    }

    void WavefrontObjImporter::appendNormals(ePoint3* element, int32_t slots)
    {
        int32_t i;
        ePoint3* temp;

        if ((objNormalsCount + slots) > objNormalsMaxLength)
        {
            temp = new ePoint3 [objNormalsCount + slots];

            if (nullptr != objNormals)
            {
                for (i = 0; i < objNormalsCount; i++)
                {
                    temp[i] = objNormals[i];
                }

                delete[](objNormals);
            }

            objNormals = temp;
            objNormalsMaxLength = (objNormalsCount + slots);
        }

        if (1 == slots)
        {
            objNormals[objNormalsCount] = *element;
            objNormalsCount++;
        }
    }

    void WavefrontObjImporter::appendFaces(WavefrontObjImporterFace* element, int32_t slots)
    {
        int32_t i;
        WavefrontObjImporterFace* temp;

        if ((objFacesCount + slots) > objFacesMaxLength)
        {
            temp = new WavefrontObjImporterFace [objFacesCount + slots];

            if (nullptr != objFaces)
            {
                for (i = 0; i < objFacesCount; i++)
                {
                    temp[i] = objFaces[i];
                }

                delete[](objFaces);
            }

            objFaces = temp;
            objFacesMaxLength = (objFacesCount + slots);
        }

        if (1 == slots)
        {
            objFaces[objFacesCount] = *element;
            objFacesCount++;
        }
    }

    void WavefrontObjImporter::appendMaterials(WavefrontObjImporterMaterial* element, int32_t slots)
    {
        int32_t i;
        WavefrontObjImporterMaterial* temp;

        if ((objMaterialsCount + slots) > objMaterialsMaxLength)
        {
            temp = new WavefrontObjImporterMaterial [objMaterialsCount + slots];

            if (nullptr != objMaterials)
            {
                for (i = 0; i < objMaterialsCount; i++)
                {
                    temp[i] = objMaterials[i];

                    /* Material name reference is increased when copying elements */
                    /* However, we need to increase "eMaterial" refCounter manually before deleting old array! */
                    objMaterials[i].material->incRef();
                }

                delete[](objMaterials);
            }

            objMaterials = temp;
            objMaterialsMaxLength = (objMaterialsCount + slots);
        }

        if (1 == slots)
        {
            objMaterials[objMaterialsCount] = *element;
            objMaterialsCount++;
        }
    }


    ////////////////////////////////////////////////////////////////
    // WavefrontObjImporter: start importing mesh
    ////////////////////////////////////////////////////////////////
    void WavefrontObjImporter::begin()
    {
        readModelData();

        constructTriMeshes();
    }


    ////////////////////////////////////////////////////////////////
    // WavefrontObjImporter: read model data (line by line)
    ////////////////////////////////////////////////////////////////
    void WavefrontObjImporter::readModelData()
    {
        int32_t a, b, c, d, valid_keywords;
        int32_t current_mtl = (-1);

        eString line;
        eString keywords[5];
        eString v_details[3];

        ePoint3 dummy_point3;
        ePoint2 dummy_point2;
        WavefrontObjImporterFace dummy_face;

        /********************************/
        /* Prepare space for elements */

        appendVertices(nullptr, 256);
        appendMapping(nullptr, 256);
        appendNormals(nullptr, 256);
        appendFaces(nullptr, 256);

        while (false == myFiles[0].endOfFileReached())
        {
            /********************************/
            /* Read one line, trim white chars, split */

            line << myFiles[0];

            valid_keywords = ArFunctions::splitString(line, keywords, 5);

            /********************************/
            /* Check the first word */

            if ((valid_keywords > 1) && ('#' != keywords[0].getText()[0]))
            {
                if (keywords[0].compare("mtllib"))
                {
                    if (valid_keywords >= 2)
                    {
                        readMaterialInfo(keywords[1]);
                    }
                }
                else if (keywords[0].compare("v"))
                {
                    if (valid_keywords >= 4)
                    {
                        dummy_point3.x = (float)std::atof(keywords[1].getText());
                        dummy_point3.y = (float)std::atof(keywords[2].getText());
                        dummy_point3.z = (float)std::atof(keywords[3].getText());
                    }
                    else
                    {
                        dummy_point3.x = 0;
                        dummy_point3.y = 0;
                        dummy_point3.z = 0;
                    }

                    appendVertices(&dummy_point3, 1);
                }
                else if (keywords[0].compare("vt"))
                {
                    if (valid_keywords >= 3)
                    {
                        dummy_point2.u = (float)std::atof(keywords[1].getText());
                        dummy_point2.v = (float)std::atof(keywords[2].getText());
                    }
                    else
                    {
                        dummy_point2.u = 0;
                        dummy_point2.v = 0;
                    }

                    appendMapping(&dummy_point2, 1);
                }
                else if (keywords[0].compare("vn"))
                {
                    if (valid_keywords >= 4)
                    {
                        dummy_point3.x = (float)std::atof(keywords[1].getText());
                        dummy_point3.y = (float)std::atof(keywords[2].getText());
                        dummy_point3.z = (float)std::atof(keywords[3].getText());
                    }
                    else
                    {
                        dummy_point3.x = 0;
                        dummy_point3.y = 0;
                        dummy_point3.z = 0;
                    }

                    appendNormals(&dummy_point3, 1);
                }
                else if (keywords[0].compare("usemtl"))
                {
                    current_mtl = (-1);

                    for (a = 0; (current_mtl < 0) && (a < objMaterialsCount); a++)
                    {
                        if (objMaterials[a].name.compare(keywords[1]))
                        {
                            current_mtl = a;
                        }
                    }
                }
                else if (keywords[0].compare("f"))
                {
                    if (valid_keywords >= 4)
                    {
                        for (a = 0; a < 3; a++)
                        {
                            dummy_face.v_id[a] = 0;
                            dummy_face.vt_id[a] = 0;
                            dummy_face.vn_id[a] = 0;

                            b = 0; // number start pointer
                            d = 0; // 3 details

                            for (c = 0; (d < 3) && (c <= keywords[1 + a].getLength()); c++)
                            {
                                if ((c >= keywords[1 + a].getLength()) || ('/' == keywords[1 + a].getText()[c]))
                                {
                                    v_details[d] = keywords[1 + a].getSubstring(b, c - b);
                                    b = c + 1;
                                    d++;
                                }
                            }

                            if (v_details[0].getLength() > 0)
                            {
                                dummy_face.v_id[a] = std::atoi(v_details[0].getText());
                            }

                            if (v_details[1].getLength() > 0)
                            {
                                dummy_face.vt_id[a] = std::atoi(v_details[1].getText());
                            }

                            if (v_details[2].getLength() > 0)
                            {
                                dummy_face.vn_id[a] = std::atoi(v_details[2].getText());
                            }
                        }
                    }
                    else
                    {
                        dummy_face.v_id[0] = 0;
                        dummy_face.vt_id[0] = 0;
                        dummy_face.vn_id[0] = 0;
                    }

                    dummy_face.material_id = current_mtl;

                    appendFaces(&dummy_face, 1);
                }
            }
        }

        myFiles[0].close();
    }


    ////////////////////////////////////////////////////////////////
    // WavefrontObjImporter: read material info (line by line)
    ////////////////////////////////////////////////////////////////
    void WavefrontObjImporter::readMaterialInfo(eString filename)
    {
        eMaterialState* dummy_mtl_state = nullptr;
        eTexture* dummy_texture = nullptr;
        eBitmap* dummy_bitmap = nullptr;

        float color[3];
        bool started_reading_mtl = false;
        WavefrontObjImporterMaterial dummy_obj_mtl;

        int32_t i;
        int32_t valid_keywords;
        eString line;
        eString keywords[5];

        if (!openMtl(filename))
        {
            return;
        }

        while (false == myFiles[1].endOfFileReached())
        {
            line << myFiles[1];

            valid_keywords = ArFunctions::splitString(line, keywords, 5);

            if ((valid_keywords > 1) && ('#' != keywords[0].getText()[0]))
            {
                if (keywords[0].compare("newmtl"))
                {
                    if (valid_keywords >= 2)
                    {
                        if (started_reading_mtl)
                        {
                            appendMaterials(&dummy_obj_mtl, 1);

                            if (nullptr != dummy_mtl_state)
                            {
                                dummy_mtl_state->decRef();
                            }

                            if (nullptr != dummy_texture)
                            {
                                dummy_texture->decRef();
                            }

                            if (nullptr != dummy_bitmap)
                            {
                                dummy_bitmap->decRef();
                            }
                        }
                        else
                        {
                            started_reading_mtl = true;
                        }

                        dummy_obj_mtl.name = keywords[1];

                        dummy_bitmap = new eBitmap();
                        dummy_bitmap->incRef();

                        dummy_texture = new eTexture(dummy_bitmap);
                        dummy_texture->incRef();

                        dummy_mtl_state = new eMaterialState();
                        dummy_mtl_state->incRef();

                        dummy_obj_mtl.material = new eMaterial(nullptr);
                        dummy_obj_mtl.material->incRef();

                        dummy_obj_mtl.material->setName(dummy_obj_mtl.name);
                        dummy_obj_mtl.material->setMaterialFlags(0x01); // "2-sided"
                    }
                }
                else if (keywords[0].compare("Ka"))
                {
                    if (valid_keywords >= 4)
                    {
                        color[0] = (float)std::atof(keywords[1].getText());
                        color[1] = (float)std::atof(keywords[2].getText());
                        color[2] = (float)std::atof(keywords[3].getText());
                    }
                    else
                    {
                        color[0] = 0.5f;
                        color[1] = 0.5f;
                        color[2] = 0.5f;
                    }

                    dummy_mtl_state->setAmbientColor(color);

                    dummy_obj_mtl.material->setMaterialState(dummy_mtl_state);
                }
                else if (keywords[0].compare("Kd"))
                {
                    if (valid_keywords >= 4)
                    {
                        color[0] = (float)std::atof(keywords[1].getText());
                        color[1] = (float)std::atof(keywords[2].getText());
                        color[2] = (float)std::atof(keywords[3].getText());
                    }
                    else
                    {
                        color[0] = 0.5f;
                        color[1] = 0.5f;
                        color[2] = 0.5f;
                    }

                    dummy_mtl_state->setDiffuseColor(color);

                    dummy_obj_mtl.material->setMaterialState(dummy_mtl_state);
                }
                else if (keywords[0].compare("Ks"))
                {
                    if (valid_keywords >= 4)
                    {
                        color[0] = (float)std::atof(keywords[1].getText());
                        color[1] = (float)std::atof(keywords[2].getText());
                        color[2] = (float)std::atof(keywords[3].getText());
                    }
                    else
                    {
                        color[0] = 0;
                        color[1] = 0;
                        color[2] = 0;
                    }

                    dummy_mtl_state->setSpecularColor(color);

                    dummy_obj_mtl.material->setMaterialState(dummy_mtl_state);
                }
                else if (keywords[0].compare("map_Kd"))
                {
                    if (valid_keywords >= 2)
                    {
                        for (i = 2; i < valid_keywords; i++)
                        {
                            keywords[1] += " ";
                            keywords[1] += keywords[i];
                        }

                        dummy_bitmap->setPath(keywords[1]);
                        dummy_bitmap->loadFromFile(workingDirectory);

                        dummy_obj_mtl.material->appendTexture(dummy_texture);

                        /* Prepare for rendering! */
                        dummy_bitmap->generateTexture();
                    }
                }
            }
        }

        if (started_reading_mtl)
        {
            appendMaterials(&dummy_obj_mtl, 1);

            if (nullptr != dummy_mtl_state)
            {
                dummy_mtl_state->decRef();
            }

            if (nullptr != dummy_texture)
            {
                dummy_texture->decRef();
            }

            if (nullptr != dummy_bitmap)
            {
                dummy_bitmap->decRef();
            }
        }

        myFiles[1].close();

        /* Don't decrease reference of "eMaterial" in local structure */
        dummy_obj_mtl.material = nullptr;
    }


    ////////////////////////////////////////////////////////////////
    // WavefrontObjImporter: construct "eTriMesh" objects
    // Append meshes to target "eGroup"
    ////////////////////////////////////////////////////////////////
    void WavefrontObjImporter::constructTriMeshes()
    {
        int32_t i, j, k, l, m, total_indices, total_vertices, total_normals, total_mappings;
        float dummy_y, dummy_z;
        eString trimesh_name;
        ePoint3 boundaries[2];

        eTriMesh* test_trimesh = nullptr;
        eGeoSet* test_geoset = nullptr;

        eGeoArray<ePoint4>* test_vertices_array = nullptr;
        eGeoArray<ushort>* test_indices_offsets = nullptr;
        eGeoArray<ushort>* test_indices_array = nullptr;
        eGeoArray<ePoint2>* test_uv_array = nullptr;
        eGeoArray<ePoint4>* test_normals_array = nullptr;

        ePoint4* test_vertices_data = nullptr;
        ushort* test_indices_offsets_data = nullptr;
        ushort* test_indices_array_data = nullptr;
        ePoint2* test_uv_data = nullptr;
        ePoint4* test_normals_data = nullptr;

        /********************************/
        /* Temporary list of vertices referenced by faces */

        referencedVertices = new int16_t [2 * objVerticesCount];

        /********************************/
        /* Reposition "v", "vt", "vn" and "f" */

        for (i = 0; i < objVerticesCount; i++)
        {
            dummy_y = objVertices[i].y;
            dummy_z = objVertices[i].z;
            objVertices[i].y = (-dummy_z);
            objVertices[i].z = dummy_y;
        }

        for (i = 0; i < objMappingCount; i++)
        {
            objMapping[i].v = (1.0f - objMapping[i].v);
        }

        for (i = 0; i < objNormalsCount; i++)
        {
            dummy_y = objNormals[i].y;
            dummy_z = objNormals[i].z;
            objNormals[i].y = (-dummy_z);
            objNormals[i].z = dummy_y;
        }

        for (i = 0; i < objFacesCount; i++)
        {
            for (j = 0; j < 3; j++)
            {
                objFaces[i].v_id[j]--;
                objFaces[i].vt_id[j]--;
                objFaces[i].vn_id[j]--;
            }
        }

        /********************************/
        /* Create new "eTriMesh" for every material (starting from NONE) */

        for (i = 0; i < objMaterialsCount + 1; i++)
        {
            total_vertices = 0;
            total_indices = 0;
            total_normals = 0;
            total_mappings = 0;

            /********************************/
            /* Checking which vertices will be used */

            std::memset(referencedVertices, 0, sizeof(int16_t) * (2 * objVerticesCount));

            for (j = 0; j < objFacesCount; j++)
            {
                if ((i - 1) == objFaces[j].material_id)
                {
                    for (k = 0; k < 3; k++)
                    {
                        l = objFaces[j].v_id[k];
                        if ((l >= 0) && (l < objVerticesCount))
                        {
                            /* Number of repetitions */
                            referencedVertices[2 * l + 1]++;

                            total_vertices++;
                            total_indices++;
                        }

                        l = objFaces[j].vt_id[k];
                        if ((l >= 0) && (l < objMappingCount))
                        {
                            total_mappings++;
                        }

                        l = objFaces[j].vn_id[k];
                        if ((l >= 0) && (l < objNormalsCount))
                        {
                            total_normals++;
                        }
                    }
                }
            }

            k = 0;

            for (j = 0; j < objVerticesCount; j++)
            {
                if (referencedVertices[2 * j + 1] > 0)
                {
                    /* Resulting ID in vertices array */
                    referencedVertices[2 * j] = k;
                    k += referencedVertices[2 * j + 1];
                }
            }

            /********************************/
            /* Continue if model is not empty */

            if (total_vertices > 0)
            {
                test_trimesh = new eTriMesh();
                test_trimesh->incRef();

                trimesh_name = fileName;
                trimesh_name += " / ";

                if (0 == i)
                {
                    trimesh_name += "???";
                }
                else
                {
                    trimesh_name += objMaterials[i - 1].name;

                    test_trimesh->setMaterial(objMaterials[i - 1].material);
                }

                test_trimesh->setName(trimesh_name);

                test_trimesh->setFlags(0x70000009);

                test_geoset = new eGeoSet();
                test_geoset->incRef();
                test_trimesh->setGeoSet(test_geoset);

                /********************************/
                /* Set-up arrays */

                test_geoset->setTwoIntegers(0x0F, total_vertices);

                test_vertices_data = new ePoint4 [total_vertices];
                test_vertices_array = new eGeoArray<ePoint4>();
                test_vertices_array->setup(total_vertices, test_vertices_data);
                test_geoset->setVerticesArray(test_vertices_array);

                //// test_indices_offsets_data = new ushort [total_indices / 3];
                //// test_indices_offsets = new eGeoArray<ushort>();
                //// test_indices_offsets->setup((total_indices / 3), test_indices_offsets_data);
                //// test_geoset->setIndicesOffsets(test_indices_offsets);

                test_indices_array_data = new ushort [total_indices];
                test_indices_array = new eGeoArray<ushort>();
                test_indices_array->setup(total_indices, test_indices_array_data);
                test_geoset->setIndicesArray(test_indices_array);

                if (total_mappings > 0)
                {
                    test_uv_data = new ePoint2 [total_vertices];
                    test_uv_array = new eGeoArray<ePoint2>;
                    test_uv_array->setup(total_vertices, test_uv_data);
                    test_geoset->setTextureCoordsArray(test_uv_array);
                }

                if (total_normals > 0)
                {
                    test_normals_data = new ePoint4 [total_vertices];
                    test_normals_array = new eGeoArray<ePoint4>();
                    test_normals_array->setup(total_vertices, test_normals_data);
                    test_geoset->setNormalsArray(test_normals_array);
                }

                /********************************/
                /* Fill arrays: indices, vertices, UV mapping, normals */

                total_indices = 0;

                for (j = 0; j < objFacesCount; j++)
                {
                    if ((i - 1) == objFaces[j].material_id)
                    {
                        for (k = 0; k < 3; k++)
                        {
                            l = objFaces[j].v_id[k];
                            if ((l >= 0) && (l < objVerticesCount))
                            {
                                /* Calculate resulting vertex ID */
                                m = referencedVertices[2 * l] + referencedVertices[2 * l + 1] - 1;
                                referencedVertices[2 * l + 1]--;

                                test_indices_array_data[total_indices] = m;

                                /* Copy "v", "vt", and "vn" data */
                                test_vertices_data[m] = {objVertices[l].x, objVertices[l].y, objVertices[l].z, 1.0f};
                                
                                l = objFaces[j].vt_id[k];
                                if ((l >= 0) && (l < objMappingCount))
                                {
                                    test_uv_data[m] = objMapping[l];
                                }

                                l = objFaces[j].vn_id[k];
                                if ((l >= 0) && (l < objNormalsCount))
                                {
                                    test_normals_data[m] = {objNormals[l].x, objNormals[l].y, objNormals[l].z, 0};
                                }
                            }
                            else
                            {
                                test_indices_array_data[total_indices] = 0;
                            }

                            total_indices++;
                        }

                        //// test_indices_offsets_data[total_indices / 3] = 3;
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

                if (nullptr != parentGroup)
                {
                    parentGroup->appendChild(test_trimesh);
                }

                /********************************/
                /* View result in editor's window :) */

                test_geoset->prepareForDrawing();

                test_geoset->decRef();
                test_trimesh->decRef();
            }
        }
    }

}
