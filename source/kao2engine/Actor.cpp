#include <kao2engine/Actor.h>
#include <kao2ar/Archive.h>

#include <kao2engine/Log.h>
#include <kao2engine/eTrack.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Actor interface
    // <kao2.00570D10> (constructor)
    // <kao2.00570F70> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_ACTOR_TYPEINFO
    (
        E_ACTOR_ID,
        "Actor",
        &E_PIVOT_TYPEINFO,
        []() -> eObject*
        {
            return new Actor;
        }
    );

    TypeInfo* Actor::getType() const
    {
        return &E_ACTOR_TYPEINFO;
    }

    Actor::Actor()
    : ePivot()
    {
        /*[0x0114]*/ script = nullptr;
    }

    Actor::~Actor()
    {
        /*[0x0114]*/ script->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // Actor serialization
    // <kao2.00571510>
    ////////////////////////////////////////////////////////////////
    void Actor::serialize(Archive &ar)
    {
        int32_t a;

        ePivot::serialize(ar);

        if (ar.getVersion() >= 0x8B)
        {
            /* "Script" object has empty serialization function */

            a = 0x01;
            ar.readOrWrite(&a, 0x04);
        }
        else
        {
            /* "Namescape" (scripting) */

            if (ar.checkGameEngine(GAME_VERSION_KAO2_PL_PC, GAME_VERSION_KAO2_PL_PC)
                || ar.checkGameEngine(GAME_VERSION_KAO2_EUR_PC, GAME_VERSION_KAO2_EUR_PC))
            {
                ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&script, &E_NAMESPACE_TYPEINFO);
            }
            else
            {
                /* Transition between [PL] and [EUR/USA/STEAM] versions is not supported yet !!! */

                a = 0x01;
                ar.readOrWrite(&a, 0x04);
            }
        }

        /* Script path ("*.def") */

        ar.serializeString(scriptPath);

        if (ar.isInExportScriptsMode())
        {
            if (ar.checkGameEngine(GAME_VERSION_KAO2_PL_PC, (-1)))
            {
                saveMyScript(ar);
            }
        }

        /* Unknown groups (possibly NodeRefs and Gadgets) */

        if (ar.getVersion() >= 0x89)
        {
            unknown_04DC.serialize(ar, &E_NODE_TYPEINFO);

            unknown_04D0.serialize(ar, &E_GADGET_TYPEINFO);
        }
    }


    ////////////////////////////////////////////////////////////////
    // Actor: export readable structure
    ////////////////////////////////////////////////////////////////
    void Actor::writeStructureToTextFile(FileOperator &file, int32_t indentation) const
    {
        int32_t i;
        eNode* test_node;

        char bufor[128];
        eString test_str;
        eTrack* test_track;

        /* "eNode" parent class */

        eNode::writeStructureToTextFile(file, indentation);

        /* "Actor" additional info */

        if (scriptPath.getLength() > 0)
        {
            if ('?' == scriptPath.getText()[0])
            {
                test_str = "<?>";
            }
            else
            {
                test_str = scriptPath;
            }
        }

        sprintf_s
        (
            bufor, 128,
            " - script: \"%s\"",
            test_str.getText()
        );

        ArFunctions::writeIndentation(file, indentation);
        file << bufor;
        ArFunctions::writeNewLine(file, 0);

        /* "ePivot" additional info */

        for (i = 0; i < animations.tracks.getSize(); i++)
        {
            test_track = (eTrack*)animations.tracks.getIthChild(i);
            sprintf_s
            (
                bufor, 128,
                " - track [%d]: \"%s\" [%.2f, %.2f]",
                i,
                test_track->getStringRepresentation().getText(),
                test_track->getStartFrame(),
                test_track->getEndFrame()
            );

            ArFunctions::writeIndentation(file, indentation);
            file << bufor;
            ArFunctions::writeNewLine(file, 0);
        }

        /* "eTransform" parent class */

        sprintf_s
        (
            bufor, 128,
            " - xform pos: (%f, %f, %f)",
            defaultTransform.pos.x,
            defaultTransform.pos.y,
            defaultTransform.pos.z
        );

        ArFunctions::writeIndentation(file, indentation);
        file << bufor;
        ArFunctions::writeNewLine(file, 0);

        sprintf_s
        (
            bufor, 128,
            " - xform rot: (%f, %f, %f, %f)",
            defaultTransform.rot.x,
            defaultTransform.rot.y,
            defaultTransform.rot.z,
            defaultTransform.rot.w
        );

        ArFunctions::writeIndentation(file, indentation);
        file << bufor;
        ArFunctions::writeNewLine(file, 0);

        sprintf_s
        (
            bufor, 128,
            " - xform scl: (%f)",
            defaultTransform.scale
        );

        ArFunctions::writeIndentation(file, indentation);
        file << bufor;
        ArFunctions::writeNewLine(file, 0);

        /* "eGroup" parent class */

        for (i = 0; i < nodes.getSize(); i++)
        {
            test_node = (eNode*)nodes.getIthChild(i);

            if (nullptr != test_node)
            {
                test_node->writeStructureToTextFile(file, (indentation + 1));
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // Actor: destroy before dereferencing
    ////////////////////////////////////////////////////////////////
    void Actor::destroyNode()
    {
        /* Actors could contain references to themselves in NodeRefs */

        unknown_04D0.clear();

        unknown_04DC.clear();

        if (nullptr != script)
        {
            script->decRef();
            script = nullptr;
        }

        ePivot::destroyNode();
    }


    ////////////////////////////////////////////////////////////////
    // Actor: custom TXT parser methods
    ////////////////////////////////////////////////////////////////

    int32_t Actor::parsingSetProperty(char* result_msg, const TxtParsingNodeProp &property)
    {
        int32_t test;

        if (1 != (test = ePivot::parsingSetProperty(result_msg, property)))
        {
            return test;
        }

        if (property.getName().compareExact("script", true))
        {
            if (!property.checkType(TXT_PARSING_NODE_PROPTYPE_STRING))
            {
                TxtParsingNode_ErrorPropType(result_msg, "script", TXT_PARSING_NODE_PROPTYPE_STRING);
                return 2;
            }

            property.getValue(&scriptPath);

            return 0;
        }

        return 1;
    }

    int32_t Actor::parsingCustomMessage(char* result_msg, const eString &message, int32_t params_count, const TxtParsingNodeProp* params)
    {
        int32_t test;

        if (1 != (test = ePivot::parsingCustomMessage(result_msg, message, params_count, params)))
        {
            return test;
        }

        if (message.compareExact("setScript", true))
        {
            if (1 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "setScript", 1);
                return 2;
            }

            /********************************/

            if (!params[0].checkType(TXT_PARSING_NODE_PROPTYPE_STRING))
            {
                TxtParsingNode_ErrorArgType(result_msg, "setScript", 0, TXT_PARSING_NODE_PROPTYPE_STRING);
                return 2;
            }

            params[0].getValue(&scriptPath);

            /********************************/

            unknown_04D0.clear();
            unknown_04DC.clear();

            if (nullptr != script)
            {
                script->decRef();
                script = nullptr;
            }

            return 0;
        }

        return 1;
    }


    ////////////////////////////////////////////////////////////////
    // Actor: save script file
    ////////////////////////////////////////////////////////////////
    void Actor::saveMyScript(Archive &ar) const
    {
        FileOperator file;
        eString result;
        char* full_path;

        bool has_question_mark = false;
        bool is_not_empty = false;

        try
        {
            /* Check if script (and path) exists */

            if (scriptPath.getLength() > 0)
            {
                if ('?' == scriptPath.getText()[0])
                {
                    result += ar.getMediaDir();
                    result += "scripts/";
                    result += name;
                    result += ".def";

                    has_question_mark = true;
                }
                else if (nullptr != script)
                {
                    result += ar.getMediaDir();
                    result += scriptPath;

                    is_not_empty = true;
                }

                if (has_question_mark || is_not_empty)
                {
                    theLog.print(eString(" @ ACTOR \"") + name + "\": EXPORTING \"" + result + "\"\n");

                    full_path = result.getText();

                    file.setDir(full_path);

                    if (!file.createDir())
                    {
                        throw ErrorMessage
                        (
                            "Actor::saveScript():\n" \
                            "Could not create directory: \"%s\"",
                            full_path
                        );
                    }

                    if (!file.open(full_path, 0))
                    {
                        throw ErrorMessage
                        (
                            "Actor::saveScript():\n" \
                            "Could not open file: \"%s\"",
                            full_path
                        );
                    }
                }

                if (has_question_mark)
                {
                    file << scriptPath.getSubstring(1);
                }
                else if (is_not_empty)
                {
                    script->saveStateToTextFile(file, 0);
                }
            }

            /* What if script exporting has failed... */

            if ((!has_question_mark) && (!is_not_empty))
            {
                theLog.print(eString(" @ ACTOR \"") + name + "\" HAS NO SCRIPT...\n");
            }
        }
        catch (ErrorMessage &e)
        {
            e.display();
        }
    }

}
