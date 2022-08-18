#include <utilities/Json.h>

namespace ZookieWizard
{
    ////////////////////////////////////////////////////////////////
    // eRef
    ////////////////////////////////////////////////////////////////

    template <typename T>
    eRef<T>::eRef()
    {
        ref = nullptr;
    }

    template <typename T>
    void eRef<T>::decRef()
    {
        if (nullptr != ref)
        {
            ref = (T *) ref->decRef();
        }
    }

    template <typename T>
    eRef<T>::~eRef()
    {
        decRef();
    }

    template <typename T>
    void eRef<T>::copy(const eRef<T>& other)
    {
        ref = other.ref;

        if (nullptr != ref)
        {
            ref->incRef();
        }
    }

    template <typename T>
    eRef<T>::eRef(const eRef<T>& other)
    {
        copy(other);
    }

    template <typename T>
    eRef<T>::eRef(T* someRef)
    {
        ref = someRef;

        if (nullptr != ref)
        {
            ref->incRef();
        }
    }

    template <typename T>
    eRef<T>& eRef<T>::operator = (const eRef<T>& other)
    {
        if ((this == &other) || (other.ref == ref))
        {
            return (*this);
        }

        decRef();
        copy(other);
        return (*this);
    }

    template <typename T>
    T* eRef<T>::get() const
    {
        return ref;
    }

    template <typename T>
    void eRef<T>::set(T* someRef)
    {
        if (someRef == ref)
        {
            return;
        }

        decRef();

        ref = someRef;

        if (nullptr != ref)
        {
            ref->incRef();
        }
    }


    ////////////////////////////////////////////////////////////////
    // eReferable
    ////////////////////////////////////////////////////////////////

    eReferable::eReferable()
    {
        referenceCounter = 0;
    }

    eReferable::~eReferable()
    {}

    void eReferable::copy(const eReferable& other)
    {
        referenceCounter = 0;
    }

    eReferable::eReferable(const eReferable& other)
    {
        copy(other);
    }

    eReferable& eReferable::operator = (const eReferable& other)
    {
        if (this == &other)
        {
            return (*this);
        }

        copy(other);

        return (*this);
    }

    void eReferable::incRef()
    {
        referenceCounter += 1;
    }

    eReferable* eReferable::decRef()
    {
        if (referenceCounter <= 0)
        {
            return this;
        }

        referenceCounter -= 1;

        if (0 == referenceCounter)
        {
            delete(this);
            return nullptr;
        }

        return this;
    }


    ////////////////////////////////////////////////////////////////
    // UTF8 escaped string
    ////////////////////////////////////////////////////////////////

    Utf8EscapedString::Utf8EscapedString()
    : eReferable()
    {
        length = 0;
        capacity = 0;
        text = nullptr;
    }

    void Utf8EscapedString::destroy()
    {
        if (nullptr != text)
        {
            delete[](text);
        }
    }

    Utf8EscapedString::~Utf8EscapedString()
    {
        destroy();
    }

    void Utf8EscapedString::copyString(const Utf8EscapedString& other)
    {
        eReferable::copy(other);

        length = other.length;
        capacity = other.capacity;

        if (capacity <= length)
        {
            capacity = (1 + length);
        }

        if (capacity > 0)
        {
            text = new char[capacity];

            if (length > 0)
            {
                memcpy(text, other.text, sizeof(char) * length);
            }

            text[length] = 0;
        }
        else
        {
            text = nullptr;
        }
    }

    Utf8EscapedString::Utf8EscapedString(const Utf8EscapedString& other)
    {
        copyString(other);
    }

    Utf8EscapedString& Utf8EscapedString::operator = (const Utf8EscapedString& other)
    {
        if (this == &other)
        {
            return (*this);
        }

        destroy();

        copyString(other);

        return (*this);
    }

    void Utf8EscapedString::dump(FileOperator& file, size_t indentation, bool startIndent) const
    {
        if (startIndent)
        {
            for (size_t i = 0; i < indentation; i++)
            {
                file << "  ";
            }
        }

        const char dummy = '"';

        file.write(&(dummy), 1);

        file.write(text, length);

        file.write(&(dummy), 1);
    }

