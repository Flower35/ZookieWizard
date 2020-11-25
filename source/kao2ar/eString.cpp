#include <kao2ar/eString.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Helper functions for the Strings
    ////////////////////////////////////////////////////////////////

    namespace StringFunctions
    {
        void convertString(eString& destination, const eUnicodeString& source)
        {
            int other_count = source.getLength();
            wchar_t* other_text = source.getText();

            destination = eString(other_count);
            char* my_text = destination.getText();

            /* Check the diactric marks */
            for (int i = 0; i < other_count; i++)
            {
                if ((other_text[i] >= 0x0000) && (other_text[i] <= 0x007F))
                {
                    my_text[i] = (char)other_text[i];
                }
                else switch (other_text[i])
                {
                    case 0x0104: my_text[i] = (char)0xA5; break; // LATIN CAPITAL LETTER A WITH OGONEK
                    case 0x0105: my_text[i] = (char)0xB9; break; // LATIN SMALL LETTER A WITH OGONEK
                    case 0x0106: my_text[i] = (char)0xC6; break; // LATIN CAPITAL LETTER C WITH ACUTE
                    case 0x0107: my_text[i] = (char)0xE6; break; // LATIN SMALL LETTER C WITH ACUTE
                    case 0x0118: my_text[i] = (char)0xCA; break; // LATIN CAPITAL LETTER E WITH OGONEK
                    case 0x0119: my_text[i] = (char)0xEA; break; // LATIN SMALL LETTER E WITH OGONEK
                    case 0x0141: my_text[i] = (char)0xA3; break; // LATIN CAPITAL LETTER L WITH STROKE
                    case 0x0142: my_text[i] = (char)0xB3; break; // LATIN SMALL LETTER L WITH STROKE
                    case 0x0143: my_text[i] = (char)0xD1; break; // LATIN CAPITAL LETTER N WITH ACUTE
                    case 0x0144: my_text[i] = (char)0xF1; break; // LATIN SMALL LETTER N WITH ACUTE
                    case 0x00D3: my_text[i] = (char)0xD3; break; // LATIN CAPITAL LETTER O WITH ACUTE
                    case 0x00F3: my_text[i] = (char)0xF3; break; // LATIN SMALL LETTER O WITH ACUTE
                    case 0x015A: my_text[i] = (char)0x8C; break; // LATIN CAPITAL LETTER S WITH ACUTE
                    case 0x015B: my_text[i] = (char)0x9C; break; // LATIN SMALL LETTER S WITH ACUTE
                    case 0x0179: my_text[i] = (char)0x8F; break; // LATIN CAPITAL LETTER Z WITH ACUTE
                    case 0x017A: my_text[i] = (char)0x9F; break; // LATIN SMALL LETTER Z WITH ACUTE
                    case 0x017B: my_text[i] = (char)0xAF; break; // LATIN CAPITAL LETTER Z WITH DOT ABOVE
                    case 0x017C: my_text[i] = (char)0xBF; break; // LATIN SMALL LETTER Z WITH DOT ABOVE

                    default: my_text[i] = '?';
                }
            }
        }

        void convertString(eUnicodeString& destination, const eString& source)
        {
            int other_count = source.getLength();
            char* other_text = source.getText();

            destination = eUnicodeString(other_count);
            wchar_t* my_text = destination.getText();

            /* Check the diactric marks */
            for (int i = 0; i < other_count; i++)
            {
                switch (other_text[i])
                {
                    case (char)0xA5: my_text[i] = 0x0104; break; // LATIN CAPITAL LETTER A WITH OGONEK
                    case (char)0xB9: my_text[i] = 0x0105; break; // LATIN SMALL LETTER A WITH OGONEK
                    case (char)0xC6: my_text[i] = 0x0106; break; // LATIN CAPITAL LETTER C WITH ACUTE
                    case (char)0xE6: my_text[i] = 0x0107; break; // LATIN SMALL LETTER C WITH ACUTE
                    case (char)0xCA: my_text[i] = 0x0118; break; // LATIN CAPITAL LETTER E WITH OGONEK
                    case (char)0xEA: my_text[i] = 0x0119; break; // LATIN SMALL LETTER E WITH OGONEK
                    case (char)0xA3: my_text[i] = 0x0141; break; // LATIN CAPITAL LETTER L WITH STROKE
                    case (char)0xB3: my_text[i] = 0x0142; break; // LATIN SMALL LETTER L WITH STROKE
                    case (char)0xD1: my_text[i] = 0x0143; break; // LATIN CAPITAL LETTER N WITH ACUTE
                    case (char)0xF1: my_text[i] = 0x0144; break; // LATIN SMALL LETTER N WITH ACUTE
                    case (char)0xD3: my_text[i] = 0x00D3; break; // LATIN CAPITAL LETTER O WITH ACUTE
                    case (char)0xF3: my_text[i] = 0x00F3; break; // LATIN SMALL LETTER O WITH ACUTE
                    case (char)0x8C: my_text[i] = 0x015A; break; // LATIN CAPITAL LETTER S WITH ACUTE
                    case (char)0x9C: my_text[i] = 0x015B; break; // LATIN SMALL LETTER S WITH ACUTE
                    case (char)0x8F: my_text[i] = 0x0179; break; // LATIN CAPITAL LETTER Z WITH ACUTE
                    case (char)0x9F: my_text[i] = 0x017A; break; // LATIN SMALL LETTER Z WITH ACUTE
                    case (char)0xAF: my_text[i] = 0x017B; break; // LATIN CAPITAL LETTER Z WITH DOT ABOVE
                    case (char)0xBF: my_text[i] = 0x017C; break; // LATIN SMALL LETTER Z WITH DOT ABOVE

                    default: my_text[i] = other_text[i];
                }
            }
        }

        template <typename charT>
        int getCharArrayLength(const charT* str)
        {
            int x = 0;
            if (nullptr != str)
            {
                while ((x < (1024 - 1)) && (0x00 != str[x]))
                {
                    x++;
                }
            }
            return x;
        }

        template <typename charT>
        charT toLowerCase(charT x)
        {
            /* Is this a number or a small ASCII character? */
            if (((x >= 0x30) && (x <= 0x39)) || ((x >= 0x61) && (x <= 0x7A)))
            {
                return x;
            }
            /* Is this a big ASCII character? */
            else if ((x >= 0x41) && (x <= 0x5A))
            {
                return (x + 0x20);
            }
            /* Is this a backslash? */
            else if (0x5C == x)
            {
                return 0x2F;
            }
            /* Unrecognized character */
            else return x;
        }

        template <typename charT>
        eStringPtrBase<charT> addStrings(const eStringPtrBase<charT>& str1, const charT* str2, int other_length)
        {
            /* Prepare a new String object */
            int first_length = str1.getLength();
            int new_length = first_length + other_length;

            eStringPtrBase<charT> result(new_length);
            charT* new_text = result.getText();

            /* Merge the two texts */
            std::memcpy(new_text, str1.getText(), sizeof(charT) * first_length);
            std::memcpy(&(new_text[first_length]), str2, sizeof(charT) * other_length);

            return result;
        }

        template <typename charT>
        bool compareStrings(const eStringPtrBase<charT>& str1, const charT* str2, int other_length, int pos, int count, bool case_sensitive)
        {
            charT* my_text = str1.getText();
            int my_length = str1.getLength();

            if (my_length <= 0)
            {
                /* Two empty texts are equal to each other */
                return (other_length <= 0);
            }

            /* Position: zero-based or counting from the end of the first string */

            if (pos < 0)
            {
                pos = my_length + pos;

                if (pos < 0)
                {
                    pos = 0;
                }
            }
            else if (pos >= my_length)
            {
                pos = my_length - 1;
            }

            /* Number of checked characters: position-based (positive) or end-base (negative) */

            if (count < 0)
            {
                count = my_length + 1 + count - pos;

                if (count < 0)
                {
                    count = 0;
                }
            }
            else if ((pos + count) > my_length)
            {
                count = my_length - pos;
            }

            if (count > other_length)
            {
                return false;
            }

            /****************/

            for (int i = 0; i < count; i++)
            {
                if (case_sensitive)
                {
                    if (my_text[pos + i] != str2[i])
                    {
                        return false;
                    }
                }
                else if (toLowerCase(my_text[pos + i]) != toLowerCase(str2[i]))
                {
                    return false;
                }
            }

            return true;
        }

        template <typename charT>
        bool comparePaths(const eStringPtrBase<charT>& str1, const charT* str2, int other_length)
        {
            int pos[2] = {0, 0};

            int length[2] =
            {
                str1.getLength(),
                other_length
            };

            charT test_char[2];

            charT* texts[2] =
            {
                str1.getText(),
                (charT*)str2
            };

            /****************/

            while ((pos[0] < length[0]) && (pos[1] < length[1]))
            {
                for (int k = 0; k < 2; k++)
                {
                    test_char[k] = '/';

                    while ((('/' == test_char[k]) || ('\\' == test_char[k])) && (pos[k] < length[k]))
                    {
                        test_char[k] = toLowerCase(texts[k][pos[k]]);
                        pos[k]++;
                    }
                }

                if (test_char[0] != test_char[1])
                {
                    return false;
                }
            }

            return ((pos[0] >= length[0]) && (pos[1] >= length[1]));
        }

    }


    ////////////////////////////////////////////////////////////////
    // eStringBase: Constructor
    ////////////////////////////////////////////////////////////////
    template <typename charT>
    eStringBase<charT>::eStringBase(int count)
    {
        count = (count > 0) ? count : 0;
        refCount = 1;
        length = count;

        if (count > 0)
        {
            text = new charT[1 + count];
            text[0] = 0x00;
            text[count] = 0x00;
        }
        else
        {
            text = nullptr;
        }
    }


    ////////////////////////////////////////////////////////////////
    // eStringBase: Destructor
    ////////////////////////////////////////////////////////////////
    template <typename charT>
    eStringBase<charT>::~eStringBase()
    {
        if (nullptr != text)
        {
            delete[](text);
            text = nullptr;
        }
    }


    ////////////////////////////////////////////////////////////////
    // eStringBase: Reference manipulation
    ////////////////////////////////////////////////////////////////

    template <typename charT>
    eStringBase<charT>* eStringBase<charT>::decRef()
    {
        if (nullptr != this)
        {
            refCount--;

            if (0 == refCount)
            {
                delete this;
                return nullptr;
            }
        }

        return this;
    }

    template <typename charT>
    void eStringBase<charT>::incRef()
    {
        if (nullptr != this)
        {
            refCount++;
        }
    }


    ////////////////////////////////////////////////////////////////
    // eStringBase: Retrieving member data
    ////////////////////////////////////////////////////////////////

    template <typename charT>
    charT* eStringBase<charT>::getText() const
    {
        if (nullptr != this)
        {
            return text;
        }

        return nullptr;
    }

    template <typename charT>
    int eStringBase<charT>::getLength() const
    {
        if (nullptr != this)
        {
            return length;
        }

        return 0;
    }

    template <typename charT>
    int eStringBase<charT>::getReferenceCount() const
    {
        if (nullptr != this)
        {
            return refCount;
        }

        return 0;
    }


    ////////////////////////////////////////////////////////////////
    // eStringPtrBase: Constructors
    ////////////////////////////////////////////////////////////////

    template <typename charT>
    eStringPtrBase<charT>::eStringPtrBase(int count)
    {
        if (count >= 0)
        {
            pString = new eStringBase<charT>(count);
        }
        else
        {
            pString = nullptr;
        }
    }

    template <typename charT>
    eStringPtrBase<charT>::eStringPtrBase(const charT* str)
    {
        createFromText(str);
    }

    template <typename charT>
    eStringPtrBase<charT>::eStringPtrBase(const eStringPtrBase<charT>& str)
    {
        /* Copy Constructor */

        pString = nullptr;

        createFromOtherString(str);
    }


    ////////////////////////////////////////////////////////////////
    // eStringPtrBase: String creation from some data
    ////////////////////////////////////////////////////////////////

    template <typename charT>
    void eStringPtrBase<charT>::createFromText(const charT* str)
    {
        int length = StringFunctions::getCharArrayLength(str);

        if (length >= 0)
        {
            pString = new eStringBase<charT>(length);

            charT* my_text = pString->getText();

            std::memcpy(my_text, str, sizeof(charT) * length);
        }
        else
        {
            pString = nullptr;
        }
    }

    template <typename charT>
    void eStringPtrBase<charT>::createFromOtherString(const eStringPtrBase<charT>& source)
    {
        if (pString != source.pString)
        {
            decRef();

            pString = source.pString;

            incRef();
        }
    }


    ////////////////////////////////////////////////////////////////
    // eStringPtrBase: Destructor
    ////////////////////////////////////////////////////////////////

    template <typename charT>
    eStringPtrBase<charT>::~eStringPtrBase()
    {
        decRef();
    }


    ////////////////////////////////////////////////////////////////
    // eStringPtrBase: Assignment operators and addition operators
    ////////////////////////////////////////////////////////////////

    template <typename charT>
    eStringPtrBase<charT>& eStringPtrBase<charT>::operator = (const charT* str)
    {
        /* In case then the String's own text is assigned to it */
        eStringBase<charT>* previous_base = pString;

        createFromText(str);

        previous_base->decRef();

        return (*this);
    }

    template <typename charT>
    eStringPtrBase<charT>& eStringPtrBase<charT>::operator = (const eStringPtrBase<charT>& str)
    {
        createFromOtherString(str);

        return (*this);
    }

    template <typename charT>
    eStringPtrBase<charT> eStringPtrBase<charT>::operator + (const charT* str) const
    {
        return StringFunctions::addStrings(*this, str, StringFunctions::getCharArrayLength(str));
    }

    template <typename charT>
    eStringPtrBase<charT> eStringPtrBase<charT>::operator + (const eStringPtrBase<charT>& str) const
    {
        return StringFunctions::addStrings(*this, str.getText(), str.getLength());
    }

    template <typename charT>
    eStringPtrBase<charT>& eStringPtrBase<charT>::operator += (const charT* str)
    {
        createFromOtherString((*this) + str);

        return (*this);
    }

    template <typename charT>
    eStringPtrBase<charT>& eStringPtrBase<charT>::operator += (const eStringPtrBase<charT>& str)
    {
        createFromOtherString((*this) + str);

        return (*this);
    }


    ////////////////////////////////////////////////////////////////
    // eStringPtrBase: Reference manipulation
    ////////////////////////////////////////////////////////////////

    template <typename charT>
    void eStringPtrBase<charT>::decRef()
    {
        pString = pString->decRef();
    }

    template <typename charT>
    void eStringPtrBase<charT>::incRef()
    {
        pString->incRef();
    }


    ////////////////////////////////////////////////////////////////
    // eStringPtrBase: Retrieving data from the base object
    ////////////////////////////////////////////////////////////////

    template <typename charT>
    charT* eStringPtrBase<charT>::getText() const
    {
        return pString->getText();
    }

    template <typename charT>
    int eStringPtrBase<charT>::getLength() const
    {
        return pString->getLength();
    }

    template <typename charT>
    int eStringPtrBase<charT>::getReferenceCount() const
    {
        return pString->getReferenceCount();
    }


    ////////////////////////////////////////////////////////////////
    // eStringPtrBase: Retrieve or set the base pointer (used with Archives)
    ////////////////////////////////////////////////////////////////

    template <typename charT>
    eStringBase<charT>* eStringPtrBase<charT>::getPointer() const
    {
        return pString;
    }

    template <typename charT>
    void eStringPtrBase<charT>::setPointer(eStringBase<charT>* newPtr)
    {
        pString = newPtr;
    }


    ////////////////////////////////////////////////////////////////
    // eStringPtrBase: Different text operations
    ////////////////////////////////////////////////////////////////

    template <typename charT>
    bool eStringPtrBase<charT>::isEmpty() const
    {
        if (nullptr != pString)
        {
            if (nullptr != pString->getText())
            {
                return (pString->getLength() <= 0);
            }
        }

        return true;
    }

    template <typename charT>
    bool eStringPtrBase<charT>::compare(const charT* str, int pos, int count, bool case_sensitive) const
    {
        int otherLength = StringFunctions::getCharArrayLength(str);

        return StringFunctions::compareStrings(*this, str, otherLength, pos, count, case_sensitive);
    }

    template <typename charT>
    bool eStringPtrBase<charT>::compare(const eStringPtrBase<charT>& str, int pos, int count, bool case_sensitive) const
    {
        return StringFunctions::compareStrings(*this, str.getText(), str.getLength(), pos, count, case_sensitive);
    }

    template <typename charT>
    bool eStringPtrBase<charT>::compareExact(const charT* str, bool case_sensitive) const
    {
        int other_length = StringFunctions::getCharArrayLength(str);

        if (getLength() != other_length)
        {
            return false;
        }

        return StringFunctions::compareStrings(*this, str, other_length, 0, (-1), case_sensitive);
    }

    template <typename charT>
    bool eStringPtrBase<charT>::compareExact(const eStringPtrBase<charT>& str, bool case_sensitive) const
    {
        int other_length = str.getLength();

        if (getLength() != other_length)
        {
            return false;
        }

        return StringFunctions::compareStrings(*this, str.getText(), other_length, 0, (-1), case_sensitive);
    }

    template <typename charT>
    bool eStringPtrBase<charT>::comparePath(const charT* str) const
    {
        int other_length = StringFunctions::getCharArrayLength(str);

        return StringFunctions::comparePaths(*this, str, other_length);
    }

    template <typename charT>
    bool eStringPtrBase<charT>::comparePath(const eStringPtrBase<charT>& str) const
    {
        return StringFunctions::comparePaths(*this, str.getText(), str.getLength());
    }

    template <typename charT>
    bool eStringPtrBase<charT>::hasExtension(const charT* str) const
    {
        int ext_length = StringFunctions::getCharArrayLength(str);
        int my_length = getLength();
        charT* my_text = getText();

        if (my_length > (1 + ext_length))
        {
            my_length -= ext_length;

            if ('.' == my_text[my_length - 1])
            {
                for (int i = 0; i < ext_length; i++)
                {
                    if (StringFunctions::toLowerCase(my_text[my_length + i]) != StringFunctions::toLowerCase(str[i]))
                    {
                        return false;
                    }
                }
            }
            else return false;
        }
        else return false;

        return true;
    }

    template <typename charT>
    eStringPtrBase<charT> eStringPtrBase<charT>::getSubstring(int pos, int count) const
    {
        int my_length = getLength();

        if (my_length <= 0)
        {
            return eStringPtrBase<charT>();
        }

        /****************/

        if (pos < 0)
        {
            pos = my_length + pos;

            if (pos < 0)
            {
                pos = 0;
            }
        }
        else if (pos >= my_length)
        {
            pos = my_length - 1;
        }

        /****************/

        if (count < 0)
        {
            count = my_length + 1 + count - pos;

            if (count < 0)
            {
                count = 0;
            }
        }
        else if ((pos + count) > my_length)
        {
            count = my_length - pos;
        }

        /* Just create a copy of the same string if the region matches */

        if ((0 == pos) && (my_length == count))
        {
            return (*this);
        }

        /****************/

        eStringPtrBase<charT> result(count);
        charT* result_text = result.getText();
        charT* my_text = &(getText()[pos]);

        std::memcpy(result_text, my_text, sizeof(charT) * count);

        return result;
    }

    template <typename charT>
    eStringPtrBase<charT> eStringPtrBase<charT>::getPath() const
    {
        int afterslash_pos = 0;
        charT* text = getText();

        for (int i = (getLength() - 1); (0 == afterslash_pos) && (i >= 0); i--)
        {
            if (('/' == text[i]) || ('\\' == text[i]))
            {
                afterslash_pos = (1 + i);
            }
        }

        return getSubstring(0, afterslash_pos);
    }

    template <typename charT>
    eStringPtrBase<charT> eStringPtrBase<charT>::getFilename(bool with_extesion) const
    {
        int sub_length = (-1);
        int afterslash_pos = 0;
        charT* text = getText();

        for (int i = (getLength() - 1); (0 == afterslash_pos) && (i >= 0); i--)
        {
            if ((!with_extesion) && ('.' == text[i]))
            {
                sub_length = i;
                with_extesion = true;
            }
            else if (('/' == text[i]) || ('\\' == text[i]))
            {
                afterslash_pos = (1 + i);

                if (sub_length > afterslash_pos)
                {
                    sub_length -= afterslash_pos;
                }
            }
        }

        return getSubstring(afterslash_pos, sub_length);
    }

    template <typename charT>
    eStringPtrBase<charT> eStringPtrBase<charT>::trimWhitespace() const
    {
        charT* my_text = getText();
        int my_length = getLength();
        int a, start = (-1), end = (-1);

        /****************/

        a = 0;

        while ((start < 0) && (a < my_length))
        {
            if (' ' == my_text[a])
            {
                a++;
            }
            else
            {
                start = a;
            }
        }

        if (start < 0)
        {
            return eStringPtrBase<charT>();
        }

        /****************/

        a = my_length - 1;

        while ((end < 0) && (a > start))
        {
            if (' ' == my_text[a])
            {
                a--;
            }
            else
            {
                end = a;
            }
        }

        if (end < 0)
        {
            end = start;
        }

        return getSubstring(start, (end - my_length));
    }

    template <typename charT>
    void eStringPtrBase<charT>::assertPath()
    {
        int length = getLength();
        charT* text = getText();

        if (length > 0)
        {
            switch (text[length - 1])
            {
                case '/':
                case '\\':
                {
                    break;
                }

                default:
                {
                    createFromOtherString(StringFunctions::addStrings((*this), "/", 1));
                }
            }
        }
    }

    template <typename charT>
    bool eStringPtrBase<charT>::isRooted() const
    {
        int length = getLength();
        charT* text = getText();

        int b = 0;

        for (int a = 0; a < length; a++)
        {
            if (0 == b)
            {
                if (((text[a] < 'a') || (text[a] > 'z')) && ((text[a] < 'A') || (text[a] > 'Z')))
                {
                    if (':' == text[a])
                    {
                        b++;
                    }
                    else
                    {
                        return false;
                    }
                }
            }
            else if (1 == b)
            {
                if (('/' == text[a]) || ('\\' == text[a]))
                {
                    return true;
                }

                return false;
            }
        }

        return false;
    }


    ////////////////////////////////////////////////////////////////
    // Explicit templates
    ////////////////////////////////////////////////////////////////

    /* eString */
    template class eStringPtrBase<char>;

    //// /* eUnicodeString */
    //// template class eStringPtrBase<wchar_t>;

}
