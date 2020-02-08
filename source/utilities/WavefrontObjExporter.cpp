#include <utilities/WavefrontObjExporter.h>

#include <kao2engine/eTriMesh.h>
#include <kao2engine/eGeoSet.h>

#include <kao2engine/eMaterial.h>
#include <kao2engine/eMaterialState.h>
#include <kao2engine/eTexture.h>
#include <kao2engine/eBitmap.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // WavefrontObjExporter: constructor
    ////////////////////////////////////////////////////////////////
    WavefrontObjExporter::WavefrontObjExporter()
    {
        trimesh = nullptr;
    }


    ////////////////////////////////////////////////////////////////
    // WavefrontObjExporter: destructor
    ////////////////////////////////////////////////////////////////
    WavefrontObjExporter::~WavefrontObjExporter()
    {
        myFiles[0].close();
        myFiles[1].close();
    }


    ////////////////////////////////////////////////////////////////
    // WavefrontObjExporter: open file and set working directory
    ////////////////////////////////////////////////////////////////
    bool WavefrontObjExporter::openObj(eString filename, eTriMesh* target)
    {
        int32_t i, j;
        char* text = filename.getText();

        if (false == target->getType()->checkHierarchy(&E_TRIMESH_TYPEINFO))
        {
            throw ErrorMessage
            (
                "WavefrontObjExporter::open():\n" \
                "Selected object is not a \"eTriMesh\" type!"
            );

            return false;
        }

        trimesh = target;

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

        myFiles[0] << "# " << trimesh->getStringRepresentation();
        writeNewLine(0);

        myFiles[0] << "# Exported with ZookieWizard at " << time_bufor;
        writeNewLine(0);
        writeNewLine(0);

        /********************************/
        /* Get material info */

        if (uses_mtl = writeMaterialInfo())
        {
            myFiles[0] << "mtllib " << fileName << ".mtl";
            writeNewLine(0);
            writeNewLine(0);
        }

        /********************************/
        /* Vertices, texture mapping, triangles */

        writeModelData(uses_mtl);
    }

    ////////////////////////////////////////////////////////////////
    // WavefrontObjExporter: write texturing info
    ////////////////////////////////////////////////////////////////
    bool WavefrontObjExporter::writeMaterialInfo()
    {
        eMaterial* test_material = trimesh->getMaterial();
        eMaterialState* test_mtl_state;

        eTexture* test_texture;
        eBitmap* test_bitmap;

        char bufor[128];
        float color[3];

        /* Check if model uses any material */

        if (nullptr != test_material)
        {
            if (!openMtl())
            {
                return false;
            }

            myFiles[1] << "newmtl material";
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
                    test_bitmap->exportImageFile(workingDirectory);
                }
            }

            myFiles[1].close();
        }

        return true;
    }


    ////////////////////////////////////////////////////////////////
    // WavefrontObjExporter: write model data
    ////////////////////////////////////////////////////////////////
    void WavefrontObjExporter::writeModelData(bool uses_mtl)
    {
        int32_t a, b, c;
        int32_t f[3];
        char bufor[128];

        int32_t total_indices = 0;
        int32_t array_length = 0;
        ePoint4* array_data4 = nullptr;
        ePoint2* array_data2 = nullptr;

        eGeoArray<ePoint4>* vertices = nullptr;
        eGeoArray<ePoint4>* normals = nullptr;
        eGeoArray<ePoint2>* mapping = nullptr;
        eGeoArray<ushort>* indices_offsets = nullptr;
        eGeoArray<ushort>* indices = nullptr;

        eGeoSet* geo = nullptr;

        /********************************/
        /* Get GeoSet */

        geo = trimesh->getGeoset();

        if (nullptr != geo)
        {
            /********************************/
            /* Get required data */

            vertices = geo->getVerticesArray();
            normals = geo->getNormalsArray();
            mapping = geo->getTextureCoordsArray();
            indices_offsets = geo->getIndicesOffsets();
            indices = geo->getIndicesArray();

            /********************************/
            /* Write vertices */
            /* (converting [X][Y][Z] to [X][Z][-Y]) */

            if (nullptr != vertices)
            {
                array_length = vertices->getLength();
                array_data4 = vertices->getData();

                for (a = 0; a < array_length; a++)
                {
                    sprintf_s
                    (
                        bufor, 128, "v %f %f %f",
                        array_data4[a].x,
                        array_data4[a].z,
                        (- array_data4[a].y)
                    );

                    myFiles[0] << bufor;
                    writeNewLine(0);
                }

                writeNewLine(0);
            }

            /********************************/
            /* Write vertex normals */

            if (nullptr != normals)
            {
                array_length = normals->getLength();
                array_data4 = normals->getData();

                for (a = 0; a < array_length; a++)
                {
                    sprintf_s
                    (
                        bufor, 128, "vn %f %f %f",
                        array_data4[a].x,
                        array_data4[a].z,
                        (- array_data4[a].y)
                    );

                    myFiles[0] << bufor;
                    writeNewLine(0);
                }

                writeNewLine(0);
            }

            /********************************/
            /* Write UV mapping */

            if (nullptr != mapping)
            {
                array_length = mapping->getLength();
                array_data2 = mapping->getData();

                for (a = 0; a < array_length; a++)
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

            /********************************/
            /* Write faces */

            if (uses_mtl)
            {
                myFiles[0] << "usemtl material";
                writeNewLine(0);
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

        myFiles[0].close();
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
                    index[0], index[1], index[2]
                );

                break;
            }

            case 0x03: // "v" + "vt"
            {
                sprintf_s
                (
                    bufor, 128, "f %d/%d %d/%d %d/%d",
                    index[0], index[0],
                    index[1], index[1],
                    index[2], index[2]
                );

                break;
            }

            case 0x05: // "v" + "vn"
            {
                sprintf_s
                (
                    bufor, 128, "f %d//%d %d//%d %d//%d",
                    index[0], index[0],
                    index[1], index[1],
                    index[2], index[2]
                );

                break;
            }

            case 0x07: // "v" + "vt" + "vn"
            {
                sprintf_s
                (
                    bufor, 128, "f %d/%d/%d %d/%d/%d %d/%d/%d",
                    index[0], index[0], index[0],
                    index[1], index[1], index[1],
                    index[2], index[2], index[2]
                );

                break;
            }

            default:
            {
                sprintf_s(bufor, 128, "f");
            }
        }

        myFiles[0] << bufor;
        writeNewLine(0);
    }

}