    void Utf8EscapedString::loadFromAnsiString(const eString& ansiString)
    {
        destroy();

        const eString escaped = ansiString.escapedUTF8();

        length = escaped.getLength();
        capacity = (length > 0) ? (1 + length) : 0;
 
        if (capacity > 0)
        {
            text = new char[capacity];

            if (length > 0)
            {
                memcpy(text, escaped.getText(), sizeof(char) * length);
            }

            text[length] = 0;
        }
        else
        {
            text = nullptr;
        }
    }


    ////////////////////////////////////////////////////////////////
    // UTF8 number
    ////////////////////////////////////////////////////////////////

    JsonNumber::JsonNumber(const float newNumber)
    : eReferable()
    {
        number = newNumber;
    }

    void JsonNumber::destroy()
    {}

    JsonNumber::~JsonNumber()
    {
        destroy();
    }

    void JsonNumber::copyNumber(const JsonNumber& other)
    {
        eReferable::copy(other);

        number = other.number;
    }

    JsonNumber::JsonNumber(const JsonNumber& other)
    {
        copyNumber(other);
    }

    JsonNumber& JsonNumber::operator = (const JsonNumber& other)
    {
        if (this == &other)
        {
            return (*this);
        }

        destroy();

        copyNumber(other);

        return (*this);
    }

    float JsonNumber::get() const
    {
        return number;
    }

    void JsonNumber::set(float newNumer)
    {
        number = newNumer;
    }

    void JsonNumber::dump(FileOperator& file, size_t indentation, bool startIndent) const
    {
        char buf[64];

        if (startIndent)
        {
            for (size_t i = 0; i < indentation; i++)
            {
                file << "  ";
            }
        }

        snprintf(buf, sizeof(buf), "%.6f", number);
        file << buf;
    }


    ////////////////////////////////////////////////////////////////
    // JSON value
    ////////////////////////////////////////////////////////////////

    JsonValue::JsonValue()
    : eReferable()
    {
        type = JSON_VALUETYPE_NULL;
    }

    void JsonValue::destroy()
    {}

    JsonValue::~JsonValue()
    {
        destroy();
    }

    void JsonValue::copyValue(const JsonValue& other)
    {
        eReferable::copy(other);

        type = other.type;
        value = other.value;
    }

    JsonValue::JsonValue(const JsonValue& other)
    {
        copyValue(other);
    }
    
    JsonValue& JsonValue::operator = (const JsonValue& other)
    {
        if (this == &other)
        {
            return (*this);
        }

        destroy();

        copyValue(other);

        return (*this);
    }

    JsonValue::JsonValue(const float number)
    : eReferable()
    {
        eRef<JsonNumber> dummyNumber(new JsonNumber(number));

        type = JSON_VALUETYPE_NUMBER;
        value = (*((eRef<eReferable> *) & dummyNumber));
    }

    JsonValue::JsonValue(const char * ansiText)
    : eReferable()
    {
        eRef<Utf8EscapedString> dummyString(new Utf8EscapedString());
        dummyString.get()->loadFromAnsiString(ansiText);

        type = JSON_VALUETYPE_STRING;
        value = (*((eRef<eReferable> *) & dummyString));
    }

    JsonValue::JsonValue(const eString& ansiString)
    : eReferable()
    {
        eRef<Utf8EscapedString> dummyString(new Utf8EscapedString());
        dummyString.get()->loadFromAnsiString(ansiString);

        type = JSON_VALUETYPE_STRING;
        value = (*((eRef<eReferable> *) &dummyString));
    }

    JsonValue::JsonValue(const JsonArray& jsonArray)
    : eReferable()
    {
        eRef<JsonArray> dummyArray(new JsonArray(jsonArray));

        type = JSON_VALUETYPE_ARRAY;
        value = (*((eRef<eReferable> *) &dummyArray));
    }
    
    JsonValue::JsonValue(const JsonObject& jsonObject)
    : eReferable()
    {
        eRef<JsonObject> dummyObject(new JsonObject(jsonObject));

        type = JSON_VALUETYPE_OBJECT;
        value = (*((eRef<eReferable> *) &dummyObject));
    }

    int JsonValue::getType() const
    {
        return type;
    }

