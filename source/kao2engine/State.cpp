#include <kao2engine/State.h>
#include <kao2ar/Archive.h>

#include <kao2engine/Property.h>
#include <kao2engine/StringSection.h>
#include <kao2engine/VoidInstruction.h>
#include <kao2engine/Gadget.h>
#include <kao2engine/NodeRef.h>
#include <kao2engine/When.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // State interface
    // <kao2.00593A90> (constructor)
    // <kao2.00594270> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_STATE_TYPEINFO
    (
        E_STATE_ID,
        "State",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return new State("", nullptr);
        }
    );

    TypeInfo* State::getType()
    {
        return &E_STATE_TYPEINFO;
    }

    State::State(eString s, State* x)
    : eRefCounter()
    {
        /*[0x08]*/ isDefault = false;
        /*[0x09]*/ isTerminal = false;
        /*[0x0C]*/ name = s;
        /*[0x10]*/ ownerState = x;
        /*[0x20]*/ currentState = nullptr;
        
        /*[0x3C-0x44]*/
        instructions[0] = nullptr;
        instructions[1] = nullptr;
        instructions[2] = nullptr;

        /*[0x70]*/ unknown_70 = (-1);

        newGadgets_count = 0;
        newGadgets_maxLength = 0;
        newGadgets = nullptr;
    }

    State::~State()
    {
        instructions[2]->decRef();
        instructions[1]->decRef();
        instructions[0]->decRef();

        if (nullptr != newGadgets)
        {
            delete[](newGadgets);
        }
    }


    ////////////////////////////////////////////////////////////////
    // New Gadgets structure
    ////////////////////////////////////////////////////////////////

    NewGadgetBase::NewGadgetBase()
    {
        /*[0x04]*/ gadgetType = nullptr;
        /*[0x08]*/ unknown = nullptr;
        /*[0x0C]*/ id = (-1);
    }

    NewGadgetBase::~NewGadgetBase()
    {
        if (nullptr != unknown)
        {
            unknown->decRef();
        }
    }

    void NewGadgetBase::serialize(Archive &ar)
    {
        /* [0x04] Type Info */
        ar.checkTypeInfo(&gadgetType);

        /* [0x00] Gadget name */
        ar.serializeString(name);

        /* [0x08] unknown object */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&unknown, &E_GADGET_TYPEINFO);

        /* [0x0C] unknown id */
        ar.readOrWrite(&id, 0x04);
    }


    ////////////////////////////////////////////////////////////////
    // State serialization
    // <kao2.005951C0>
    ////////////////////////////////////////////////////////////////
    void State::serialize(Archive &ar)
    {
        int32_t i, j;
        Gadget* test_gadget[2];
        eString test_names[2];

        /* [0x08] Is this state a `default state`? */
        ar.readOrWrite(&isDefault, 0x01);

        /* [0x09] unknown */
        if (ar.getVersion() >= 0x7B)
        {
            ar.readOrWrite(&isTerminal, 0x01);
        }
        else
        {
            isTerminal = false;
        }

        /* [0x0C] Actor name or State name */
        ar.serializeString(name);

        /* [0x10] Parent namespace link */
        ar.serialize((eObject**)&ownerState, &E_STATE_TYPEINFO);

        /* [0x14] Collection of inner states */
        subStates.serialize(ar, &E_STATE_TYPEINFO);

        if (ar.getVersion() <= 0x87)
        {
            /* [0x20] Default state link */
            ar.serialize((eObject**)&currentState, &E_STATE_TYPEINFO);
        }

        /* [0x24] Collection of String Sections */
        stringSections.serialize(ar, nullptr);

        /* [0x30] Collection of Properties */
        properties.serialize(ar, nullptr);

        /* [0x3C] Instructions (assumed: "enter", "leave", "update") */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&(instructions[0]), &E_VOIDINSTRUCTION_TYPEINFO);
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&(instructions[1]), &E_VOIDINSTRUCTION_TYPEINFO);
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&(instructions[2]), &E_VOIDINSTRUCTION_TYPEINFO);

        /* [0x48] `when A.B() {...}` blocks */
        whens.serialize(ar, &E_WHEN_TYPEINFO);

        if (ar.getVersion() <= 0x87)
        {
            /* [0x54] `gadget A ("B")` lines */
            gadgets.serialize(ar, &E_GADGET_TYPEINFO);

            if (ar.isInReadMode())
            {
                /* Sanity check: different gadget names */

                for (i = 1; i < gadgets.getSize(); i++)
                {
                    test_gadget[0] = (Gadget*)(gadgets.getIthChild(i));
                    test_names[0] = test_gadget[0]->getStringRepresentation();

                    for (j = 0; j < i; j++)
                    {
                        test_gadget[1] = (Gadget*)(gadgets.getIthChild(j));
                        test_names[1] = test_gadget[1]->getStringRepresentation();

                        if (test_names[0].compare(test_names[1], 0, 0, true))
                        {
                            try
                            {
                                throw ErrorMessage
                                (
                                    "State::serialize():\n" \
                                    "duplicate gadget names!\n" \
                                    " - \"%s\" [%s]\n" \
                                    " - \"%s\" [%s]\n" \
                                    "(state: \"%s\")",
                                    test_names[0].getText(), test_gadget[0]->getType()->name,
                                    test_names[1].getText(), test_gadget[1]->getType()->name,
                                    name.getText()
                                );
                            }
                            catch (ErrorMessage &e)
                            {
                                e.display();
                            }
                        }
                    }
                }
            }
        }

        /* [0x60] `node A ("B")` lines */
        nodeRefs.serialize(ar, &E_NODEREF_TYPEINFO);

        /* [0x6C/0x60] Animation name (if exists) */
        ar.serializeString(anim);

        /* [0x70/0x64] unknown */
        ar.readOrWrite(&unknown_70, 0x04);

        /* [0x74/0x68] unknown */
        ar.serializeString(unknown_74);

        if (ar.getVersion() >= 0x89)
        {
            /* [0x78] unknown */
            ar.readOrWrite(&unknown_78, 0x04);

            /* [0x20] Default state with reference */
            ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&currentState, &E_STATE_TYPEINFO);

            /* [0x6C-0x74] new gadgets group */

            if (ar.isInReadMode())
            {
                if (nullptr != newGadgets)
                {
                    delete[](newGadgets);
                    newGadgets = nullptr;

                    newGadgets_maxLength = 0;
                    newGadgets_count = 0;
                }

                ar.readOrWrite(&newGadgets_maxLength, 0x04);

                newGadgets = new NewGadgetBase [newGadgets_maxLength];

                for (i = 0; i < newGadgets_maxLength; i++)
                {
                    newGadgets[i].serialize(ar);

                    newGadgets_count = (i+1);
                }
            }
            else
            {
                ar.readOrWrite(&newGadgets_count, 0x04);

                for (i = 0; i < newGadgets_count; i++)
                {
                    newGadgets[i].serialize(ar);
                }
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // State: get name
    ////////////////////////////////////////////////////////////////
    eString State::getStringRepresentation()
    {
        return name;
    }


    ////////////////////////////////////////////////////////////////
    // State: write it down, line by line... ;)
    ////////////////////////////////////////////////////////////////
    void State::saveStateToTextFile(FileOperator &file, int32_t indentation)
    {
        /********************************/
        /* Preparations before text generation */
        
        int32_t i = 0;
        int32_t j = 0;
        bool has_empty_body = true;
        bool found_gadget_name = false;
        bool written_any_property = false;
        bool* written_properties = nullptr;
        
        const char* instruction_block_names[3] =
        {
            "enter",
            "update",
            "leave"
        };

        StringSection* test_section = nullptr;
        Gadget* test_gadget = nullptr;
        Property* test_prop = nullptr;
        NodeRef* test_noderef = nullptr;
        State* test_state = nullptr;
        When* test_when = nullptr;

        j = properties.getSize();
        
        try
        {
            written_properties = new bool [j];
        }
        catch (std::bad_alloc)
        {
            written_properties = nullptr;
        }

        if (nullptr != written_properties)
        {
            std::memset(written_properties, false, j);
        }

        /********************************/
        /* Opening statement */

        if (nullptr == ownerState)
        {
            file << "actor ";
        }
        else
        {
            if (isTerminal)
            {
                file << "terminal ";
            }

            if (isDefault)
            {
                file << "default ";
            }

            file << "state ";
        }

        file << name;

        if (anim.getLength() > 0)
        {
            file << " (\"";
            file << anim;
            file << "\")";
        }

        ArFunctions::writeNewLine(file, indentation);

        file << "{";
        indentation++;

        /********************************/
        /* String sections */
        /* (each `StringSection`: auto new line at the beginning) */
        
        for (i = 0; i < stringSections.getSize(); i++)
        {
            test_section = (StringSection*)stringSections.getIthChild(i);

            if (nullptr != test_section)
            {
                found_gadget_name = false;

                for (j = 0; (j < gadgets.getSize()) && (false == found_gadget_name); j++)
                {
                    test_gadget = (Gadget*)gadgets.getIthChild(j);

                    if (nullptr != test_gadget)
                    {
                        found_gadget_name = test_gadget->getStringRepresentation().compare(test_section->getStringRepresentation(), 0, 0, true);
                    }
                }

                if (false == found_gadget_name)
                {
                    has_empty_body = false;

                    test_section->saveSectionToTextFile(file, indentation);
            
                    ArFunctions::writeNewLine(file, 0);
                }
            }
        }

        /********************************/
        /* Gadgets and their properties */

        for (i = 0; i < gadgets.getSize(); i++)
        {
            test_gadget = (Gadget*)gadgets.getIthChild(i);

            if (nullptr != test_gadget)
            {
                has_empty_body = false;

                ArFunctions::writeNewLine(file, indentation);

                file << test_gadget->generateScriptText();

                indentation++;

                for (j = 0; j < properties.getSize(); j++)
                {
                    test_prop = (Property*)properties.getIthChild(j);

                    if (nullptr != test_prop)
                    {
                        if (test_prop->compareGadgets(test_gadget))
                        {
                            written_properties[j] = true;

                            ArFunctions::writeNewLine(file, indentation);

                            file << test_prop->generateScriptText();
                        }
                    }
                }

                found_gadget_name = false;

                for (j = 0; (j < stringSections.getSize()) && (false == found_gadget_name); j++)
                {
                    test_section = (StringSection*)stringSections.getIthChild(j);

                    if (nullptr != test_section)
                    {
                        found_gadget_name = test_gadget->getStringRepresentation().compare(test_section->getStringRepresentation(), 0, 0, true);
                    }
                }

                if (true == found_gadget_name)
                {
                    test_section->saveSectionToTextFile(file, indentation);
                }

                indentation--;
                ArFunctions::writeNewLine(file, 0);
            }
        }

        /********************************/
        /* Properties that have not been written */

        for (i = 0; i < properties.getSize(); i++)
        {
            test_prop = (Property*)properties.getIthChild(i);

            if (nullptr != test_prop)
            {
                if (false == written_properties[i])
                {
                    has_empty_body = false;
                    written_any_property = true;

                    ArFunctions::writeNewLine(file, indentation);

                    file << test_prop->generateScriptText();
                }
            }
        }

        if (true == written_any_property)
        {
            ArFunctions::writeNewLine(file, 0);
        }

        if (nullptr != written_properties)
        {
            delete[](written_properties);
        }

        /********************************/
        /* Node References */

        for (i = 0; i < nodeRefs.getSize(); i++)
        {
            test_noderef = (NodeRef*)nodeRefs.getIthChild(i);

            if (nullptr != test_noderef)
            {
                has_empty_body = false;

                ArFunctions::writeNewLine(file, indentation);

                file << test_noderef->generateScriptText();

                ArFunctions::writeNewLine(file, 0);
            }
        }

        /********************************/
        /* Instructions */
        /* (each `VoidInstruction`: auto new line at the beginning) */

        for (i = 0; i < 3; i++)
        {
            if (nullptr != instructions[i])
            {
                has_empty_body = false;

                ArFunctions::writeNewLine(file, indentation);

                file << instruction_block_names[i];

                indentation++;

                instructions[i]->saveInstructionToTextFile(file, indentation);

                indentation--;

                ArFunctions::writeNewLine(file, 0);
            }
        }

        /********************************/
        /* Children States */
        /* (each `State`: auto new line at the end) */

        for (i = 0; i < subStates.getSize(); i++)
        {
            ArFunctions::writeNewLine(file, indentation);

            test_state = (State*)subStates.getIthChild(i);
            
            if (nullptr != test_state)
            {
                has_empty_body = false;

                test_state->saveStateToTextFile(file, indentation);
            }
        }

        /********************************/
        /* Whens */
        /* (each `When`: auto new line at the beginning) */

        for (i = 0; i < whens.getSize(); i++)
        {
            test_when = (When*)whens.getIthChild(i);

            if (nullptr != test_when)
            {
                has_empty_body = false;

                test_when->saveWhenToTextFile(file, indentation);

                ArFunctions::writeNewLine(file, 0);
            }
        }

        /********************************/
        /* Closing statement */

        if (false == has_empty_body)
        {
            indentation--;

            ArFunctions::writeIndentation(file, indentation);
        }

        file << "}";

        ArFunctions::writeNewLine(file, 0);
    }


    ////////////////////////////////////////////////////////////////
    // State: print
    ////////////////////////////////////////////////////////////////
    eString State::getLogPrintMessage()
    {
        eString result = eObject::getLogPrintMessage();

        result += "\n - \"";
        result += name;
        result += "\"";

        if (anim.getLength() > 0)
        {
            result += " (\"";
            result += anim;
            result += "\")";
        }

        return result;
    }


    ////////////////////////////////////////////////////////////////
    // State: get owner (used with "ShiftInstruction")
    ////////////////////////////////////////////////////////////////
    State* State::getOwner()
    {
        return ownerState;
    }

}
