#include <ElephantBase/kao2ar.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // String operations (macros) for scripts
    ////////////////////////////////////////////////////////////////

    FileOperator& operator << (FileOperator &fo, const char* str)
    {
        fo.write((void*)str, StringFunctions::getCharArrayLength(str));

        return fo;
    }

    FileOperator& operator << (FileOperator &fo, const eString &str)
    {
        fo.write(str.getText(), str.getLength());

        return fo;
    }

    void operator << (eString &str, FileOperator &fo)
    {
        int32_t i;
        char test[2] = {0x00, 0x00};
        eString result;

        while (('\n' != test[0]) && (!fo.endOfFileReached()))
        {
            if (fo.read(&(test[0]), 0x01))
            {
                result += test;
            }
        }

        i = result.getLength() - 1;

        while (i >= 0)
        {
            if (result.getText()[i] < 0x20)
            {
                result = result.getSubstring(0, i);

                i--;
            }
            else
            {
                i = (-1);
            }
        }

        str = result;
    }

    void ArFunctions::writeIndentation(FileOperator &fo, int32_t indentation)
    {
        int32_t i;
        eString result;

        for (i = 0; i < indentation; i++)
        {
            result += "    ";
        }

        fo << result;
    }

    void ArFunctions::writeNewLine(FileOperator &fo, int32_t indentation)
    {
        /* "\n" is automatically changed to "\r\n" by `std::fstream` */

        fo << "\n";

        writeIndentation(fo, indentation);
    }

    int32_t ArFunctions::splitString(eString &source, eString* destination, int32_t max_entries)
    {
        int32_t counter = 0;
        int32_t parts = 0;
        int32_t start = 0;
        int32_t middle = 0;
        int32_t end = source.getLength() - 1;
        char* text = source.getText();

        while ((counter < 2) && (start < end))
        {
            counter = 0;

            if (text[start] <= 0x20)
            {
                start++;
            }
            else
            {
                counter++;
            }

            if (text[end] <= 0x20)
            {
                end--;
            }
            else
            {
                counter++;
            }
        }

        while ((parts + 1) < max_entries)
        {
            middle = start + 1;

            while ((middle <= end) && (text[middle] > 0x20))
            {
                middle++;
            }

            destination[parts] = source.getSubstring(start, middle - start);
            parts++;

            if (middle > end)
            {
                return parts;
            }

            start = middle;
            counter = 0;

            while ((counter < 1) && (start < end))
            {
                if (text[start] <= 0x20)
                {
                    start++;
                }
                else
                {
                    counter = 1;
                }
            }
        }

        if (start <= end)
        {
            /* Could be a line containing only the LF symbol */
            if (text[start] > 0x20)
            {
                destination[parts] = source.getSubstring(start, end - start + 1);
                parts++;
            }
        }

        return parts;
    }

    int32_t ArFunctions::propertyString(eString &source, eString* destination, int32_t max_entries, int32_t line_number)
    {
        int32_t counter, start[2], middle, end;
        eString dummy;
        char* text;

        if (max_entries < 2)
        {
            throw ErrorMessage
            (
                "String parsing error (line %d):\n" \
                "expected at least 2 entries! (before and after the `=` sign)",
                line_number
            );
            return 0;
        }

        end = source.getLength() - 1;
        text = source.getText();

        start[0] = (-1);
        start[1] = (-1);
        middle = (-1);

        for (counter = 0; counter < end; counter++)
        {
            if ('=' == text[counter])
            {
                if (counter <= 0)
                {
                    throw ErrorMessage
                    (
                        "String parsing error (line %d):\n" \
                        "`=` sign found at the beginning!",
                        line_number
                    );
                    return 0;
                }
                else if (middle < 0)
                {
                    middle = counter;
                }
                else
                {
                    throw ErrorMessage
                    (
                        "String parsing error (line %d):\n" \
                        "multiple `=` signs found!",
                        line_number
                    );
                    return 0;
                }
            }
        }

        if (middle < 0)
        {
            throw ErrorMessage
            (
                "String parsing error (line %d):\n" \
                "`=` sign not found!",
                line_number
            );
            return 0;
        }

        for (counter = 0; (start[1] < 0) && (counter < middle); counter++)
        {
            if (text[counter] > 0x20)
            {
                if (start[0] < 0)
                {
                    start[0] = counter;
                }
            }
            else if (text[counter] <= 0x20)
            {
                if (start[0] >= 0)
                {
                    start[1] = counter;
                }
            }
        }

        if (start[0] < 0)
        {
            throw ErrorMessage
            (
                "String parsing error (line %d):\n" \
                "Nothing found on the left side of `=` sign!",
                line_number
            );
            return 0;
        }

        if (start[1] < 0)
        {
            start[1] = middle;
        }

        destination[0] = source.getSubstring(start[0], start[1] - start[0]);
        dummy = source.getSubstring(middle + 1);
        return splitString(dummy, &(destination[1]), max_entries - 1);
    }

    eString ArFunctions::removeComment(eString source, bool hashtag_or_slashes)
    {
        int length = source.getLength();
        const char* text = source.getText();

        if ((hashtag_or_slashes) && (length >= 1))
        {
            for (int a = 0; a < length; a++)
            {
                if ('#' == text[a])
                {
                    return source.getSubstring(0, a);
                }
            }
        }
        else if (length >= 2)
        {
            length--;

            for (int a = 0; a < length; a++)
            {
                if (('/' == text[a]) && ('/' == text[a+1]))
                {
                    return source.getSubstring(0, a);
                }
            }
        }

        return source;
    }


    ////////////////////////////////////////////////////////////////
    // <kao2.0059FE90>
    ////////////////////////////////////////////////////////////////
    bool ArFunctions::compareNameWithWildcards(const char* source, const char* format)
    {
        char a, b;

        if ((nullptr == source) || (nullptr == format))
        {
            return false;
        }

        while (1)
        {
            b = format[0];

            if (('*' == b) && ('\0' == format[1]))
            {
                return true;
            }

            a = source[0];

            if (('\0' == a) && ('\0' == b))
            {
                return true;
            }

            if ('*' == b)
            {
                format++;
                b = format[0];

                if ('\0' == b)
                {
                    return true;
                }

                while ('\0' != a)
                {
                    if (compareNameWithWildcards(source, format))
                    {
                        return true;
                    }

                    source++;
                    a = source[0];
                }

                return false;
            }

            if (('?' != b) && (b != a))
            {
                return false;
            }

            source++;
            format++;
        }

        return false;
    }

}