    void JsonValue::setType(const int someType)
    {
        type = someType;

        switch (type)
        {
            case JSON_VALUETYPE_NUMBER:
            {
                eRef<JsonNumber> dummyNumber(new JsonNumber());
                value = (*((eRef<eReferable> *) & dummyNumber));
                break;
            }
            case JSON_VALUETYPE_STRING:
            {
                eRef<Utf8EscapedString> dummyString(new Utf8EscapedString());
                value = (*((eRef<eReferable> *) & dummyString));
                break;
            }
            case JSON_VALUETYPE_ARRAY:
            {
                eRef<JsonArray> dummyArray(new JsonArray());
                value = (*((eRef<eReferable> *) & dummyArray));
                break;
            }
            case JSON_VALUETYPE_OBJECT:
            {
                eRef<JsonObject> dummyObject(new JsonObject());
                value = (*((eRef<eReferable> *) & dummyObject));
                break;
            }
            default:
            {
                value = eRef<eReferable>();
            }
        }
    }

    eReferable* JsonValue::getValue() const
    {
        return value.get();
    }

    void JsonValue::setValue(const int someType, const eReferable& someValue)
    {
        type = someType;

        switch (type)
        {
            case JSON_VALUETYPE_NUMBER:
            {
                eRef<JsonNumber> dummyNumber(new JsonNumber(*((JsonNumber *) &someValue)));
                value = (*((eRef<eReferable> *) &dummyNumber));
                break;
            }
            case JSON_VALUETYPE_STRING:
            {
                eRef<Utf8EscapedString> dummyString(new Utf8EscapedString(*((Utf8EscapedString *) &someValue)));
                value = (*((eRef<eReferable> *) &dummyString));
                break;
            }
            case JSON_VALUETYPE_ARRAY:
            {
                eRef<JsonArray> dummyArray(new JsonArray(*((JsonArray *) &someValue)));
                value = (*((eRef<eReferable> *) &dummyArray));
                break;
            }
            case JSON_VALUETYPE_OBJECT:
            {
                eRef<JsonObject> dummyObject(new JsonObject(*((JsonObject *) &someValue)));
                value = (*((eRef<eReferable> *) &dummyObject));
                break;
            }
            default:
            {
                value = eRef<eReferable>();
            }
        }
    }

    eRef<eReferable> JsonValue::getValueRef() const
    {
        return value;
    }

    void JsonValue::setValueRef(const int someType, const eRef<eReferable>& valueRef)
    {
        type = someType;
        value = valueRef;
    }

