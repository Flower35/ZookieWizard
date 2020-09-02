#include <kao2ar/Archive.h>
#include <kao2engine/eGroup.h>

#include <utilities/ColladaExporter.h>
#include <utilities/WavefrontObjExporter.h>
#include <utilities/WavefrontObjImporter.h>
#include <kao2ar/ArCustomParser.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Ar: show scene as a structured text file
    ////////////////////////////////////////////////////////////////
    void Archive::writeStructureToTextFile(const char* output_path) const
    {
        FileOperator text_file;

        if (nullptr != parentObject)
        {
            text_file.setDir((char*)output_path);
            text_file.createDir();

            if (!text_file.open(output_path, 0))
            {
                throw ErrorMessage
                (
                    "Archive::writeStructureToTextFile():\n\n" \
                    "Could not open file: \"%s\"",
                    output_path
                );
            }

            parentObject->writeStructureToTextFile(text_file, 0);
        }
    }


    ////////////////////////////////////////////////////////////////
    // Ar: show scene as XML file
    ////////////////////////////////////////////////////////////////
    void Archive::writeStructureToXmlFile(eString filename) const
    {
        eNode* test_node;
        ColladaExporter exporter;

        if (nullptr != parentObject)
        {
            if (parentObject->getType()->checkHierarchy(&E_NODE_TYPEINFO))
            {
                test_node = (eNode*)parentObject;

                exporter.openXml(filename);

                while (exporter.continueExporting())
                {
                    test_node->writeNodeToXmlFile(exporter);
                }
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // Ar: export selected TriMesh to OBJ file
    ////////////////////////////////////////////////////////////////
    void Archive::writeSelectedObjectToObjFile(eString filename) const
    {
        WavefrontObjExporter exporter;

        if (nullptr != selectedObject)
        {
            if (exporter.openObj(filename, selectedObject))
            {
                exporter.begin();
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // Ar: import TriMesh to selected Group from OBJ file
    ////////////////////////////////////////////////////////////////
    void Archive::appendToSelectedObjectFromObjFile(eString filename)
    {
        WavefrontObjImporter importer;

        if (nullptr != selectedObject)
        {
            if (importer.openObj(filename, (eGroup*)selectedObject))
            {
                importer.begin();

                changeSelectedObject(NODES_LISTBOX_UPDATE_CURRENT, nullptr);
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // Ar: change Nodes with specific instructions from a TXT file
    ////////////////////////////////////////////////////////////////
    int32_t Archive::changeNodesWithTxtFile(const char* filename)
    {
        ArCustomParser parser;
        eGroup* dummy_group = nullptr;

        if ((nullptr != selectedObject) && selectedObject->getType()->checkHierarchy(&E_GROUP_TYPEINFO))
        {
            dummy_group = (eGroup*)selectedObject;
        }

        if (parser.openFile(filename, dummy_group))
        {
            return parser.beginParsing();
        }

        return (-1);
    }

}
