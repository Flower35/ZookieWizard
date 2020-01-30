#include <utilities/ColladaExporter.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ColladaExporter: constructor
    ////////////////////////////////////////////////////////////////
    ColladaExporter::ColladaExporter()
    {
        state = 0;
        indentation = 0;

        tagsCount = 0;
        tagsMaxLength = 16;
        tags = new ColladaExporterTag [16];

        objRefsCount = 0;
        objRefsMaxLength = 1024; // (--dsp--) "32768"
        objRefs = new ColladaExporterObjRef [1024];
    }


    ////////////////////////////////////////////////////////////////
    // ColladaExporter: destructor
    ////////////////////////////////////////////////////////////////
    ColladaExporter::~ColladaExporter()
    {
        myFile.close();

        if (nullptr != tags)
        {
            delete[](tags);
            tags = nullptr;
        }

        if (nullptr != objRefs)
        {
            delete[](objRefs);
            objRefs = nullptr;
        }
    }


    ////////////////////////////////////////////////////////////////
    // ColladaExporter: open file and set working directory
    ////////////////////////////////////////////////////////////////
    void ColladaExporter::openXml(eString filename)
    {
        int32_t i, l;
        char* text = filename.getText();

        if (!myFile.open(text, (FILE_OPERATOR_MODE_BINARY)))
        {
            throw ErrorMessage
            (
                "ColladaExporter::open():\n" \
                "Could not open file: \"%s\"",
                text
            );
        }

        l = filename.getLength();

        for (i = l - 1; i >= 0; i--)
        {
            switch (text[i])
            {
                case '/':
                case '\\':
                {
                    workingDirectory = filename.getSubstring(0, (i + 1));

                    return;
                }
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // ColladaExporter: should we continue exporting data
    ////////////////////////////////////////////////////////////////
    bool ColladaExporter::continueExporting()
    {
        bool result = true;

        switch (state)
        {
            case 0:
            {
                myFile << "<?xml version = \"1.0\" encoding=\"utf-8\"?>";
                writeNewLine();

                openTag("COLLADA");
                insertTagAttrib("xmlns", "http://www.collada.org/2008/03/COLLADASchema");
                insertTagAttrib("version", "1.5.0");

                openTag("asset");
                
                openTag("created");
                closeTag();

                openTag("modified");
                closeTag();

                openTag("unit");
                insertTagAttrib("name", "meter");
                insertTagAttrib("meter", "1");
                closeTag();

                openTag("up_axis");
                writeInsideTag("Z_UP");
                closeTag();

                closeTag(); // "asset"

                /* Open first library */
                /* Each case will close its library and move onto another group */

                openTag("library_lights");

                break;
            }

            case COLLADA_EXPORTER_STATE_LIGHTS:
            {
                closeTag(); // "library_lights"

                openTag("library_cameras");

                break;
            }

            case COLLADA_EXPORTER_STATE_CAMERAS:
            {
                closeTag(); // "library_cameras"

                openTag("library_images");

                break;
            }

            case COLLADA_EXPORTER_STATE_IMAGES:
            {
                closeTag(); // "library_images"

                openTag("library_effects");

                break;
            }

            case COLLADA_EXPORTER_STATE_EFFECTS:
            {
                closeTag(); // "library_effects"

                openTag("library_materials");

                break;
            }

            case COLLADA_EXPORTER_STATE_MATERIALS:
            {
                closeTag(); // "library_materials"

                openTag("library_geometries");

                break;
            }

            case COLLADA_EXPORTER_STATE_GEOMETRIES:
            {
                closeTag(); // "library_geometries"

                openTag("library_controllers");

                break;
            }

            case COLLADA_EXPORTER_STATE_CONTROLLERS:
            {
                closeTag(); // "library_controllers"

                openTag("library_animations");

                break;
            }

            case COLLADA_EXPORTER_STATE_ANIMATIONS:
            {
                closeTag(); // "library_animations"

                openTag("library_visual_scenes");

                break;
            }

            case COLLADA_EXPORTER_STATE_VISUAL_SCENES:
            {
                closeTag(); // "library_visual_scenes"

                openTag("scene");

                break;
            }

            case COLLADA_EXPORTER_STATE_SCENE:
            {
                closeTag(); // "scene"

                closeTag(); // "COLLADA"

                result = false;

                if (0 != tagsCount)
                {
                    throw ErrorMessage
                    (
                        "ColladaExporter::continueExporting():\n" \
                        "finished constructing document, but there are tags left unclosed!"
                    );
                }

                break;
            }

            default:
            {
                throw ErrorMessage
                (
                    "ColladaExporter::continueExporting():\n" \
                    "unrecognized state!"
                );
            }
        }

        state++;

        return result;
    }


    ////////////////////////////////////////////////////////////////
    // ColladaExporter: write new line
    ////////////////////////////////////////////////////////////////
    void ColladaExporter::writeNewLine()
    {
        myFile << "\n";
    }


    ////////////////////////////////////////////////////////////////
    // ColladaExporter: write new line
    ////////////////////////////////////////////////////////////////
    void ColladaExporter::writeIndentation()
    {
        int32_t i;
        eString spaces("  ");

        /* Two spaces per nested tag */

        for (i = 0; i < indentation; i++)
        {
            myFile << spaces;
        }
    }


    ////////////////////////////////////////////////////////////////
    // ColladaExporter: write text inside XML tag
    ////////////////////////////////////////////////////////////////
    void ColladaExporter::writeInsideTag(eString text)
    {
        if (tagsCount <= 0)
        {
            throw ErrorMessage
            (
                "ColladaExporter::writeInsideTag():" \
                "no open tags!"
            );
        }

        switch (tags[tagsCount - 1].state)
        {
            case 1:
            {
                /* There are no nested tags after tag opening */

                myFile << ">";

                myFile << text;

                tags[tagsCount - 1].state = 3;

                break;
            }

            case 3:
            {
                /* Entering large text in smaller parts (to avoid strings overflow) */

                myFile << " ";

                myFile << text;

                break;
            }

            default:
            {
                throw ErrorMessage
                (
                    "ColladaExporter::writeInsideTag():\n" \
                    "invalid state! (tag <%s>)",
                    tags[tagsCount - 1].name.getText()
                );
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // ColladaExporter: open new XML tag
    ////////////////////////////////////////////////////////////////
    void ColladaExporter::openTag(eString name)
    {
        int32_t i;
        ColladaExporterTag* temp_tags;

        if (tagsCount > 0)
        {
            switch (tags[tagsCount - 1].state)
            {
                case 1:
                {
                    /* New nested tag */

                    myFile << ">";

                    indentation++;
                    writeNewLine();

                    tags[tagsCount - 1].state = 2;

                    break;
                }

                case 2:
                {
                    /* Previous tag is already open */

                    /* When tags are cloed, new line is automatically inserted */

                    break;
                }

                default:
                {
                    throw ErrorMessage
                    (
                        "ColladaExporter::openTag():\n" \
                        "invalid state! (tag <%s>)",
                        tags[tagsCount - 1].name.getText()
                    );
                }
            }
        }

        if (tagsCount >= tagsMaxLength)
        {
            temp_tags = new ColladaExporterTag [tagsMaxLength + 1];

            for (i = 0; i < tagsMaxLength; i++)
            {
                temp_tags[i] = tags[i];
            }

            delete[](tags);
            tags = temp_tags;

            tagsMaxLength++;
        }

        /* Set tag state and save tag name */

        writeIndentation();
        myFile << "<" << name;

        tags[tagsCount].name = name;
        tags[tagsCount].state = 1;
        tagsCount++;
    }


    ////////////////////////////////////////////////////////////////
    // ColladaExporter: insert tag attribute
    ////////////////////////////////////////////////////////////////
    void ColladaExporter::insertTagAttrib(eString name, eString value)
    {
        eString test_str;

        if (tagsCount <= 0)
        {
            throw ErrorMessage
            (
                "ColladaExporter::insertTagAttrib():\n" \
                "no open tags!"
            );
        }

        if (1 != tags[tagsCount - 1].state)
        {
            throw ErrorMessage
            (
                "ColladaExporter::insertTagAttrib():\n" \
                "invalid state! (tag <%s>)",
                tags[tagsCount - 1].name.getText()
            );
        }

        test_str = " ";
        test_str += name;
        test_str += "=\"";
        test_str += value;
        test_str += "\"";

        myFile << test_str;
    }


    ////////////////////////////////////////////////////////////////
    // ColladaExporter: close tag
    ////////////////////////////////////////////////////////////////
    void ColladaExporter::closeTag()
    {
        eString test_str;

        if (tagsCount <= 0)
        {
            throw ErrorMessage
            (
                "ColladaExporter::closeTag():" \
                "no open tags!"
            );
        }

        switch (tags[tagsCount - 1].state)
        {
            case 1:
            {
                /* No nested list (eg. only attributes in empty element) */

                myFile << " />";
                writeNewLine();

                break;
            }

            case 2:
            case 3:
            {
                /* End one level of nested tags */

                if (2 == tags[tagsCount - 1].state)
                {
                    /* No indentation for one-line tag with text inside */
                    indentation--;
                    writeIndentation();
                }

                test_str = "</";
                test_str += tags[tagsCount - 1].name;
                test_str += ">";

                myFile << test_str;
                writeNewLine();

                break;
            }
        }

        tagsCount--;
    }


    ////////////////////////////////////////////////////////////////
    // ColladaExporter: get current state
    ////////////////////////////////////////////////////////////////
    int32_t ColladaExporter::getState()
    {
        return state;
    }


    ////////////////////////////////////////////////////////////////
    // ColladaExporter: get and update Object Reference IDs
    ////////////////////////////////////////////////////////////////
    int32_t ColladaExporter::getObjectRefId(int32_t type, void* pointer, bool can_be_created)
    {
        int32_t i;
        int32_t current_id;
        //// (--dsp--) ColladaExporterObjRef* temp_refs;

        /* Checking if pointer was already copied */

        for (i = 0; i < objRefsCount; i++)
        {
            if (pointer == objRefs[i].pointer)
            {
                if (type != objRefs[i].type)
                {
                    throw ErrorMessage
                    (
                        "ColladaExporter::getObjectRefId():\n" \
                        "stored objects types mismatch? THIS SHOULD NEVER HAPPEN!"
                    );
                }

                return objRefs[i].id;
            }
        }

        if (false == can_be_created)
        {
            throw ErrorMessage
            (
                "ColladaExporter::getObjectRefId():\n" \
                "object has not been stored yet!"
            );
        }

        /* Adding new element to the list of references */

        if (objRefsCount >= objRefsMaxLength)
        {
            throw ErrorMessage
            (
                "ColladaExporter::getObjectRefId():\n" \
                "too many references!"
            );
        }

        current_id = 0;

        for (i = 0; i < objRefsCount; i++)
        {
            if (type == objRefs[i].type)
            {
                if (current_id != objRefs[i].id)
                {
                    throw ErrorMessage
                    (
                        "ColladaExporter::getObjectRefId():\n" \
                        "invalid stored object ID? THIS SHOULD NEVER HAPPEN!"
                    );
                }

                current_id++;
            }
        }

        objRefs[objRefsCount].id = current_id;
        objRefs[objRefsCount].type = type;
        objRefs[objRefsCount].pointer = pointer;
        objRefsCount++;

        return current_id;
    }


    ////////////////////////////////////////////////////////////////
    // ColladaExporter: check if object was alerady exported
    ////////////////////////////////////////////////////////////////
    bool ColladaExporter::objectRefAlreadyExists(int32_t type, void* pointer)
    {
        int32_t i;

        for (i = 0; i < objRefsCount; i++)
        {
            if (pointer == objRefs[i].pointer)
            {
                if (type != objRefs[i].type)
                {
                    throw ErrorMessage
                    (
                        "ColladaExporter::objectRefAlreadyExists():\n" \
                        "stored objects types mismatch? THIS SHOULD NEVER HAPPEN!"
                    );
                }

                return true;
            }
        }

        return false;
    }


    ////////////////////////////////////////////////////////////////
    // ColladaExporter: get working directory
    ////////////////////////////////////////////////////////////////
    eString ColladaExporter::getWorkingDirectory()
    {
        return workingDirectory;
    }

}
