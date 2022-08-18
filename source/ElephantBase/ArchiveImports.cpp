#include <ElephantBase/Archive.h>
#include <ElephantEngine/eGroup.h>

#include <utilities/ColladaExporter.h>
#include <utilities/WavefrontObjExporter.h>
#include <utilities/WavefrontObjImporter.h>
#include <ElephantBase/ArCustomParser.h>

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
    void Archive::exportProxies(int32_t version_override) const
    {
        if ((nullptr != parentObject) && parentObject->getType()->checkHierarchy(&E_NODE_TYPEINFO))
        {
            ((eNode*)parentObject)->exportXRef(getMediaDir(), version_override);
        }
    }


    ////////////////////////////////////////////////////////////////
    // Archive: reload all proxies
    ////////////////////////////////////////////////////////////////
    void Archive::reloadProxies(int32_t version_override) const
    {
        if ((nullptr != parentObject) && parentObject->getType()->checkHierarchy(&E_NODE_TYPEINFO))
        {
            ((eNode*)parentObject)->reloadXRef(getMediaDir(), version_override);
        }
    }


    ////////////////////////////////////////////////////////////////
    // Archive: show scene as a structured JSON file
    ////////////////////////////////////////////////////////////////
    void Archive::writeTreeToJsonFile(const char* output_path) const
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
                    "Archive::writeTreeToJsonFile():\n\n" \
                    "Could not open file: \"%s\"",
                    output_path
                );
            }

            JsonValue jsonOutput;
            parentObject->dumpTreeAsJsonValue(jsonOutput, true);
            jsonOutput.dump(text_file, 0, false);
            text_file << "\n";
        }
    }


    ////////////////////////////////////////////////////////////////
    // Archive: show scene as XML file
    ////////////////////////////////////////////////////////////////
    void Archive::writeTreeToXmlFile(eString filename) const
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
