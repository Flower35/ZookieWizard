
#ifndef H_JSON
#define H_JSON

#include <ZookieWizard/ZookieWizard.h>
#include <ElephantBase/kao2ar.h>
#include <ElephantBase/eString.h>

namespace ZookieWizard
{
    ////////////////////////////////////////////////////////////////
    // JSON definitions
    ////////////////////////////////////////////////////////////////

    #define JSON_VALUETYPE_NULL    0
    #define JSON_VALUETYPE_FALSE   1
    #define JSON_VALUETYPE_TRUE    2
    #define JSON_VALUETYPE_NUMBER  3
    #define JSON_VALUETYPE_STRING  4
    #define JSON_VALUETYPE_ARRAY   5
    #define JSON_VALUETYPE_OBJECT  6


    ////////////////////////////////////////////////////////////////
    // JSON structures
    ////////////////////////////////////////////////////////////////

    template <typename T>
    class eRef
    {
        private:
            T* ref;

            void copy(const eRef<T> &other);
            void decRef();

        public:
            eRef();
            ~eRef();

            eRef(const eRef<T>& other);
            eRef(T* someRef);
            eRef<T>& operator = (const eRef<T>& other);

            T* get() const;
            void set(T* someRef);
    };
    
    class eReferable
    {
        private:
            int referenceCounter;

        protected:
            void copy(const eReferable &other);

        public:
            eReferable();
            ~eReferable();

            eReferable(const eReferable& other);
            eReferable& operator = (const eReferable& other);

            void incRef();
            eReferable* decRef();
    };

    class Utf8EscapedString : public eReferable
    {
        private:
            size_t length;
            size_t capacity;
            char * text;

            void destroy();
            void copyString(const Utf8EscapedString& other);

        public:
            Utf8EscapedString();
            ~Utf8EscapedString();

            Utf8EscapedString(const Utf8EscapedString& other);
            Utf8EscapedString& operator = (const Utf8EscapedString& other);

            void dump(FileOperator& file, size_t indentation, bool startIndent) const;

            void loadFromAnsiString(const eString& ansiString);
    };

    class JsonNumber : public eReferable
    {
        private:
            float number;

            void destroy();
            void copyNumber(const JsonNumber& other);

        public:
            JsonNumber(const float newNumber = 0);
            ~JsonNumber();

            JsonNumber(const JsonNumber& other);
            JsonNumber& operator = (const JsonNumber& other);

            float get() const;
            void set(float newNumer);

            void dump(FileOperator& file, size_t indentation, bool startIndent) const;
    };

    class JsonArray;
    class JsonObject;

    class JsonValue : public eReferable
    {
        private:
            int type;
            eRef<eReferable> value;

            void destroy();
            void copyValue(const JsonValue& other);

        public:
            JsonValue();
            ~JsonValue();

            JsonValue(const JsonValue& other);
            JsonValue& operator = (const JsonValue& other);

            JsonValue(const float number);

            JsonValue(const char * ansiText);
            JsonValue(const eString& ansiString);

            JsonValue(const JsonArray& jsonArray);
            JsonValue(const JsonObject& jsonObject);

            int getType() const;
            void setType(const int someType);

            eReferable * getValue() const;
            void setValue(const int someType, const eReferable& someValue);

            eRef<eReferable> getValueRef() const;
            void setValueRef(const int someType, const eRef<eReferable>& valueRef);

            void dump(FileOperator& file, size_t indentation, bool startIndent) const;
    };
    
    class JsonArray : public eReferable
    {
        private:
            size_t count;
            size_t capacity;
            eRef<JsonValue> * values;

            void destroy();
            void copyArray(const JsonArray& other);

        public:
            JsonArray();
            ~JsonArray();

            JsonArray(const JsonArray& other);
            JsonArray& operator = (const JsonArray& other);

            void dump(FileOperator& file, size_t indentation, bool startIndent) const;

            void clear();

            void appendValue(const JsonValue& value);
            void appendValueRef(const eRef<JsonValue>& valueRef);
    };
    
    class JsonPair : public eReferable
    {
        private:
            eRef<Utf8EscapedString> key;
            eRef<JsonValue> value;

            void destroy();
            void copyPair(const JsonPair& other);

        public:
            JsonPair();
            ~JsonPair();

            JsonPair(const JsonPair& other);
            JsonPair& operator = (const JsonPair& other);

            void setKey(eRef<Utf8EscapedString> keyRef);
            void setValue(eRef<JsonValue> valueRef);

            void dump(FileOperator& file, size_t indentation, bool startIndent) const;
    };

    class JsonObject : public eReferable
    {
        private:
            size_t count;
            size_t capacity;
            eRef<JsonPair> * pairs;

            void destroy();
            void copyObject(const JsonObject& other);

        public:
            JsonObject();
            ~JsonObject();

            JsonObject(const JsonObject& other);
            JsonObject& operator = (const JsonObject& other);

            void dump(FileOperator& file, size_t indentation, bool startIndent) const;

            void clear();

            void appendKeyValue(const eString ansiKey, const JsonValue& value);
            void appendPairRef(const eRef<JsonPair>& pairRef);
    };
}

#endif
