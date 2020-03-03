#include <kao2ar/eString.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Dodatkowe funkcje szblonowe
    ////////////////////////////////////////////////////////////////

    namespace StringFunctions
    {
        void convertString(eString& str1, const eUnicodeString& str2)
        {
            /* Przygotuj nowe dane */
            int otherCount = str2.getLength();
            wchar_t* otherText = str2.getText();
            eString newStr(otherCount);
            str1 = newStr;
            char* myText = str1.getText();

            /* Sprawdzaj znaki diakrytyczne */
            for (int i = 0; i < otherCount; i++)
            {
                if ((otherText[i] >= 0x0000) && (otherText[i] <= 0x007F))
                {
                    myText[i] = (char)otherText[i];
                }
                else switch (otherText[i])
                {
                    case 0x0104: myText[i] = (char)0xA5; break; // LATIN CAPITAL LETTER A WITH OGONEK
                    case 0x0105: myText[i] = (char)0xB9; break; // LATIN SMALL LETTER A WITH OGONEK
                    case 0x0106: myText[i] = (char)0xC6; break; // LATIN CAPITAL LETTER C WITH ACUTE
                    case 0x0107: myText[i] = (char)0xE6; break; // LATIN SMALL LETTER C WITH ACUTE
                    case 0x0118: myText[i] = (char)0xCA; break; // LATIN CAPITAL LETTER E WITH OGONEK
                    case 0x0119: myText[i] = (char)0xEA; break; // LATIN SMALL LETTER E WITH OGONEK
                    case 0x0141: myText[i] = (char)0xA3; break; // LATIN CAPITAL LETTER L WITH STROKE
                    case 0x0142: myText[i] = (char)0xB3; break; // LATIN SMALL LETTER L WITH STROKE
                    case 0x0143: myText[i] = (char)0xD1; break; // LATIN CAPITAL LETTER N WITH ACUTE
                    case 0x0144: myText[i] = (char)0xF1; break; // LATIN SMALL LETTER N WITH ACUTE
                    case 0x00D3: myText[i] = (char)0xD3; break; // LATIN CAPITAL LETTER O WITH ACUTE
                    case 0x00F3: myText[i] = (char)0xF3; break; // LATIN SMALL LETTER O WITH ACUTE
                    case 0x015A: myText[i] = (char)0x8C; break; // LATIN CAPITAL LETTER S WITH ACUTE
                    case 0x015B: myText[i] = (char)0x9C; break; // LATIN SMALL LETTER S WITH ACUTE
                    case 0x0179: myText[i] = (char)0x8F; break; // LATIN CAPITAL LETTER Z WITH ACUTE
                    case 0x017A: myText[i] = (char)0x9F; break; // LATIN SMALL LETTER Z WITH ACUTE
                    case 0x017B: myText[i] = (char)0xAF; break; // LATIN CAPITAL LETTER Z WITH DOT ABOVE
                    case 0x017C: myText[i] = (char)0xBF; break; // LATIN SMALL LETTER Z WITH DOT ABOVE

                    default: myText[i] = '?';
                }
            }
        }

        void convertString(eUnicodeString& str1, const eString& str2)
        {
            /* Przygotuj nowe dane */
            int otherCount = str2.getLength();
            char* otherText = str2.getText();
            eUnicodeString newStr(otherCount);
            str1 = newStr;
            wchar_t* myText = str1.getText();
            myText[otherCount] = 0x00;

            /* Sprawdzaj znaki diakrytyczne */
            for (int i = 0; i < otherCount; i++)
            {
                switch (otherText[i])
                {
                    case (char)0xA5: myText[i] = 0x0104; break; // LATIN CAPITAL LETTER A WITH OGONEK
                    case (char)0xB9: myText[i] = 0x0105; break; // LATIN SMALL LETTER A WITH OGONEK
                    case (char)0xC6: myText[i] = 0x0106; break; // LATIN CAPITAL LETTER C WITH ACUTE
                    case (char)0xE6: myText[i] = 0x0107; break; // LATIN SMALL LETTER C WITH ACUTE
                    case (char)0xCA: myText[i] = 0x0118; break; // LATIN CAPITAL LETTER E WITH OGONEK
                    case (char)0xEA: myText[i] = 0x0119; break; // LATIN SMALL LETTER E WITH OGONEK
                    case (char)0xA3: myText[i] = 0x0141; break; // LATIN CAPITAL LETTER L WITH STROKE
                    case (char)0xB3: myText[i] = 0x0142; break; // LATIN SMALL LETTER L WITH STROKE
                    case (char)0xD1: myText[i] = 0x0143; break; // LATIN CAPITAL LETTER N WITH ACUTE
                    case (char)0xF1: myText[i] = 0x0144; break; // LATIN SMALL LETTER N WITH ACUTE
                    case (char)0xD3: myText[i] = 0x00D3; break; // LATIN CAPITAL LETTER O WITH ACUTE
                    case (char)0xF3: myText[i] = 0x00F3; break; // LATIN SMALL LETTER O WITH ACUTE
                    case (char)0x8C: myText[i] = 0x015A; break; // LATIN CAPITAL LETTER S WITH ACUTE
                    case (char)0x9C: myText[i] = 0x015B; break; // LATIN SMALL LETTER S WITH ACUTE
                    case (char)0x8F: myText[i] = 0x0179; break; // LATIN CAPITAL LETTER Z WITH ACUTE
                    case (char)0x9F: myText[i] = 0x017A; break; // LATIN SMALL LETTER Z WITH ACUTE
                    case (char)0xAF: myText[i] = 0x017B; break; // LATIN CAPITAL LETTER Z WITH DOT ABOVE
                    case (char)0xBF: myText[i] = 0x017C; break; // LATIN SMALL LETTER Z WITH DOT ABOVE

                    default: myText[i] = otherText[i];
                }
            }
        }

        template <typename charT>
        int getCharArrayLength(const charT* str)
        {
            int x = 0;
            if (nullptr != str)
            {
                while ((x < 255) && (0x00 != str[x]))
                {
                    x++;
                }
            }
            return x;
        }

        template <typename charT>
        eStringPtrBase<charT> addStrings(const eStringPtrBase<charT>& str1, const charT* str2, int otherLength)
        {
            /* Przygotuj nowy ci¹g znaków */
            int count1 = str1.getLength();
            int newCount = count1 + otherLength;
            eStringPtrBase<charT> newStr(newCount);
            charT* newText = newStr.getText();

            /* Przypisz nowe dane */
            std::memcpy(newText, str1.getText(), sizeof(charT) * count1);
            std::memcpy(&(newText[count1]), str2, sizeof(charT) * otherLength);

            /* Niepotrzebne `incRef`, bo wywo³ywany jest "copy constructor" */
            return newStr;
        }

        template <typename charT>
        bool compareStrings(const eStringPtrBase<charT>& str1, const charT* str2, int otherLength, int pos, int count, bool case_sensitive)
        {
            charT* myText = str1.getText();
            int myLength = str1.getLength();

            /* Case when we compare full strings, instead of first string's portion */

            if ((count < 0) && (pos <= 0) && (myLength != otherLength))
            {
                return false;
            }

            /* Other setups */

            if (myLength <= 0)
            {
                return false;
            }

            if (pos < 0)
            {
                pos = myLength + pos;

                if (pos < 0)
                {
                    pos = 0;
                }
            }
            else if (pos >= myLength)
            {
                pos = 0;
            }

            if ((count <= 0) || ((pos + count) > myLength))
            {
                count = myLength - pos;
            }

            if (count > otherLength)
            {
                count = otherLength;
            }

            for (int i = 0; i < count; i++)
            {
                if (case_sensitive)
                {
                    if (myText[pos + i] != str2[i])
                    {
                        return false;
                    }
                }
                else if (toLowerCase(myText[pos + i]) != toLowerCase(str2[i]))
                {
                    return false;
                }
            }

            return true;
        }

        template <typename charT>
        charT toLowerCase(charT x)
        {
            /* Czy jest numerem lub ma³¹ liter¹ ASCII? */
            if (((x >= 0x30) && (x <= 0x39)) || ((x >= 0x61) && (x <= 0x7A)))
            {
                return x;
            }
            /* Czy jest du¿¹ liter¹ ASCII? */
            else if ((x >= 0x41) && (x <= 0x5A))
            {
                return (x + 0x20);
            }
            /* Czy jest backslashem? */
            else if (0x5C == x)
            {
                return 0x2F;
            }
            /* Nierozpoznany znak */
            else return x;
        }

    }


    ////////////////////////////////////////////////////////////////
    // Retrieve or set pointer
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
    // Funkcje zwi¹zane z konstrukcj¹
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
            text[count] = 0x00;
        }
        else
        {
            text = nullptr;
        }
    }

    template <typename charT>
    eStringPtrBase<charT>::eStringPtrBase(int count)
    {
        create(count);
    }

    template <typename charT>
    eStringPtrBase<charT>::eStringPtrBase(const charT* str)
    {
        create(str);
    }

    template <typename charT>
    eStringPtrBase<charT>::eStringPtrBase(const eStringPtrBase<charT>& str)
    {
        /* copy constructor */
        pString = nullptr;
        copy(str);
    }

    template <typename charT>
    void eStringPtrBase<charT>::create(int count)
    {
        /* Kao2 engine doesn't accept NULLPTR Strings... */
        /* So it will be empty only when `count < 0` */

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
    void eStringPtrBase<charT>::create(const charT* str)
    {
        int count = StringFunctions::getCharArrayLength(str);

        if (count >= 0)
        {
            pString = new eStringBase<charT>(count);
            charT* myText = pString->getText();
            std::memcpy(myText, str, sizeof(charT) * count);
        }
        else
        {
            pString = nullptr;
        }
    }


    ////////////////////////////////////////////////////////////////
    // Usuwanie, modyfikowanie referencji
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

    template <typename charT>
    eStringPtrBase<charT>::~eStringPtrBase()
    {
        decRef();
    }

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
    // Odwo³ania do wartoœci prywatnych
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
    // Operatory przypisywania i kopiowania
    ////////////////////////////////////////////////////////////////

    template <typename charT>
    void eStringPtrBase<charT>::copy(const eStringPtrBase<charT>& str)
    {
        if (pString != str.pString)
        {
            /* Wyczyœæ obecne dane */
            decRef();

            /* Przypisz nowe dane (w operatorze mamy dostêp do prywatnej wartoœci) */
            pString = str.pString;

            incRef();
        }
    }

    template <typename charT>
    eStringPtrBase<charT>& eStringPtrBase<charT>::operator = (const charT* str)
    {
        /* Wyczyœæ obecne dane */
        decRef();

        /* Przypisz nowe dane */
        create(str);
        return *this;
    }

    template <typename charT>
    eStringPtrBase<charT>& eStringPtrBase<charT>::operator = (const eStringPtrBase<charT>& str)
    {
        copy(str);
        return *this;
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
        copy((*this) + str);
        return *this;
    }

    template <typename charT>
    eStringPtrBase<charT>& eStringPtrBase<charT>::operator += (const eStringPtrBase<charT>& str)
    {
        copy((*this) + str);
        return *this;
    }


    ////////////////////////////////////////////////////////////////
    // Ró¿ne funkcje operuj¹ce na tekstach
    ////////////////////////////////////////////////////////////////

    template <typename charT>
    bool eStringPtrBase<charT>::compare(const eStringPtrBase<charT>& str, int pos, int count, bool case_sensitive) const
    {
        return StringFunctions::compareStrings(*this, str.getText(), str.getLength(), pos, count, case_sensitive);
    }

    template <typename charT>
    bool eStringPtrBase<charT>::compare(const charT* str, int pos, int count, bool case_sensitive) const
    {
        int otherLength = StringFunctions::getCharArrayLength(str);

        return StringFunctions::compareStrings(*this, str, otherLength, pos, count, case_sensitive);
    }

    template <typename charT>
    bool eStringPtrBase<charT>::hasExtension(const charT* str) const
    {
        int otherCount = StringFunctions::getCharArrayLength(str);
        int myCount = pString->getLength();
        charT* myText = pString->getText();

        if (myCount > (1 + otherCount))
        {
            if ('.' == myText[myCount - otherCount - 1])
            {
                for (int i = 0; i < otherCount; i++)
                {
                    if (StringFunctions::toLowerCase(myText[myCount - otherCount + i]) != StringFunctions::toLowerCase(str[i]))
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
        int myLength = pString->getLength();

        if (pos < 0)
        {
            pos = myLength + pos;

            if (pos < 0)
            {
                pos = 0;
            }
        }
        else if (pos >= myLength)
        {
            pos = 0;
        }

        if ((count <= 0) || ((pos + count) > myLength))
        {
            count = myLength - pos;
        }

        /* Niezmienone dane zapewni¹ kopiê referencji */
        if ((0 == pos) && (myLength == count))
        {
            return *this;
        }

        eStringPtrBase<charT> newStr(count);
        charT* otherText = newStr.getText();
        charT* myText = &(pString->getText()[pos]);

        std::memcpy(otherText, myText, sizeof(charT) * count);

        /* Niepotrzebne `incRef`, bo wywo³ywany jest "copy constructor" */
        return newStr;
    }

    template <typename charT>
    eStringPtrBase<charT> eStringPtrBase<charT>::getFilename() const
    {
        int posSlash = 0;
        int posBackslash = 0;
        int count = pString->getLength();
        charT* myText = pString->getText();

        for (int i = (count -1); i >= 0; i--)
        {
            if ((0 == posSlash) && ('/' == myText[i]))
            {
                posSlash = (1 + i);
            }
            else if ((0 == posBackslash) && ('\\' == myText[i]))
            {
                posBackslash = (1 + i);
            }
        }

        return getSubstring(posSlash > posBackslash ? posSlash : posBackslash);
    }


    ////////////////////////////////////////////////////////////////
    // Jawne instancje typów tekstu
    ////////////////////////////////////////////////////////////////

    /* eString */
    template class eStringPtrBase<char>;

    /* eUnicodeString */
    template class eStringPtrBase<wchar_t>;

}
