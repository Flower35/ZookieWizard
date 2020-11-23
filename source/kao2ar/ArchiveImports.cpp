#include <kao2ar/Archive.h>
#include <kao2engine/eGroup.h>

#include <utilities/ColladaExporter.h>
#include <utilities/WavefrontObjExporter.h>
#include <utilities/WavefrontObjImporter.h>
#include <kao2ar/ArCustomParser.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Archive: export all scripts
    ////////////////////////////////////////////////////////////////
    void Archive::exportScripts() const
    {
        if ((nullptr != parentObject) && parentObject->getType()->checkHierarchy(&E_NODE_TYPEINFO))
        {
            ((eNode*)parentObject)->exportScripts(getMediaDir());
        }
    }

    ////////////////////////////////////////////////////////////////
    // Archive: export all proxies
    ////////////////////////////////////////////////////////////////
    void Archive::exportProxies() const
    {
        if ((nullptr != parentObject) && parentObject->getType()->checkHierarchy(&E_NODE_TYPEINFO))
        {
            ((eNode*)parentObject)->exportXRef(getMediaDir(), engineOpenedWith);
        }
    }


    ////////////////////////////////////////////////////////////////
    // Archive: show scene as a structured text file
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

            parentObject->writeStructureToTextFile(text_file, 0, false);
        }
    }


    ////////////////////////////////////////////////////////////////
    // Archive: show scene as XML file
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
    // Archive: export selected TriMesh to OBJ file
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
    // Archive: import TriMesh to selected Group from OBJ file
    ////////////////////////////////////////////////////////////////
    void Archive::appendToSelectedObjectFromObjFile(eString filename)
    {
        WavefrontObjImporter importer;
        eSRP default_srp;

        if (nullptr != selectedObject)
        {
            importer.begin(filename, (eGroup*)selectedObject, WAVEFRONT_OBJ_IMPORTER_DEFAULT_FLAGS, default_srp);

            changeSelectedObject(NODES_LISTBOX_UPDATE_CURRENT, nullptr);
        }
    }


    ////////////////////////////////////////////////////////////////
    // Archive: change Nodes with specific instructions from a TXT file
    ////////////////////////////////////////////////////////////////
    int32_t Archive::changeNodesWithTxtFile(const char* filename)
    {
        ArCustomParser parser;

        int32_t result = (-1);
        eGroup* dummy_group = nullptr;

        if ((nullptr != selectedObject) && selectedObject->getType()->checkHierarchy(&E_GROUP_TYPEINFO))
        {
            dummy_group = (eGroup*)selectedObject;
        }

        if (parser.openFile(filename, dummy_group))
        {
            result = parser.beginParsing();

            selectedObject = parser.getDefaultParent();
            changeSelectedObject(NODES_LISTBOX_UPDATE_CURRENT, nullptr);
        }

        return result;
    }

}
