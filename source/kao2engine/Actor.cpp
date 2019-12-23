#include <kao2engine/Actor.h>
#include <kao2ar/Archive.h>

#include <kao2engine/Log.h>

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

    TypeInfo* Actor::getType()
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
    // Actor: save script file
    ////////////////////////////////////////////////////////////////
    void Actor::saveMyScript(Archive &ar)
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
