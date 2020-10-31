#include <utilities/WavefrontObjImporter.h>

#include <kao2engine/Log.h>

#include <kao2engine/eGroup.h>
#include <kao2engine/eTriMesh.h>
#include <kao2engine/eGeoSet.h>

#include <ZookieWizard/ZookieWizardMaterials.h>
#include <kao2engine/eMaterial.h>
#include <kao2engine/eMaterialState.h>
#include <kao2engine/eTexture.h>
#include <kao2engine/eBitmap.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // WavefrontObjImporter structures
    ////////////////////////////////////////////////////////////////

    WavefrontObjImporterVertex::WavefrontObjImporterVertex()
    {
        x = 0; y = 0; z = 0;

        /* Default color: Black (object is not "glowing" / is affected by lighting) */
        r = 0; g = 0; b = 0;
    }

    bool WavefrontObjImporterVertex::operator == (const WavefrontObjImporterVertex &vertex) const
    {
        return (vertex.x == x) && (vertex.y == y) && (vertex.z == z)
            && (vertex.r == r) && (vertex.g == g) && (vertex.b == b);
    }

    WavefrontObjImporterFace::WavefrontObjImporterFace()
    {
        material_id = (-1);
        group_id = (-1);
        v_id[0] = 0;
        vt_id[0] = 0;
        vn_id[0] = 0;
    }

    bool WavefrontObjImporterFace::matchesSetting(const int32_t g_id, const int32_t m_id) const
    {
        return ((g_id == group_id) && (m_id == material_id));
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

        objGroups = nullptr;
        objGroupsCount = 0;
        objGroupsMaxLength = 0;

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

        if (nullptr != objGroups)
        {
            delete[](objGroups);
            objGroups = nullptr;
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

        workingDirectory = filename.getPath();
        fileName = filename.getFilename(false);

        return true;
    }


    ////////////////////////////////////////////////////////////////
    // WavefrontObjImporter: open material library file
    ////////////////////////////////////////////////////////////////
    bool WavefrontObjImporter::openMtl(eString filename)
    {
        eString name = filename.isRooted() ? filename : (workingDirectory + filename);
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

    void WavefrontObjImporter::appendVertices(WavefrontObjImporterVertex* element, int32_t slots)
    {
        int32_t i;
        WavefrontObjImporterVertex* temp;

        if ((objVerticesCount + slots) > objVerticesMaxLength)
        {
            temp = new WavefrontObjImporterVertex [objVerticesCount + slots];

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

    void WavefrontObjImporter::appendGroups(eString* element, int32_t slots)
    {
        int32_t i;
        eString* temp;

        if ((objGroupsCount + slots) > objGroupsMaxLength)
        {
            temp = new eString [objGroupsCount + slots];

            if (nullptr != objGroups)
            {
                for (i = 0; i < objGroupsCount; i++)
                {
                    temp[i] = objGroups[i];
                }

                delete[](objGroups);
            }

            objGroups = temp;
            objGroupsMaxLength = (objGroupsCount + slots);
        }

        if (1 == slots)
        {
            objGroups[objGroupsCount] = *element;
            objGroupsCount++;
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
        int32_t current_group = (-1);

        eString line;
        eString keywords[8];
        eString v_details[3];

        WavefrontObjImporterVertex dummy_vertex;
        ePoint3 dummy_point3;
        ePoint2 dummy_point2;
        WavefrontObjImporterFace dummy_face;

        theLog.print(" Parsing the OBJ document, please wait...\n");

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

            line = ArFunctions::removeComment(line, true);

            valid_keywords = ArFunctions::splitString(line, keywords, 8);

            /********************************/
            /* Check the first word */

            if (valid_keywords > 1)
            {
                if (keywords[0].compareExact("mtllib", true))
                {
                    if (valid_keywords >= 2)
                    {
                        for (a = 2; a < valid_keywords; a++)
                        {
                            keywords[1] += " ";
                            keywords[1] += keywords[a];
                        }

                        readMaterialInfo(keywords[1]);
                    }
                }
                else if (keywords[0].compareExact("v", true))
                {
                    dummy_vertex = WavefrontObjImporterVertex();

                    if (valid_keywords >= 4)
                    {
                        dummy_vertex.x = (float)std::atof(keywords[1].getText());
                        dummy_vertex.y = (float)std::atof(keywords[2].getText());
                        dummy_vertex.z = (float)std::atof(keywords[3].getText());

                        /* Extended OBJ format: color components */

                        if (valid_keywords >= 5)
                        {
                            dummy_vertex.r = (float)std::atof(keywords[4].getText());
                        }

                        if (valid_keywords >= 6)
                        {
                            dummy_vertex.g = (float)std::atof(keywords[5].getText());
                        }

                        if (valid_keywords >= 7)
                        {
                            dummy_vertex.b = (float)std::atof(keywords[6].getText());
                        }
                    }

                    appendVertices(&dummy_vertex, 1);
                }
                else if (keywords[0].compareExact("vt", true))
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
                else if (keywords[0].compareExact("vn", true))
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
                else if (keywords[0].compareExact("usemtl", true))
                {
                    current_mtl = (-1);

                    for (a = 2; a < valid_keywords; a++)
                    {
                        keywords[1] += " ";
                        keywords[1] += keywords[a];
                    }

                    for (a = 0; (current_mtl < 0) && (a < objMaterialsCount); a++)
                    {
                        if (objMaterials[a].name.compareExact(keywords[1], true))
                        {
                            current_mtl = a;
                        }
                    }
                }
                else if (keywords[0].compareExact("o", true))
                {
                    current_group = (-1);

                    for (a = 2; a < valid_keywords; a++)
                    {
                        keywords[1] += " ";
                        keywords[1] += keywords[a];
                    }

                    for (a = 0; (current_group < 0) && (a < objGroupsCount); a++)
                    {
                        if (objGroups[a].compareExact(keywords[1], true))
                        {
                            current_group = a;
                        }
                    }

                    if (current_group < 0)
                    {
                        appendGroups(&(keywords[1]), 1);
                        current_group = (objGroupsCount - 1);
                    }
                }
                else if (keywords[0].compareExact("f", true))
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
                    dummy_face.group_id = current_group;

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

        theLog.print(eString(" Parsing material library \"") + filename + "\".\n");

        while (false == myFiles[1].endOfFileReached())
        {
            line << myFiles[1];

            valid_keywords = ArFunctions::splitString(line, keywords, 5);

            if ((valid_keywords > 1) && ('#' != keywords[0].getText()[0]))
            {
                if (keywords[0].compareExact("newmtl", true))
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

                        /* 0x01 = "2-sided" */
                        dummy_obj_mtl.material->setMaterialFlags(0x01);
                    }
                }
                else if (keywords[0].compareExact("Ka", true))
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
                else if (keywords[0].compareExact("Kd", true))
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
                else if (keywords[0].compareExact("Ks", true))
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
                else if (keywords[0].compareExact("map_Kd", true))
                {
                    if (valid_keywords >= 2)
                    {
                        for (i = 2; i < valid_keywords; i++)
                        {
                            keywords[1] += " ";
                            keywords[1] += keywords[i];
                        }

                        try
                        {
                            dummy_bitmap->setPath(keywords[1]);
                            dummy_bitmap->loadFromFile(workingDirectory, false);
                        }
                        catch (ErrorMessage &err)
                        {
                            err.display();
                        }

                        dummy_obj_mtl.material->appendTexture(dummy_texture);

                        if (dummy_bitmap->isTransparent())
                        {
                            /* 0x02 = "TM_BLEND" */
                            dummy_obj_mtl.material->setMaterialFlags(0x02);
                        }

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
        int32_t group_id, mat_id, j, k, l, m;
        int32_t total_indices, total_vertices, total_normals, total_mappings;
        float dummy_floats[3];
        eString trimesh_name;
        ePoint3 dummy_vectors[2];

        uint16_t temp_id[4];
        bool temp_tests[3];

        eGroup* test_group = nullptr;
        eTriMesh* test_trimesh = nullptr;
        eGeoSet* test_geoset = nullptr;
        eMaterialState* dummy_mtl_state = nullptr;

        eGeoArray<ePoint4>* test_vertices_array = nullptr;
        eGeoArray<ushort>* test_indices_offsets = nullptr;
        eGeoArray<ushort>* test_indices_array = nullptr;
        eGeoArray<ePoint2>* test_uv_array = nullptr;
        eGeoArray<ePoint4>* test_normals_array = nullptr;
        eGeoArray<ePoint4>* test_colors_array = nullptr;

        ePoint4* test_vertices_data = nullptr;
        ushort* test_indices_offsets_data = nullptr;
        ushort* test_indices_array_data = nullptr;
        ePoint2* test_uv_data = nullptr;
        ePoint4* test_normals_data = nullptr;
        ePoint4* test_colors_data = nullptr;

        theLog.print(" Constructing 3D objects, please wait...\n");

        /********************************/
        /* Temporary list of vertices referenced by faces */
        /* [0] = objVertices ID, [1] = objMapping ID, */
        /* [2] = objNormals ID, [3] = separate list of indices */

        referencedVertices = new uint16_t [4 * (3 * objFacesCount)];

        /********************************/
        /* Reposition "v", "vt", "vn" and "f" */

        for (j = 0; j < objVerticesCount; j++)
        {
            dummy_floats[0] = objVertices[j].y;
            dummy_floats[1] = objVertices[j].z;
            objVertices[j].y = (-dummy_floats[1]);
            objVertices[j].z = dummy_floats[0];
        }

        for (j = 0; j < objMappingCount; j++)
        {
            objMapping[j].v = (1.0f - objMapping[j].v);
        }

        for (j = 0; j < objNormalsCount; j++)
        {
            dummy_floats[0] = objNormals[j].y;
            dummy_floats[1] = objNormals[j].z;
            objNormals[j].y = (-dummy_floats[1]);
            objNormals[j].z = dummy_floats[0];
        }

        for (j = 0; j < objFacesCount; j++)
        {
            for (k = 0; k < 3; k++)
            {
                objFaces[j].v_id[k]--;
                objFaces[j].vt_id[k]--;
                objFaces[j].vn_id[k]--;

                /* Using same IDs for "duplicated" v/vt/vn entries */

                m = objFaces[j].v_id[k];

                if (m < objVerticesCount)
                {
                    for (l = 0; l < m; l++)
                    {
                        if (objVertices[l] == objVertices[m])
                        {
                            objFaces[j].v_id[k] = l;

                            l = m; // explicit break
                        }
                    }
                }

                m = objFaces[j].vt_id[k];

                if (m < objMappingCount)
                {
                    for (l = 0; l < m; l++)
                    {
                        if (objMapping[l] == objMapping[m])
                        {
                            objFaces[j].vt_id[k] = l;

                            l = m; // explicit break
                        }
                    }
                }

                m = objFaces[j].vn_id[k];

                if (m < objNormalsCount)
                {
                    for (l = 0; l < m; l++)
                    {
                        if (objNormals[l] == objNormals[m])
                        {
                            objFaces[j].vn_id[k] = l;

                            l = m; // explicit break
                        }
                    }
                }
            }
        }

        /********************************/
        /* Sort by object groups (starting from NONE) */

        for (group_id = (-1); group_id < objGroupsCount; group_id++)
        {
            if (groupHasMultipleMaterials(group_id))
            {
                test_group = new eGroup;
                test_group->incRef();

                trimesh_name = fileName;

                if (group_id >= 0)
                {
                    trimesh_name += " - ";
                    trimesh_name += objGroups[group_id];
                }

                test_group->setName(trimesh_name);

                test_group->setFlags(0x10000089);
            }

            /********************************/
            /* Create new "eTriMesh" for every material (starting from NONE) */

            for (mat_id = (-1); mat_id < objMaterialsCount; mat_id++)
            {
                total_vertices = 0;
                total_indices = 0;
                total_normals = 0;
                total_mappings = 0;

                /********************************/
                /* Checking which vertices will be used */

                for (j = 0; j < objFacesCount; j++)
                {
                    if (objFaces[j].matchesSetting(group_id, mat_id))
                    {
                        for (k = 0; k < 3; k++)
                        {
                            temp_id[0] = objFaces[j].v_id[k];
                            temp_id[1] = objFaces[j].vt_id[k];
                            temp_id[2] = objFaces[j].vn_id[k];

                            temp_tests[0] = (temp_id[0] >= 0) && (temp_id[0] < objVerticesCount);
                            temp_tests[1] = (temp_id[1] >= 0) && (temp_id[1] < objMappingCount);
                            temp_tests[2] = (temp_id[2] >= 0) && (temp_id[2] < objNormalsCount);

                            if (temp_tests[0])
                            {
                                m = 0;

                                /* `3 == m` and the loop breaks only when a vertex with exact params existed */

                                for (l = 0; (l < total_vertices) && (m < 3); l++)
                                {
                                    if (referencedVertices[4 * l + 0] == temp_id[0])
                                    {
                                        m = 1;

                                        if (temp_tests[1])
                                        {
                                            if (referencedVertices[4 * l + 1] == temp_id[1])
                                            {
                                                m++;
                                            }
                                        }
                                        else
                                        {
                                            m++;
                                        }

                                        if (temp_tests[2])
                                        {
                                            if (m >= 2) // UV mapping must be matching too.
                                            {
                                                temp_id[3] = referencedVertices[4 * l + 2];

                                                if (temp_id[3] != temp_id[2])
                                                {
                                                    if ((temp_id[3] >= 0) && (temp_id[3] < objNormalsCount))
                                                    {
                                                        objNormals[temp_id[3]] += objNormals[temp_id[2]];
                                                        objNormals[temp_id[3]].normalize();

                                                        m++;
                                                    }
                                                }
                                                else
                                                {
                                                    m++;
                                                }
                                            }
                                        }
                                        else
                                        {
                                            m++;
                                        }
                                    }
                                    else
                                    {
                                        m = 0;
                                    }
                                }

                                if (m < 3)
                                {
                                    /* Inserting another vertex parameters because it differs */

                                    referencedVertices[4 * total_vertices + 0] = temp_id[0];

                                    if (temp_tests[1])
                                    {
                                        referencedVertices[4 * total_vertices + 1] = temp_id[1];

                                        total_mappings++;
                                    }

                                    if (temp_tests[2])
                                    {
                                        referencedVertices[4 * total_vertices + 2] = temp_id[2];

                                        total_normals++;
                                    }
                                    else
                                    {
                                        /* marking Normal ID as invalid, so it cannot be used for addition */
                                        referencedVertices[4 * total_vertices + 2] = (-1);
                                    }

                                    total_vertices++;
                                }
                                else
                                {
                                    /* Last matching vertex ID before loop counter was increased */
                                    l--;
                                }

                                referencedVertices[4 * total_indices + 3] = l;

                                total_indices++;
                            }
                        }
                    }
                }

                /********************************/
                /* Continue if model is not empty */

                if (total_vertices > 65535)
                {
                    ErrorMessage
                    (
                        "WavefrontObjImporter::constructTriMeshes():\n"
                        "too many vertices! (max 65535 per object)"
                    ).display();
                }
                else if (total_vertices > 0)
                {
                    test_trimesh = new eTriMesh();
                    test_trimesh->incRef();

                    trimesh_name = fileName;

                    if (group_id >= 0)
                    {
                        trimesh_name += " - ";
                        trimesh_name += objGroups[group_id];
                    }

                    trimesh_name += " / ";

                    if (mat_id < 0)
                    {
                        trimesh_name += "???";
                    }
                    else
                    {
                        trimesh_name += objMaterials[mat_id].name;

                        test_trimesh->setMaterial(objMaterials[mat_id].material);
                    }

                    test_trimesh->setName(trimesh_name);

                    test_trimesh->setFlags(0x10000089);

                    test_geoset = new eGeoSet();
                    test_geoset->incRef();
                    test_trimesh->setGeoset(test_geoset);

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

                    test_colors_data = new ePoint4 [total_vertices];
                    test_colors_array = new eGeoArray<ePoint4>();
                    test_colors_array->setup(total_vertices, test_colors_data);
                    test_geoset->setColorsArray(test_colors_array);

                    if (total_mappings > 0)
                    {
                        test_uv_data = new ePoint2 [total_vertices];
                        test_uv_array = new eGeoArray<ePoint2>;
                        test_uv_array->setup(total_vertices, test_uv_data);
                        test_geoset->setTextureCoordsArray(test_uv_array);
                    }
                    else
                    {
                        test_geoset->setTextureCoordsArray(nullptr);
                    }

                    if (total_normals > 0)
                    {
                        test_normals_data = new ePoint4 [total_vertices];
                        test_normals_array = new eGeoArray<ePoint4>();
                        test_normals_array->setup(total_vertices, test_normals_data);
                        test_geoset->setNormalsArray(test_normals_array);
                    }

                    /********************************/
                    /* Fill arrays: indices, vertices, colors, UV mapping, normals */

                    for (j = 0; j < total_indices; j++)
                    {
                        test_indices_array_data[j] = referencedVertices[4 * j + 3];
                    }

                    for (j = 0; j < total_vertices; j++)
                    {
                        k = referencedVertices[4 * j + 0];

                        test_vertices_data[j] = {objVertices[k].x, objVertices[k].y, objVertices[k].z, 1.0f};

                        test_colors_data[j] = {objVertices[k].r, objVertices[k].g, objVertices[k].b, 1.0f};

                        if (total_mappings > 0)
                        {
                            k = referencedVertices[4 * j + 1];

                            test_uv_data[j] = objMapping[k];
                        }

                        if (total_normals > 0)
                        {
                            k = referencedVertices[4 * j + 2];

                            test_normals_data[j] = {objNormals[k].x, objNormals[k].y, objNormals[k].z, 0};
                        }
                    }

                    /********************************/
                    /* Calculate boundary box */

                    calculateBoundaryBox(dummy_vectors[0], dummy_vectors[1], total_vertices, test_vertices_data, 0, nullptr);

                    test_trimesh->setBoundaryBox(dummy_vectors[0], dummy_vectors[1]);

                    /********************************/
                    /* Update "eGroup" */

                    if (nullptr != test_group)
                    {
                        test_group->appendChild(test_trimesh);

                        if (nullptr != parentGroup)
                        {
                            parentGroup->appendChild(test_group);
                        }
                    }
                    else if (nullptr != parentGroup)
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

            if (nullptr != test_group)
            {
                test_group->decRef();
                test_group = nullptr;
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // WavefrontObjImporter: check if object should be grouped
    ////////////////////////////////////////////////////////////////
    bool WavefrontObjImporter::groupHasMultipleMaterials(const int32_t g_id) const
    {
        int32_t a, b;

        for (a = 0; a < (objFacesCount - 1); a++)
        {
            if (g_id == objFaces[a].group_id)
            {
                for (b = (a + 1); b < objFacesCount; b++)
                {
                    if (g_id == objFaces[b].group_id)
                    {
                        if (objFaces[a].material_id != objFaces[b].material_id)
                        {
                            return true;
                        }
                    }
                }
            }
        }

        return false;
    }

}
