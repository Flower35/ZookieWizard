#include <kao2ar/ArCustomParser.h>

#include <kao2engine/eNode.h>
#include <kao2engine/eGroup.h>
#include <kao2engine/eScene.h>
#include <kao2engine/NodeRefLinker.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ArCustomPraser: definitions
    ////////////////////////////////////////////////////////////////

    #define AR_CUSTOM_PARSER_STATUS_OK 0
    #define AR_CUSTOM_PARSER_STATUS_EOF 1
    #define AR_CUSTOM_PARSER_STATUS_INVCHAR 2
    #define AR_CUSTOM_PARSER_STATUS_UNEXP 3
    #define AR_CUSTOM_PARSER_STATUS_TOOMANY 4

    #define AR_CUSTOM_PARSER_NAME_MAXLENGTH 32
    #define AR_CUSTOM_PARSER_STRING_MAXLENGTH 512


    ////////////////////////////////////////////////////////////////
    // ArCustomParserNoderef: constructor
    ////////////////////////////////////////////////////////////////
    ArCustomParserNoderef::ArCustomParserNoderef()
    {
        reference = nullptr;
    }


    ////////////////////////////////////////////////////////////////
    // ArCustomParserNoderef: setting values
    ////////////////////////////////////////////////////////////////
    void ArCustomParserNoderef::set(eNode* new_reference, eString new_name)
    {
        reference = new_reference;
        name = new_name;
    }


    ////////////////////////////////////////////////////////////////
    // ArCustomParserNoderef: retrieving values
    ////////////////////////////////////////////////////////////////

    eString ArCustomParserNoderef::getName() const
    {
        return name;
    }

    eNode* ArCustomParserNoderef::getReference() const
    {
        return reference;
    }


    ////////////////////////////////////////////////////////////////
    // ArCustomParser: constructor
    ////////////////////////////////////////////////////////////////
    ArCustomParser::ArCustomParser()
    {
        lineNumber = 1;
        characterPosition = 1;
        currentIndentation = 0;

        textBufor = nullptr;

        lastPropType = (-1);
        lastNoderef = nullptr;
        validFloats = 0;

        defaultParent = nullptr;
        lastNode = nullptr;

        noderefsCount = 0;
        noderefs = nullptr;

        propsCount = 0;
        propsMaxLength = 0;
        props = nullptr;
    }


    ////////////////////////////////////////////////////////////////
    // ArCustomParser: destructor
    ////////////////////////////////////////////////////////////////
    ArCustomParser::~ArCustomParser()
    {
        if (nullptr != textBufor)
        {
            delete[](textBufor);
        }

        if (nullptr != noderefs)
        {
            delete[](noderefs);
        }

        if (nullptr != props)
        {
            delete[](props);
        }
    }


    ////////////////////////////////////////////////////////////////
    // ArCustomParser: inserting new property
    ////////////////////////////////////////////////////////////////
    void ArCustomParser::insertNewProp(TxtParsingNodeProp* new_prop)
    {
        TxtParsingNodeProp* temp;
        char bufor[LARGE_BUFFER_SIZE];
        int32_t a;

        if (nullptr == new_prop)
        {
            return;
        }

        eString new_name = new_prop->getName();

        if (new_name.getLength() > 0)
        {
            for (a = 0; a < propsCount; a++)
            {
                if (props[a].getName().compareExact(new_name, false))
                {
                    sprintf_s(bufor, LARGE_BUFFER_SIZE, "Duplicate property \"%s\" found.", new_name.getText());

                    throwError(AR_CUSTOM_PARSER_STATUS_OK, "An error occurred while parsing \"eNode\" properties!", bufor);
                }
            }
        }

        if ((propsCount + 1) > propsMaxLength)
        {
            temp = new TxtParsingNodeProp [propsMaxLength + 1];

            if (nullptr != props)
            {
                for (a = 0; a < propsCount; a++)
                {
                    temp[a] = props[a];
                }

                delete[](props);
            }

            props = temp;
            propsMaxLength++;
        }

        props[propsCount] = (*new_prop);
        propsCount++;
    }


    ////////////////////////////////////////////////////////////////
    // ArCustomParser: inserting new noderef with its identifier
    ////////////////////////////////////////////////////////////////
    void ArCustomParser::insertNewNoderef(eNode* new_reference, eString new_name)
    {
        ArCustomParserNoderef* temp;
        char bufor[LARGE_BUFFER_SIZE];
        int32_t a;

        if (new_name.getLength() > 0)
        {
            for (a = 0; a < noderefsCount; a++)
            {
                if (noderefs[a].getName().compareExact(new_name, false))
                {
                    sprintf_s(bufor, LARGE_BUFFER_SIZE, "Duplicate identifier \"%s\" found.", new_name.getText());

                    throwError(AR_CUSTOM_PARSER_STATUS_OK, "An error occurred while parsing NodeRef!", bufor);
                }
            }
        }

        if (nullptr == new_reference)
        {
            throwError(AR_CUSTOM_PARSER_STATUS_OK, "An error occurred while parsing NodeRef!", "\"eNode\" pointer is not assigned.");
        }

        temp = new ArCustomParserNoderef [noderefsCount + 1];

        if (nullptr != noderefs)
        {
            for (a = 0; a < noderefsCount; a++)
            {
                temp[a] = noderefs[a];
            }

            delete[](noderefs);
        }

        noderefs = temp;

        noderefs[noderefsCount].set(new_reference, new_name);
        noderefsCount++;
    }


    ////////////////////////////////////////////////////////////////
    // ArCustomParser: open source file
    ////////////////////////////////////////////////////////////////
    bool ArCustomParser::openFile(eString filename, eGroup* current_parent)
    {
        const char* text = filename.getText();

        if ((nullptr != current_parent) && current_parent->getType()->checkHierarchy(&E_GROUP_TYPEINFO))
        {
            defaultParent = current_parent;
        }

        if (!sourceFile.open(text, (FILE_OPERATOR_MODE_READ | FILE_OPERATOR_MODE_BINARY)))
        {
            throw ErrorMessage
            (
                "ArCustomParser::openFile():\n" \
                "Could not open file: \"%s\"",
                text
            );

            return false;
        }

        return true;
    }


    ////////////////////////////////////////////////////////////////
    // ArCustomParser: main parsing function
    ////////////////////////////////////////////////////////////////
    int32_t ArCustomParser::beginParsing()
    {
        int32_t successful_messages = 0;
        int32_t test[2];
        eString dummy_str[2];
        char bufor[2][LARGE_BUFFER_SIZE];

        TypeInfo* dummy_typeinfo;
        eNode* root_node = ArFunctions::getCurrentScene();
        eNode* dummy_node;
        eGroup* dummy_parent[2];

        char dummy_char;
        bool continue_with_props;
        TxtParsingNodeProp dummy_prop;
        NodeRefLinker noderefinker;

        try
        {
            while (!sourceFile.endOfFileReached())
            {
                if (AR_CUSTOM_PARSER_STATUS_OK != (test[0] = expectName()))
                {
                    if (AR_CUSTOM_PARSER_STATUS_EOF != test[0])
                    {
                        throwError(test[0], "Error while parsing a keyword", nullptr);
                    }
                }
                else
                {
                    if (lastName.compareExact("FindNode", true))
                    {
                        /********************************/
                        /* "FindNode": (1) type and name */

                        parseTypeInfoAndIdentifier(false, "FindNode", dummy_typeinfo, dummy_str[0]);

                        /********************************/
                        /* "FindNode": (2) linker text */

                        if (AR_CUSTOM_PARSER_STATUS_OK != (test[0] = expectChar('(')))
                        {
                            throwError(test[0], "\"FindNode\": error while reading linker text", "Expected `(`.");
                        }

                        if (AR_CUSTOM_PARSER_STATUS_OK != (test[0] = expectString()))
                        {
                            throwError(test[0], "\"FindNode\": error while reading linker text", nullptr);
                        }

                        if (AR_CUSTOM_PARSER_STATUS_OK != (test[0] = expectChar(')')))
                        {
                            throwError(test[0], "\"FindNode\": error while reading linker text", "Expected `)`.");
                        }

                        dummy_str[1] = lastString;

                        /********************************/
                        /* "FindNode": (3) linking and storing noderef */

                        dummy_node = noderefinker.findLink
                        (
                            root_node,
                            (nullptr != defaultParent) ? defaultParent : root_node,
                            "FindNode_link",
                            dummy_str[1],
                            dummy_typeinfo
                        );

                        insertNewNoderef(dummy_node, dummy_str[0]);

                        /********************************/
                        /* "FindNode": finished */

                        successful_messages++;
                    }
                    else if (lastName.compareExact("AddNode", true))
                    {
                        /********************************/
                        /* "AddNode": (1) type and name */

                        parseTypeInfoAndIdentifier(true, "AddNode", dummy_typeinfo, dummy_str[0]);

                        /********************************/
                        /* "AddNode": (2) begin checking properties */

                        if (AR_CUSTOM_PARSER_STATUS_OK != (test[0] = expectChar('(')))
                        {
                            throwError(test[0], "\"AddNode\": error while reading properties", "Expected `(`.");
                        }

                        propsCount = 0;
                        continue_with_props = true;

                        sprintf_s(bufor[1] , LARGE_BUFFER_SIZE, "Unknown error...");

                        while (continue_with_props)
                        {
                            if (AR_CUSTOM_PARSER_STATUS_OK != (test[0] = skipUntilNotEmpty()))
                            {
                                throwError(test[0], "\"AddNode\": error while reading properties", nullptr);
                            }

                            if (sourceFile.peek(dummy_char))
                            {
                                if (')' == dummy_char)
                                {
                                    characterPosition++;
                                    sourceFile.skip(+1);

                                    continue_with_props = false;
                                }
                                else
                                {
                                    if (AR_CUSTOM_PARSER_STATUS_OK != (test[0] = expectFullProperty("AddNode", &dummy_prop)))
                                    {
                                        throwError(test[0], "\"AddNode\": error while reading properties", nullptr);
                                    }

                                    insertNewProp(&dummy_prop);
                                }
                            }
                            else
                            {
                                throwError(AR_CUSTOM_PARSER_STATUS_EOF, "\"AddNode\": error while reading properties", nullptr);
                            }
                        }

                        /********************************/
                        /* "AddNode": (3) creating object and using all found properties */

                        dummy_node = (eNode*)dummy_typeinfo->create();

                        if (nullptr == dummy_node)
                        {
                            sprintf_s(bufor[0], LARGE_BUFFER_SIZE, "Class \"%s\" is abstract.", dummy_typeinfo->name);

                            throwError(AR_CUSTOM_PARSER_STATUS_OK, "\"AddNode\": error while creating new node", bufor[0]);
                        }

                        dummy_node->incRef();

                        if (nullptr != defaultParent)
                        {
                            defaultParent->appendChild(dummy_node);
                        }

                        for (int32_t a = 0; a < propsCount; a++)
                        {
                            if (0 != (test[0] = dummy_node->parsingSetProperty(bufor[1], props[a])))
                            {
                                dummy_node->decRef();

                                if (1 == test[0])
                                {
                                    sprintf_s(bufor[0], LARGE_BUFFER_SIZE, "\"%s\": Unrecognized property \"%s\".", dummy_typeinfo->name, props[a].getName().getText());
                                }
                                else
                                {
                                    sprintf_s(bufor[0], LARGE_BUFFER_SIZE, "\"%s\": %s", dummy_typeinfo->name, bufor[1]);
                                }

                                throwError(AR_CUSTOM_PARSER_STATUS_OK, "\"AddNode\": error while assigning property", bufor[0]);
                            }
                        }

                        dummy_parent[0] = dummy_node->getParentNode();

                        dummy_node->decRef();

                        if (nullptr == dummy_parent[0])
                        {
                            throwError(AR_CUSTOM_PARSER_STATUS_OK, "\"AddNode\": error while creating new node", "No default parent selected. (parsing from node that is not \"eGroup\" or its child)");
                        }

                        dummy_node->editingNewNodeSetup();

                        /********************************/
                        /* "AddNode": (4) store noderef if the identifier was not empty */

                        if (dummy_str[0].getLength() > 0)
                        {
                            insertNewNoderef(dummy_node, dummy_str[0]);
                        }

                        /********************************/
                        /* "AddNode": finished */

                        successful_messages++;
                    }
                    else if (lastName.compareExact("NodeMsg", true))
                    {
                        /********************************/
                        /* "NodeMsg": (1) identifier name */

                        if (AR_CUSTOM_PARSER_STATUS_OK != (test[0] = expectName()))
                        {
                            throwError(test[0], "\"NodeMsg\": error while reading node identifier", nullptr);
                        }

                        if (lastName.getLength() <= 0)
                        {
                            throwError(AR_CUSTOM_PARSER_STATUS_OK, "\"NodeMsg\": no node identifier defined", nullptr);
                        }

                        dummy_node = findNodeByIdentifier("NodeMsg");

                        dummy_typeinfo = dummy_node->getType();

                        /********************************/
                        /* "NodeMsg": (2) message */

                        if (AR_CUSTOM_PARSER_STATUS_OK != (test[0] = expectName()))
                        {
                            throwError(test[0], "\"NodeMsg\": error while reading message", nullptr);
                        }

                        if (lastName.getLength() <= 0)
                        {
                            throwError(AR_CUSTOM_PARSER_STATUS_OK, "\"NodeMsg\": no message defined", nullptr);
                        }

                        dummy_str[0] = lastName;

                        /********************************/
                        /* "NodeMsg": (3) begin checking arguments */

                        if (AR_CUSTOM_PARSER_STATUS_OK != (test[0] = expectChar('(')))
                        {
                            throwError(test[0], "\"NodeMsg\": error while reading arguments", "Expected `(`.");
                        }

                        propsCount = 0;
                        continue_with_props = true;

                        sprintf_s(bufor[1] , LARGE_BUFFER_SIZE, "Unknown error...");

                        while (continue_with_props)
                        {
                            if (AR_CUSTOM_PARSER_STATUS_OK != (test[0] = skipUntilNotEmpty()))
                            {
                                throwError(test[0], "\"NodeMsg\": error while reading arguments", nullptr);
                            }

                            if (sourceFile.peek(dummy_char))
                            {
                                if (')' == dummy_char)
                                {
                                    characterPosition++;
                                    sourceFile.skip(+1);

                                    continue_with_props = false;
                                }
                                else
                                {
                                    dummy_prop.setName(eString(-1));

                                    if (AR_CUSTOM_PARSER_STATUS_OK != (test[0] = expectProperty("NodeMsg", &dummy_prop)))
                                    {
                                        throwError(test[0], "\"NodeMsg\": error while reading arguments", nullptr);
                                    }

                                    insertNewProp(&dummy_prop);
                                }
                            }
                            else
                            {
                                throwError(AR_CUSTOM_PARSER_STATUS_EOF, "\"NodeMsg\": error while reading arguments", nullptr);
                            }
                        }

                        /********************************/
                        /* "NodeMsg": (4) sending a message with all collected arguments */

                        if (0 != (test[0] = dummy_node->parsingCustomMessage(bufor[1], dummy_str[0], propsCount, props)))
                        {
                            if (1 == test[0])
                            {
                                sprintf_s(bufor[0], LARGE_BUFFER_SIZE, "\"%s\": Unrecognized message \"%s\".", dummy_typeinfo->name, dummy_str[0].getText());
                            }
                            else
                            {
                                sprintf_s(bufor[0], LARGE_BUFFER_SIZE, "\"%s\": %s", dummy_typeinfo->name, bufor[1]);
                            }

                            throwError(AR_CUSTOM_PARSER_STATUS_OK, "\"NodeMsg\": error while sending a custom message", bufor[0]);
                        }

                        /********************************/
                        /* "NodeMsg": finished */

                        successful_messages++;
                    }
                    else if (lastName.compareExact("NodeSetCollision", true))
                    {
                        /********************************/
                        /* "NodeSetCollision": (1) identifier name */

                        if (AR_CUSTOM_PARSER_STATUS_OK != (test[0] = expectName()))
                        {
                            throwError(test[0], "\"NodeSetCollision\": error while reading node identifier", nullptr);
                        }

                        if (lastName.getLength() <= 0)
                        {
                            throwError(AR_CUSTOM_PARSER_STATUS_OK, "\"NodeSetCollision\": no node identifier defined", nullptr);
                        }

                        dummy_node = findNodeByIdentifier("NodeSetCollision");

                        /********************************/
                        /* "NodeSetCollision": (2) desired state - number in brackets */

                        if (AR_CUSTOM_PARSER_STATUS_OK != (test[0] = expectChar('(')))
                        {
                            throwError(test[0], "\"NodeSetCollision\": error while reading collision state", "Expected `(`.");
                        }

                        if (AR_CUSTOM_PARSER_STATUS_OK != (test[0] = skipUntilNotEmpty()))
                        {
                            throwError(test[0], "\"NodeSetCollision\": error while reading collision state", nullptr);
                        }

                        if (sourceFile.peek(dummy_char))
                        {
                            if ('1' == dummy_char)
                            {
                                test[1] = 1;
                            }
                            else if ('0' == dummy_char)
                            {
                                test[1] = 0;
                            }
                            else
                            {
                                throwError(AR_CUSTOM_PARSER_STATUS_OK, "\"NodeSetCollision\": error while reading collision state", "Expected `0` or `1`.");
                            }

                            characterPosition++;
                            sourceFile.skip(+1);
                        }
                        else
                        {
                            throwError(AR_CUSTOM_PARSER_STATUS_EOF, "\"NodeSetCollision\": error while reading collision state", nullptr);
                        }

                        if (AR_CUSTOM_PARSER_STATUS_OK != (test[0] = expectChar(')')))
                        {
                            throwError(test[0], "\"NodeSetCollision\": error while reading collision state", "Expected `)`.");
                        }

                        /********************************/
                        /* "NodeSetCollision": (3) rebuilding or clearing collision */

                        if (0 != test[1])
                        {
                            dummy_node->editingRebuildCollision();
                        }
                        else
                        {
                            dummy_node->editingClearCollision();
                        }

                        /********************************/
                        /* "NodeSetCollision": finished */

                        successful_messages++;
                    }
                    else if (lastName.compareExact("RemoveNode", true))
                    {
                        /********************************/
                        /* "RemoveNode": (1) identifier name */

                        if (AR_CUSTOM_PARSER_STATUS_OK != (test[0] = expectName()))
                        {
                            throwError(test[0], "\"RemoveNode\": error while reading node identifier", nullptr);
                        }

                        if (lastName.getLength() <= 0)
                        {
                            throwError(AR_CUSTOM_PARSER_STATUS_OK, "\"RemoveNode\": no node identifier defined", nullptr);
                        }

                        dummy_node = findNodeByIdentifier("RemoveNode");

                        /********************************/
                        /* "RemoveNode": (2) checking parent and dereferencing node */

                        dummy_parent[0] = dummy_node->getParentNode();

                        if (nullptr == dummy_parent[0])
                        {
                            sprintf_s(bufor[0], LARGE_BUFFER_SIZE, "\"RemoveNode\": node \"%s\" has no parent", lastName.getText());
                            throwError(AR_CUSTOM_PARSER_STATUS_OK, bufor[0], nullptr);
                        }

                        if (dummy_node->getReferenceCount() >= 2)
                        {
                            if (nullptr != (dummy_parent[1] = dummy_parent[0]->getRootNode()))
                            {
                                dummy_parent[1]->findAndDereference(dummy_node);
                            }
                        }

                        dummy_parent[0]->findAndDeleteChild(dummy_node);

                        /********************************/
                        /* "RemoveNode": finished */

                        successful_messages++;
                    }
                    else
                    {
                        throwError(AR_CUSTOM_PARSER_STATUS_OK, "Unrecognized keyword", lastName.getText());
                    }
                }
            }
        }
        catch (ErrorMessage &err)
        {
            err.display();

            return (-1);
        }

        return successful_messages;
    }


    ////////////////////////////////////////////////////////////////
    // ArCustomParser: parsing macro for "FindNode" and "AddNode"
    ////////////////////////////////////////////////////////////////
    void ArCustomParser::parseTypeInfoAndIdentifier(bool can_name_be_empty, const char* current_msg, TypeInfo* &returned_type, eString &returned_name)
    {
        int32_t test;
        char bufor[2][LARGE_BUFFER_SIZE];

        /********************************/
        /* (1) class type */

        if (AR_CUSTOM_PARSER_STATUS_OK != (test = expectName()))
        {
            sprintf_s(bufor[0], LARGE_BUFFER_SIZE, "\"%s\": error while reading class type", current_msg);

            throwError(test, bufor[0], nullptr);
        }

        if (lastName.getLength() > 0)
        {
            try
            {
                returned_type = InterfaceManager.getTypeInfo(lastName.getText());
            }
            catch (ErrorMessage)
            {
                sprintf_s(bufor[0], LARGE_BUFFER_SIZE, "\"%s\": error while reading class type", current_msg);
                sprintf_s(bufor[1], LARGE_BUFFER_SIZE, "TypeInfo for name \"%s\" not found!", lastName.getText());

                throwError(AR_CUSTOM_PARSER_STATUS_OK, bufor[0], bufor[1]);
            }

            if ((nullptr == returned_type) || !returned_type->checkHierarchy(&E_NODE_TYPEINFO))
            {
                sprintf_s(bufor[0], LARGE_BUFFER_SIZE, "\"%s\": class type is not a child of \"eNode\"", current_msg);
                sprintf_s(bufor[1], LARGE_BUFFER_SIZE, "\"%s\"", lastName.getText());

                throwError(AR_CUSTOM_PARSER_STATUS_OK, bufor[0], bufor[1]);
            }
        }
        else
        {
            sprintf_s(bufor[0], LARGE_BUFFER_SIZE, "\"%s\": no class type defined", current_msg);

            throwError(AR_CUSTOM_PARSER_STATUS_OK, bufor[0], nullptr);
        }

        /********************************/
        /* (2) noderef name */

        if (AR_CUSTOM_PARSER_STATUS_OK != (test = expectName()))
        {
            sprintf_s(bufor[0], LARGE_BUFFER_SIZE, "\"%s\": error while reading node identifier", current_msg);

            throwError(test, bufor[0], nullptr);
        }

        if ((!can_name_be_empty) && (lastName.getLength() <= 0))
        {
            sprintf_s(bufor[0], LARGE_BUFFER_SIZE, "\"%s\": no node identifier defined", current_msg);

            throwError(AR_CUSTOM_PARSER_STATUS_OK, bufor[0], nullptr);
        }

        returned_name = lastName;
    }


    ////////////////////////////////////////////////////////////////
    // ArCustomParser: throwing an error message
    ////////////////////////////////////////////////////////////////
    void ArCustomParser::throwError(int32_t status, const char* main_message, const char* param1) const
    {
        const char* reason;
        char result[2 * LARGE_BUFFER_SIZE];

        switch (status)
        {
            case AR_CUSTOM_PARSER_STATUS_EOF:
            {
                reason = "End of file reached.";
                break;
            }

            case AR_CUSTOM_PARSER_STATUS_INVCHAR:
            {
                reason = "Invalid character found in the text file.";
                break;
            }

            case AR_CUSTOM_PARSER_STATUS_UNEXP:
            {
                reason = "Unexpected character found.";
                break;
            }

            case AR_CUSTOM_PARSER_STATUS_TOOMANY:
            {
                reason = "Exceeded reserved size for a string buffer.";
                break;
            }

            default:
            {
                reason = nullptr;
            }
        }

        if ((nullptr == main_message) || (std::strlen(main_message) <= 0))
        {
            main_message = "An unexpected error has occured while parsing the text file";
        }

        if ((nullptr == param1) || (std::strlen(param1) <= 0))
        {
            param1 = nullptr;
        }

        sprintf_s
        (
            result, 2 * LARGE_BUFFER_SIZE,
            "%s!%s%s%s%s\n\n(line %d, position %d)",
            main_message,
            (nullptr != reason) ? "\n\nREASON: " : "",
            (nullptr != reason) ? reason : "",
            (nullptr != param1) ? "\n\n" : "",
            (nullptr != param1) ? param1 : "",
            lineNumber, characterPosition
        );

        throw ErrorMessage(result);
    }


    ////////////////////////////////////////////////////////////////
    // ArCustomParser: skip whitespace or comments
    // until some text that makes sense is found
    ////////////////////////////////////////////////////////////////
    int32_t ArCustomParser::skipUntilNotEmpty()
    {
        char last[2] = {'\0', '\0'};
        char current;

        bool erase_current = false;
        bool line_comment = false;
        bool block_comment = false;
        bool regular_string = false;
        bool block_string = false;

        while (!sourceFile.endOfFileReached())
        {
            if (sourceFile.peek(current))
            {
                if ((!line_comment) && (!block_comment))
                {
                    if ('/' == last[0])
                    {
                        if ('/' == current)
                        {
                            line_comment = true;
                        }
                        else if ('*' == current)
                        {
                            block_comment = true;
                            erase_current = true;
                        }
                        else
                        {
                            return AR_CUSTOM_PARSER_STATUS_INVCHAR;
                        }
                    }
                    else if (('\t' != current) && ('\n' != current) && ('\r' != current))
                    {
                        if (current < ' ')
                        {
                            return AR_CUSTOM_PARSER_STATUS_INVCHAR;
                        }
                        else if ((' ' != current) && ('/' != current))
                        {
                            return AR_CUSTOM_PARSER_STATUS_OK;
                        }
                    }
                }
                else if (block_comment)
                {
                    if ((!block_string) && (!regular_string) && ('*' == last[0]) && ('/' == current))
                    {
                        block_comment = false;
                        erase_current = true;
                    }
                    else if (('`' == last[1]) && ('`' == last[0]) && ('`' == current))
                    {
                        block_string = !block_string;
                        erase_current = true;
                    }
                    else if ('"' == current)
                    {
                        regular_string = !regular_string;
                    }
                    else if ((current < ' ') && (current >= 0) && ('\t' != current) && ('\n' != current) && ('\r' != current))
                    {
                        return AR_CUSTOM_PARSER_STATUS_INVCHAR;
                    }
                }

                if ((current < ' ') && (current >= 0))
                {
                    if ('\n' == current)
                    {
                        regular_string = false;
                        line_comment = false;

                        lineNumber++;
                        characterPosition = 0;
                        currentIndentation = (-1);
                    }
                    else if ('\t' == current)
                    {
                        currentIndentation += 3;
                    }
                    else if ('\r' != current)
                    {
                        return AR_CUSTOM_PARSER_STATUS_INVCHAR;
                    }
                }

                last[1] = last[0];

                if (erase_current)
                {
                    last[0] = '\0';
                    erase_current =  false;
                }
                else
                {
                    last[0] = current;
                }

                sourceFile.skip(+1);
                characterPosition++;
                currentIndentation++;
            }
        }

        return AR_CUSTOM_PARSER_STATUS_EOF;
    }


    ////////////////////////////////////////////////////////////////
    // ArCustomParser: validating identifier name
    // (returns 1 if character is valid)
    // (returns 0 if identifier ends)
    // (otherwise returns 2)
    ////////////////////////////////////////////////////////////////
    int32_t ArCustomParser::validatingIdentifierName(bool is_first, char x) const
    {
        if (((!is_first) && (x >= '0') && (x <= '9')) || ((x >= 'A') && (x <= 'Z')) || ((x >= 'a') && (x <= 'z')) || ('_' == x))
        {
            return 1;
        }
        else if (('\t' == x) || ('\n' == x) || ('\r' == x) || (' ' == x) || ('(' == x) || (')' == x) || ('=' == x) || ('[' == x))
        {
            return 0;
        }

        return 2;
    }

    ////////////////////////////////////////////////////////////////
    // ArCustomParser: find noderef by the `lastName`
    ////////////////////////////////////////////////////////////////
    eNode* ArCustomParser::findNodeByIdentifier(const char* current_msg) const
    {
        char bufor[2][LARGE_BUFFER_SIZE];
        eNode* result = nullptr;

        for (int32_t a = 0; (nullptr == result) && (a < noderefsCount); a++)
        {
            if (noderefs[a].getName().compareExact(lastName, true))
            {
                result = noderefs[a].getReference();
            }
        }

        if (nullptr == result)
        {
            sprintf_s(bufor[0], LARGE_BUFFER_SIZE, "\"%s\": error while checking node identifier", current_msg);
            sprintf_s(bufor[1], LARGE_BUFFER_SIZE, "Identifier \"%s\" not found.", lastName.getText());
            throwError(AR_CUSTOM_PARSER_STATUS_OK, bufor[0], bufor[1]);
        }

        return result;
    }


    ////////////////////////////////////////////////////////////////
    // ArCustomParser: check a single character
    ////////////////////////////////////////////////////////////////
    int32_t ArCustomParser::expectChar(char x)
    {
        int32_t test;
        char current;

        if (AR_CUSTOM_PARSER_STATUS_OK != (test = skipUntilNotEmpty()))
        {
            return test;
        }

        if (sourceFile.read(&current, 0x01))
        {
            if (x == current)
            {
                characterPosition++;
                currentIndentation++;

                return AR_CUSTOM_PARSER_STATUS_OK;
            }

            return AR_CUSTOM_PARSER_STATUS_UNEXP;
        }

        return AR_CUSTOM_PARSER_STATUS_EOF;
    }


    ////////////////////////////////////////////////////////////////
    // ArCustomParser: reading identifier name
    ////////////////////////////////////////////////////////////////
    int32_t ArCustomParser::expectName()
    {
        char current;
        int32_t test;
        int32_t size = 0;
        bool checking_first_of = true;

        /********************************/

        if (AR_CUSTOM_PARSER_STATUS_OK != (test = skipUntilNotEmpty()))
        {
            return test;
        }

        if (nullptr == textBufor)
        {
            textBufor = new char[AR_CUSTOM_PARSER_STRING_MAXLENGTH];
        }

        /********************************/

        while (!sourceFile.endOfFileReached())
        {
            if (size >= AR_CUSTOM_PARSER_NAME_MAXLENGTH)
            {
                return AR_CUSTOM_PARSER_STATUS_TOOMANY;
            }

            if (sourceFile.peek(current))
            {
                test = validatingIdentifierName(checking_first_of, current);
                checking_first_of = false;

                if (0 == test)
                {
                    textBufor[size] = '\0';
                    lastName = textBufor;
                    return AR_CUSTOM_PARSER_STATUS_OK;
                }
                else if (2 == test)
                {
                    return AR_CUSTOM_PARSER_STATUS_INVCHAR;
                }

                characterPosition++;
                sourceFile.skip(+1);

                textBufor[size] = current;
                size++;
            }
        }

        return AR_CUSTOM_PARSER_STATUS_EOF;
    }


    ////////////////////////////////////////////////////////////////
    // ArCustomParser: reading a single- or multiline string
    ////////////////////////////////////////////////////////////////
    int32_t ArCustomParser::expectString()
    {
        char last[2] = {'\0', '\0'};
        char current;

        int32_t test;
        int32_t size = 0;

        bool erase_current = false;
        bool multiline = false;
        bool singleline = false;
        bool whitespace_beginning = true;
        bool newline_started = true;

        /********************************/

        if (AR_CUSTOM_PARSER_STATUS_OK != (test = skipUntilNotEmpty()))
        {
            return test;
        }

        if (nullptr == textBufor)
        {
            textBufor = new char[AR_CUSTOM_PARSER_STRING_MAXLENGTH];
        }

        /********************************/

        while (!sourceFile.endOfFileReached())
        {
            if (size >= AR_CUSTOM_PARSER_STRING_MAXLENGTH)
            {
                return AR_CUSTOM_PARSER_STATUS_TOOMANY;
            }

            if (sourceFile.peek(current))
            {
                if ((!multiline) && (!singleline))
                {
                    if ((0 == size) && ('"' == current))
                    {
                        singleline = true;

                        erase_current = true;
                        size = 0;
                    }
                    else if ((2 == size) && ('`' == last[1]) && ('`' == last[0]) && ('`' == current))
                    {
                        multiline = true;

                        erase_current = true;
                        size = 0;
                    }
                    else
                    {
                        size++;

                        if (size > 2)
                        {
                            return AR_CUSTOM_PARSER_STATUS_UNEXP;
                        }
                    }
                }
                else if (singleline)
                {
                    if ('"' == current)
                    {
                        characterPosition++;
                        sourceFile.skip(+1);

                        textBufor[size] = '\0';
                        lastString = textBufor;
                        return AR_CUSTOM_PARSER_STATUS_OK;
                    }
                    else if (('\t' != current) && (current < ' ') && (current >= 0))
                    {
                        return AR_CUSTOM_PARSER_STATUS_INVCHAR;
                    }
                    else
                    {
                        textBufor[size] = current;
                        size++;
                    }
                }
                else if (multiline)
                {
                    if ('`' == current)
                    {
                        if (('`' == last[1]) && ('`' == last[0]))
                        {
                            characterPosition++;
                            sourceFile.skip(+1);

                            size -= 3;

                            while ((size >= 0) && (('\t' == textBufor[size]) || ('\n' == textBufor[size]) || ('\n' == textBufor[size])))
                            {
                                size--;
                            }

                            textBufor[size + 1] = '\0';

                            lastString = textBufor;
                            return AR_CUSTOM_PARSER_STATUS_OK;
                        }
                        else
                        {
                            textBufor[size] = current;
                            size++;
                        }
                    }
                    else if ((current <= ' ') && (current >= 0))
                    {
                        if (('\t' == current) || ('\n' == current) || ('\r' == current) || (' ' == current))
                        {
                            if ('\n' == current)
                            {
                                lineNumber++;
                                characterPosition = 0;
                                currentIndentation = 0;

                                newline_started = true;

                                if (!whitespace_beginning)
                                {
                                    textBufor[size] = '\n';
                                    size++;
                                }
                            }
                            else if ((!newline_started) && ('\r' != current))
                            {
                                textBufor[size] = current;
                                size++;
                            }
                        }
                        else
                        {
                            return AR_CUSTOM_PARSER_STATUS_INVCHAR;
                        }
                    }
                    else
                    {
                        if (whitespace_beginning)
                        {
                            whitespace_beginning = false;
                            newline_started = false;
                        }
                        else if (newline_started)
                        {
                            newline_started = false;
                        }

                        textBufor[size] = current;
                        size++;
                    }
                }

                last[1] = last[0];

                if (erase_current)
                {
                    last[0] = '\0';
                    erase_current = false;
                }
                else
                {
                    last[0] = current;
                }

                characterPosition++;
                sourceFile.skip(+1);
            }
        }

        return AR_CUSTOM_PARSER_STATUS_EOF;
    }


    ////////////////////////////////////////////////////////////////
    // ArCustomParser: read a number
    // (additional result: 1 if an INT, 2 if a FLOAT, 0 otherwise)
    // ("emptiness" is checked first by the caller)
    ////////////////////////////////////////////////////////////////
    int32_t ArCustomParser::expectNumber(int32_t &result, int32_t &returned_int, float &returned_float)
    {
        result = 0;

        char current;
        int32_t size = 0;

        bool store = false;
        bool hexadecimal = false;
        bool floatingpoint = false;
        int32_t only_zeroes = 0;

        /********************************/

        if (nullptr == textBufor)
        {
            textBufor = new char[AR_CUSTOM_PARSER_STRING_MAXLENGTH];
        }

        /********************************/

        while (!sourceFile.endOfFileReached())
        {
            if (size >= AR_CUSTOM_PARSER_NAME_MAXLENGTH)
            {
                return AR_CUSTOM_PARSER_STATUS_TOOMANY;
            }

            if (sourceFile.peek(current))
            {
                store = false;

                if ('0' == current)
                {
                    if (0 == only_zeroes)
                    {
                        only_zeroes = 1;
                    }

                    store = true;
                }
                else if ((current >= '1') && (current <= '9'))
                {
                    only_zeroes = (-1);
                    store = true;
                }
                else if (('\t' == current) || ('\n' == current) || ('\r' == current) || (' ' == current) || (')' == current) || ('[' == current) || (']' == current))
                {
                    textBufor[size] = '\0';

                    if (hexadecimal)
                    {
                        returned_int = std::strtol(textBufor, NULL, 16);

                        if ((ERANGE != errno) && ((0 != returned_int) || (1 == only_zeroes)))
                        {
                            result = 1;
                        }
                    }
                    else if (floatingpoint)
                    {
                        returned_float = (float)std::strtod(textBufor, NULL);

                        if ((ERANGE != errno) && ((0 != returned_float) || (1 == only_zeroes)))
                        {
                            result = 2;
                        }
                    }
                    else
                    {
                        returned_int = std::strtol(textBufor, NULL, 10);

                        if ((ERANGE != errno) && ((0 != returned_int) || (1 == only_zeroes)))
                        {
                            result = 1;
                        }
                    }

                    return AR_CUSTOM_PARSER_STATUS_OK;
                }
                else if (hexadecimal && (((current >= 'A') && (current <= 'F')) || ((current >= 'a') && (current <= 'f'))))
                {
                    store = true;
                }
                else if ((0 == size) && (!hexadecimal) && (('-' == current) || ('+' == current)))
                {
                    store = true;
                }
                else if ((1 == size) && (!hexadecimal) && ('0' == textBufor[0]) && ('x' == current))
                {
                    hexadecimal = true;
                    size = 0;
                }
                else if ((!hexadecimal) && (!floatingpoint) && ('.' == current))
                {
                    floatingpoint = true;
                    store = true;
                }
                else
                {
                    return AR_CUSTOM_PARSER_STATUS_INVCHAR;
                }

                characterPosition++;
                sourceFile.skip(+1);

                if (store)
                {
                    textBufor[size] = current;
                    size++;
                }
            }
        }

        return AR_CUSTOM_PARSER_STATUS_EOF;
    }


    ////////////////////////////////////////////////////////////////
    // ArCustomParser: read magic property
    // ("emptiness" is checked first by the caller)
    ////////////////////////////////////////////////////////////////
    int32_t ArCustomParser::expectProperty(const char* current_msg, TxtParsingNodeProp* result)
    {
        char bufor[2][LARGE_BUFFER_SIZE];
        int32_t test[3];
        char test_char;
        eNode* dummy_node;
        int32_t dummy_int;
        float dummy_floats[3];

        if (nullptr == result)
        {
            throwError(AR_CUSTOM_PARSER_STATUS_OK, nullptr, "expectProperty(): result pointer is not assigned.");
        }

        result->setValue(TXT_PARSING_NODE_PROPTYPE_UNKNOWN, nullptr);

        /********************************/

        if (sourceFile.peek(test_char))
        {
            if (('"' == test_char) || ('`' == test_char))
            {
                if (AR_CUSTOM_PARSER_STATUS_OK != (test[0] = expectString()))
                {
                    return test[0];
                }

                result->setValue(TXT_PARSING_NODE_PROPTYPE_STRING, &lastString);

                return AR_CUSTOM_PARSER_STATUS_OK;
            }
            else if (1 == validatingIdentifierName(true, test_char))
            {
                if (AR_CUSTOM_PARSER_STATUS_OK != (test[0] = expectName()))
                {
                    return test[0];
                }

                dummy_node = findNodeByIdentifier(current_msg);

                result->setValue(TXT_PARSING_NODE_PROPTYPE_NODEREF, &dummy_node);

                return AR_CUSTOM_PARSER_STATUS_OK;
            }
            else if (((test_char >= '0') && (test_char <= '9')) || ('+' == test_char) || ('-' == test_char))
            {
                if (AR_CUSTOM_PARSER_STATUS_OK != (test[0] = expectNumber(test[1], dummy_int, dummy_floats[0])))
                {
                    return test[0];
                }

                if (1 == test[1])
                {
                    result->setValue(TXT_PARSING_NODE_PROPTYPE_INTEGER, &dummy_int);
                    return AR_CUSTOM_PARSER_STATUS_OK;
                }
                else if (2 == test[1])
                {
                    result->setValue(TXT_PARSING_NODE_PROPTYPE_FLOAT1, dummy_floats);
                    return AR_CUSTOM_PARSER_STATUS_OK;
                }

                sprintf_s(bufor[0], LARGE_BUFFER_SIZE, "\"%s\": error while reading property", current_msg);
                throwError(AR_CUSTOM_PARSER_STATUS_OK, bufor[0], "Could not convert a number to an integer or floating-point.");
            }
            else if ('[' == test_char)
            {
                characterPosition++;
                sourceFile.skip(+1);

                test[2] = 0;

                while (test[2] <= 3)
                {
                    if (AR_CUSTOM_PARSER_STATUS_OK != (test[0] = skipUntilNotEmpty()))
                    {
                        return test[0];
                    }

                    if (sourceFile.peek(test_char))
                    {
                        if (']' == test_char)
                        {
                            characterPosition++;
                            sourceFile.skip(+1);

                            if ((test[2] >= 1) && (test[2] <= 3))
                            {
                                result->setValue(TXT_PARSING_NODE_PROPTYPE_FLOAT1 - 1 + test[2], dummy_floats);
                            }

                            return AR_CUSTOM_PARSER_STATUS_OK;
                        }
                        else if (test[2] >= 3)
                        {
                            sprintf_s(bufor[0], LARGE_BUFFER_SIZE, "\"%s\": error while reading property", current_msg);
                            throwError(AR_CUSTOM_PARSER_STATUS_OK, bufor[0], "Too many numbers in square brackets. Maximum is 3.");
                        }
                        else if (AR_CUSTOM_PARSER_STATUS_OK != (test[0] = expectNumber(test[1], dummy_int, dummy_floats[test[2]])))
                        {
                            return test[0];
                        }

                        if (1 == test[1])
                        {
                            dummy_floats[test[2]] = (float)dummy_int;
                        }
                        else if (2 != test[1])
                        {
                            sprintf_s(bufor[0], LARGE_BUFFER_SIZE, "\"%s\": error while reading property", current_msg);
                            throwError(AR_CUSTOM_PARSER_STATUS_OK, bufor[0], "Could not convert a number to floating-point.");
                        }

                        test[2]++;
                    }
                    else
                    {
                        return AR_CUSTOM_PARSER_STATUS_EOF;
                    }
                }

                return AR_CUSTOM_PARSER_STATUS_TOOMANY;
            }
            else
            {
                return AR_CUSTOM_PARSER_STATUS_UNEXP;
            }
        }

        return AR_CUSTOM_PARSER_STATUS_EOF;
    }


    ////////////////////////////////////////////////////////////////
    // ArCustomParser: read one `identifier = property` pair
    // ("emptiness" is checked first by the caller)
    ////////////////////////////////////////////////////////////////
    int32_t ArCustomParser::expectFullProperty(const char* current_msg, TxtParsingNodeProp* result)
    {
        char bufor[LARGE_BUFFER_SIZE];
        int32_t test;

        if (nullptr == result)
        {
            throwError(AR_CUSTOM_PARSER_STATUS_OK, nullptr, "expectFullProperty(): result pointer is not assigned.");
        }

        /********************************/

        if (AR_CUSTOM_PARSER_STATUS_OK != (test = expectName()))
        {
            return test;
        }

        if (lastName.getLength() <= 0)
        {
            sprintf_s(bufor, LARGE_BUFFER_SIZE, "\"%s\": error while reading property", current_msg);
            throwError(AR_CUSTOM_PARSER_STATUS_OK, bufor, "Property identifier is empty.");
        }

        result->setName(lastName);

        /********************************/

        if (AR_CUSTOM_PARSER_STATUS_OK != (test = expectChar('=')))
        {
            sprintf_s(bufor, LARGE_BUFFER_SIZE, "\"%s\": error while reading property", current_msg);
            throwError(test, bufor, "Expected `=`.");
        }

        /********************************/

        if (AR_CUSTOM_PARSER_STATUS_OK != (test = skipUntilNotEmpty()))
        {
            return test;
        }

        return expectProperty(current_msg, result);
    }

}
