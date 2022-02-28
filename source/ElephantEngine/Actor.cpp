#include <ElephantEngine/Actor.h>
#include <ElephantBase/Archive.h>

#include <ZookieWizard/WindowsManager.h>
#include <ElephantEngine/Log.h>
#include <ElephantEngine/eTrack.h>

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

    const TypeInfo* Actor::getType() const
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
    // Actor: cloning the object
    ////////////////////////////////////////////////////////////////

    void Actor::createFromOtherObject(const Actor &other)
    {
        script = nullptr;

        scriptPath = other.scriptPath;

        if ((nullptr != other.script) || (other.unknown_04D0.getSize() > 0) || (other.unknown_04DC.getSize() > 0))
        {
            GUI::theWindowsManager.displayMessage
            (
                WINDOWS_MANAGER_MESSAGE_WARNING,
                    "WARNING: You are trying to clone the \"Actor\" object with a precompiled script.\n\n" \
                    "This operation is currently not supported.\n\n" \
                    "The new \"Actor\" will contain an empty \"Namespace\" (no states and no gadgets)." \
            );
        }
    }


    Actor::Actor(const Actor &other)
    : ePivot(other)
    {
        createFromOtherObject(other);
    }

    Actor& Actor::operator = (const Actor &other)
    {
        if ((&other) != this)
        {
            ePivot::operator = (other);

            /****************/

            script->decRef();

            unknown_04D0.clear();

            unknown_04DC.clear();

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* Actor::cloneFromMe() const
    {
        return new Actor(*this);
    }


    ////////////////////////////////////////////////////////////////
    // Actor: serialization
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

            if (ar.isInReadMode() || ((nullptr != script) && (script->canBeExported() ^ (ar.getVersion() >= 0x89))))
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
    void Actor::writeStructureToTextFile(FileOperator &file, int32_t indentation, bool group_written) const
    {
        int32_t a;
        eNode* child_node;
        eString test_str;

        /* "ePivot": parent class */

        ePivot::writeStructureToTextFile(file, indentation, true);

        /* "Actor": additional info */

        ArFunctions::writeIndentation(file, indentation);

        if (!(scriptPath.isEmpty()))
        {
            if ('?' == scriptPath.getText()[0])
            {
                file << " - script (multiline):";
                ArFunctions::writeNewLine(file, 0);
                file << "```";
                ArFunctions::writeNewLine(file, 0);
                file << scriptPath;
                ArFunctions::writeNewLine(file, 0);
                file << "```";
            }
            else
            {
                file << " - script: \"";
                file << scriptPath;
                file << "\"";
            }

            ArFunctions::writeNewLine(file, 0);
        }

        /****************/

        if (!group_written)
        {
            MACRO_KAO2_GROUP_FOREACH_NODE({ child_node->writeStructureToTextFile(file, (indentation + 1), false); })
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
    // Actor: find reference to some node when deleting it
    ////////////////////////////////////////////////////////////////
    void Actor::findAndDereference(eNode* target)
    {
        if (nullptr != script)
        {
            script->removeNoderefsWithSpecifiedLink(target);
        }

        unknown_04DC.findAndDeleteChild(target);
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
    void Actor::exportScripts(const eString &media_dir) const
    {
        FileOperator file;
        eString result;
        char* full_path;

        bool has_question_mark = false;
        bool is_not_empty = false;

        try
        {
            /* Check if script (and path) exists */

            if (!(scriptPath.isEmpty()))
            {
                if ('?' == scriptPath.getText()[0])
                {
                    result += media_dir;
                    result += "scripts/";
                    result += name;
                    result += ".def";

                    has_question_mark = true;
                }
                else if ((nullptr != script) && (script->canBeExported()))
                {
                    result += media_dir;
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
                            "Actor::exportScripts():\n" \
                            "Could not create directory: \"%s\"",
                            full_path
                        );
                    }

                    if (!file.open(full_path, 0))
                    {
                        throw ErrorMessage
                        (
                            "Actor::exportScripts():\n" \
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

        /****************/

        eGroup::exportScripts(media_dir);
    }

}
