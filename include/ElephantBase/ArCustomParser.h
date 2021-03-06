#ifndef H_AR_CUSTOM_PARSER
#define H_AR_CUSTOM_PARSER

#include <ElephantBase/kao2ar.h>

namespace ZookieWizard
{
    class eNode;
    class eGroup;

    class TxtParsingNodeProp; /* declared in "eNode.h" */


    ////////////////////////////////////////////////////////////////
    // ArCustomParserNoderef class
    ////////////////////////////////////////////////////////////////

    class ArCustomParserNoderef
    {
        /*** Properties ***/

        private:

            eString name;
            eNode* reference;

        /*** Methods ***/

        public:

            ArCustomParserNoderef();
            ~ArCustomParserNoderef();

        private:

            void createFromOtherObject(const ArCustomParserNoderef &other);

        public:

            ArCustomParserNoderef(const ArCustomParserNoderef &other);
            ArCustomParserNoderef& operator = (const ArCustomParserNoderef &other);

            void set(eNode* new_reference, eString new_name);

            eString getName() const;
            eNode* getReference() const;
    };


    ////////////////////////////////////////////////////////////////
    // ArCustomParserFileStatus class
    ////////////////////////////////////////////////////////////////

    class ArCustomParserFileStatus
    {
        /*** Properties ***/

        public:

            eString fileName;
            int32_t fileOffset;

            int32_t lineNumber;
            int32_t characterPosition;
            int32_t currentIndentation;
    };

    #define AR_CUSTOM_PARSER_MAX_INCLUDES 16


    ////////////////////////////////////////////////////////////////
    // ArCustomParser class
    ////////////////////////////////////////////////////////////////

    class ArCustomParser
    {
        /*** Properties ***/

        private:

            FileOperator sourceFile;
            int32_t lineNumber;
            int32_t characterPosition;
            int32_t currentIndentation;

            char* textBufor;

            int32_t lastPropType;
            eString lastName;
            eString lastString;
            eNode* lastNoderef;
            int32_t validFloats;
            float lastFloats[3];

            eGroup* defaultParent;
            eNode* lastNode;

            int32_t noderefsCount;
            int32_t noderefsMaxLength;
            ArCustomParserNoderef* noderefs;

            int32_t propsCount;
            int32_t propsMaxLength;
            TxtParsingNodeProp* props;

            int32_t includedFileId;
            ArCustomParserFileStatus includedFiles[AR_CUSTOM_PARSER_MAX_INCLUDES];

        /*** Methods ***/

        public:

            ArCustomParser();
            ~ArCustomParser();

            bool openFile(eString filename, eGroup* current_parent);
            eGroup* getDefaultParent() const;
            int32_t beginParsing();

        private:

            void insertNewProp(TxtParsingNodeProp* new_prop);
            void insertNewNoderef(eNode* new_reference, eString new_name);
            void removeNoderef(eNode* reference);

            void throwError(int32_t status, const char* main_message, const char* param1) const;

            int32_t skipUntilNotEmpty();

            int32_t validatingIdentifierName(bool is_first, char x) const;
            int32_t checkIfLastNameWasReserved() const;
            int32_t findNodeByIdentifier(const char* current_msg, eNode** result, bool can_be_reserved) const;

            int32_t expectChar(char x);
            int32_t expectName();
            int32_t expectString();
            int32_t expectNumber(int32_t &result, int32_t &returned_int, float &returned_float);
            int32_t expectProperty(const char* current_msg, TxtParsingNodeProp* result);
            int32_t expectFullProperty(const char* current_msg, TxtParsingNodeProp* result);

            void collectPropertiesInParentheses(const char* current_msg, bool full_props);
            void parseTypeInfoAndIdentifier(bool can_name_be_empty, const char* current_msg, const TypeInfo* &returned_type, eString &returned_name);

    };

}

#endif