    void JsonValue::dump(FileOperator& file, size_t indentation, bool startIndent) const
    {
        int dummy_type = type;
        eReferable * dummy_value = value.get();

        if (nullptr == dummy_value)
        {
            switch (dummy_type)
            {
                case JSON_VALUETYPE_NULL:
                case JSON_VALUETYPE_FALSE:
                case JSON_VALUETYPE_TRUE:
                {
                    break;
                }
                default:
                {
                    dummy_type = JSON_VALUETYPE_NULL;
                }
            }
        }

        switch (dummy_type)
        {
            case JSON_VALUETYPE_NULL:
            case JSON_VALUETYPE_FALSE:
            case JSON_VALUETYPE_TRUE:
            {
                if (startIndent)
                {
                    for (size_t i = 0; i < indentation; i++)
                    {
                        file << "  ";
                    }
                }
                break;
            }
        }

        switch (dummy_type)
        {
            case JSON_VALUETYPE_NULL:
            {
                file << "null";
                break;
            }
            case JSON_VALUETYPE_FALSE:
            {
                file << "false";
                break;
            }
            case JSON_VALUETYPE_TRUE:
            {
                file << "true";
                break;
            }
            case JSON_VALUETYPE_NUMBER:
            {
                JsonNumber * jsonNumber = (JsonNumber *) dummy_value;
                jsonNumber->dump(file, indentation, startIndent);
                break;
            }
            case JSON_VALUETYPE_STRING:
            {
                Utf8EscapedString * jsonString = (Utf8EscapedString *) dummy_value;
                jsonString->dump(file, indentation, startIndent);
                break;
            }
            case JSON_VALUETYPE_ARRAY:
            {
                JsonArray * jsonArray = (JsonArray *) dummy_value;
                jsonArray->dump(file, indentation, startIndent);
                break;
            }
            case JSON_VALUETYPE_OBJECT:
            {
                JsonObject * jsonObject = (JsonObject *) dummy_value;
                jsonObject->dump(file, indentation, startIndent);
                break;
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // JSON array
    ////////////////////////////////////////////////////////////////

    JsonArray::JsonArray()
    : eReferable()
    {
        count = 0;
        capacity = 0;
        values = nullptr;
    }

    void JsonArray::destroy()
    {
        if (nullptr != values)
        {
            delete[](values);
        }
    }

    JsonArray::~JsonArray()
    {
        destroy();
    }

    void JsonArray::copyArray(const JsonArray& other)
    {
        eReferable::copy(other);

        count = other.count;
        capacity = other.capacity;

        if (capacity < count)
        {
            capacity = count;
        }

        if (capacity > 0)
        {
            values = new eRef<JsonValue>[capacity];

            for (size_t i = 0; i < count; i++)
            {
                values[i] = other.values[i];
            }
        }
        else
        {
            values = nullptr;
        }
    }

    JsonArray::JsonArray(const JsonArray& other)
    {
        copyArray(other);
    }
    
    JsonArray& JsonArray::operator = (const JsonArray& other)
    {
        if (this == &other)
        {
            return (*this);
        }

        destroy();

        copyArray(other);

        return (*this);
    }

    void JsonArray::dump(FileOperator& file, size_t indentation, bool startIndent) const
    {
        size_t i;
        char dummy;
        bool multiline = false;

        for (i = 0; (i < count) && (!multiline); i++)
        {
            JsonValue * dummy_value = values[i].get();

            if (nullptr != dummy_value)
            {
                switch (dummy_value->getType())
                {
                    case JSON_VALUETYPE_STRING:
                    case JSON_VALUETYPE_ARRAY:
                    case JSON_VALUETYPE_OBJECT:
                    {
                        multiline = true;
                        break;
                    }
                }
            }
        }

        if (startIndent)
        {
            for (i = 0; i < indentation; i++)
            {
                file << "  ";
            }
        }

        dummy = '[';
        file.write(&(dummy), 1);

        if (count > 0)
        {
            indentation++;

            if (multiline)
            {
                dummy = '\n';
                file.write(&(dummy), 1);
            }

            for (i = 0; i < count; i++)
            {
                JsonValue * jsonValue = values[i].get();

                if (nullptr != jsonValue)
                {
                    jsonValue->dump(file, indentation, multiline);
                }
                else
                {
                    if (multiline)
                    {
                        for (i = 0; i < indentation; i++)
                        {
                            file << "  ";
                        }
                    }

                    file << "null";
                }

                if (i < (count - 1))
                {
                    dummy = ',';
                    file.write(&(dummy), 1);

                    if (!multiline)
                    {
                        dummy = ' ';
                        file.write(&(dummy), 1);
                    }
                }

                if (multiline)
                {
                    dummy = '\n';
                    file.write(&(dummy), 1);
                }
            }

            indentation--;

            if (multiline)
            {
                for (i = 0; i < indentation; i++)
                {
                    file << "  ";
                }
            }
        }

        dummy = ']';
        file.write(&(dummy), 1);
    }

    void JsonArray::clear()
    {
        count = 0;
    }

    void JsonArray::appendValue(const JsonValue& value)
    {
        eRef<JsonValue> dummyValue(new JsonValue(value));

        appendValueRef(dummyValue);
    }

    void JsonArray::appendValueRef(const eRef<JsonValue>& valueRef)
    {
        if ((count + 1) > capacity)
        {
            size_t new_capacity = (1 + capacity);
            eRef<JsonValue> * new_values = new eRef<JsonValue>[new_capacity];

            if (nullptr != values)
            {
                for (size_t i = 0; i < count; i++)
                {
                    new_values[i] = values[i];
                }

                delete[](values);
            }

            capacity = new_capacity;
            values = new_values;
        }

        values[count] = valueRef;
        count++;
    }


    ////////////////////////////////////////////////////////////////
    // JSON pair
    ////////////////////////////////////////////////////////////////

    JsonPair::JsonPair()
    : eReferable()
    {}

    void JsonPair::destroy()
    {}

    JsonPair::~JsonPair()
    {
        destroy();
    }

    void JsonPair::copyPair(const JsonPair& other)
    {
        eReferable::copy(other);

        key = other.key;
        value = other.value;
    }

    JsonPair::JsonPair(const JsonPair& other)
    {
        copyPair(other);
    }
    
    JsonPair& JsonPair::operator = (const JsonPair& other)
    {
        if (this == &other)
        {
            return (*this);
        }

        destroy();

        copyPair(other);

        return (*this);
    }

    void JsonPair::setKey(eRef<Utf8EscapedString> keyRef)
    {
        key = keyRef;
    }

    void JsonPair::setValue(eRef<JsonValue> valueRef)
    {
        value = valueRef;
    }

    void JsonPair::dump(FileOperator& file, size_t indentation, bool startIndent) const
    {
        if (startIndent)
        {
            for (size_t i = 0; i < indentation; i++)
            {
                file << "  ";
            }
        }

        Utf8EscapedString * jsonString = key.get();

        if (nullptr != jsonString)
        {
            jsonString->dump(file, 0, false);
        }
        else
        {
            file << "\"\"";
        }

        file << ": ";

        JsonValue * jsonValue = value.get();

        if (nullptr != jsonValue)
        {
            jsonValue->dump(file, indentation, false);
        }
        else
        {
            file << "null";
        }
    }


    ////////////////////////////////////////////////////////////////
    // JSON object
    ////////////////////////////////////////////////////////////////

    JsonObject::JsonObject()
    : eReferable()
    {
        count = 0;
        capacity = 0;
        pairs = nullptr;
    }

    void JsonObject::destroy()
    {
        if (nullptr != pairs)
        {
            delete[](pairs);
        }
    }
    
    JsonObject::~JsonObject()
    {
        destroy();
    }

    void JsonObject::copyObject(const JsonObject& other)
    {
        eReferable::copy(other);

        count = other.count;
        capacity = other.capacity;

        if (capacity < count)
        {
            capacity = count;
        }

        if (capacity > 0)
        {
            pairs = new eRef<JsonPair>[capacity];

            for (size_t i = 0; i < count; i++)
            {
                pairs[i] = other.pairs[i];
            }
        }
        else
        {
            pairs = nullptr;
        }
    }

    JsonObject::JsonObject(const JsonObject& other)
    {
        copyObject(other);
    }
    
    JsonObject& JsonObject::operator = (const JsonObject& other)
    {
        if (this == &other)
        {
            return (*this);
        }

        destroy();

        copyObject(other);

        return (*this);
    }

    void JsonObject::dump(FileOperator& file, size_t indentation, bool startIndent) const
    {
        size_t i;
        char dummy;

        if (startIndent)
        {
            for (i = 0; i < indentation; i++)
            {
                file << "  ";
            }
        }

        dummy = '{';
        file.write(&(dummy), 1);

        if (count > 0)
        {
            indentation++;

            dummy = '\n';
            file.write(&(dummy), 1);

            for (i = 0; i < count; i++)
            {
                JsonPair * jsonPair = pairs[i].get();

                if (nullptr != jsonPair)
                {
                    jsonPair->dump(file, indentation, true);
                    
                    if (i < (count - 1))
                    {
                        dummy = ',';
                        file.write(&(dummy), 1);
                    }

                    dummy = '\n';
                    file.write(&(dummy), 1);
                }
            }

            indentation--;

            for (i = 0; i < indentation; i++)
            {
                file << "  ";
            }
        }

        dummy = '}';
        file.write(&(dummy), 1);
    }

    void JsonObject::clear()
    {
        count = 0;
    }

    void JsonObject::appendKeyValue(const eString ansiKey, const JsonValue& value)
    {
        eRef<Utf8EscapedString> dummyKey(new Utf8EscapedString());
        dummyKey.get()->loadFromAnsiString(ansiKey);

        eRef<JsonValue> dummyValue(new JsonValue(value));

        eRef<JsonPair> dummyPair(new JsonPair());
        dummyPair.get()->setKey(dummyKey);
        dummyPair.get()->setValue(dummyValue);

        appendPairRef(dummyPair);
    }

    void JsonObject::appendPairRef(const eRef<JsonPair>& pairRef)
    {
        if ((count + 1) > capacity)
        {
            size_t new_capacity = (1 + capacity);
            eRef<JsonPair> * new_pairs = new eRef<JsonPair>[new_capacity];

            if (nullptr != pairs)
            {
                for (size_t i = 0; i < count; i++)
                {
                    new_pairs[i] = pairs[i];
                }

                delete[](pairs);
            }

            capacity = new_capacity;
            pairs = new_pairs;
        }

        pairs[count] = pairRef;
        count++;
    }

}
