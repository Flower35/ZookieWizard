#ifndef H_KAO2AR_STRING
#define H_KAO2AR_STRING

#include <cstring> // `std::memcpy`

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Klasay napisów w KAO2/KAO3
    ////////////////////////////////////////////////////////////////

    template <typename charT>
    class eStringBase
    {
        /*** Properties ***/

        private:

            int refCount;
            int length;
            charT* text;

        /*** Methods ***/

        public:

            /* Konstrukcja klasy */
            eStringBase<charT>(int count);

            /* Usuwanie, modyfikowanie referencji */
            ~eStringBase();
            eStringBase<charT>* decRef();
            void incRef();

            /* Odwo³ania do wartoœci prywatnych */
            charT* getText() const;
            int getLength() const;
            int getReferenceCount() const;
    };

    template <typename charT>
    class eStringPtrBase
    {
        /*** eString pointer wrapper ***/

        private:

            eStringBase<charT>* pString;

        /*** Methods ***/

        public:

            /* Retrieve or set pointer - used with Archives */
            eStringBase<charT>* getPointer() const;
            void setPointer(eStringBase<charT>*  newPtr);

            /* Funkcje zwi¹zane z konstrukcj¹ */
            void create(int count);
            void create(const charT* str);
            void copy(const eStringPtrBase<charT>& sourceStr);

            /* Modyfikowanie referencji */
            void decRef();
            void incRef();

            /* Funkcje zwi¹zane z konstrukcj¹ i dekonstrukcj¹ */
            eStringPtrBase<charT>(int count = 0);
            eStringPtrBase<charT>(const charT* str);
            eStringPtrBase<charT>(const eStringPtrBase<charT>& str);
            ~eStringPtrBase();

            /* Odwo³ania do wartoœci prywatnych */
            charT* getText() const;
            int getLength() const;
            int getReferenceCount() const;

            /* Ró¿ne funkcje operuj¹ce na tekstach */
            bool compare(const charT* str, int pos = 0, int count = (-1), bool case_sensitive = false) const;
            bool compare(const eStringPtrBase<charT>& str, int pos = 0, int count = (-1), bool case_sensitive = false) const;
            bool compareExact(const charT* str, bool case_sensitive = true) const;
            bool compareExact(const eStringPtrBase<charT>& str, bool case_sensitive = true) const;
            bool comparePath(const charT* str) const;
            bool comparePath(const eStringPtrBase<charT>& str) const;
            bool hasExtension(const charT* str) const;
            eStringPtrBase<charT> getSubstring(int pos, int count = (-1)) const;
            eStringPtrBase<charT> getPath() const;
            eStringPtrBase<charT> getFilename(bool with_extesion) const;
            eStringPtrBase<charT> trimWhitespace() const;
            bool isRooted() const;

            /* Operatory przypisywania i kopiowania */
            eStringPtrBase<charT>& operator = (const charT* str);
            eStringPtrBase<charT>& operator = (const eStringPtrBase<charT>& str);
            eStringPtrBase<charT> operator + (const charT* str) const;
            eStringPtrBase<charT> operator + (const eStringPtrBase<charT>& str) const;
            eStringPtrBase<charT>& operator += (const charT* str);
            eStringPtrBase<charT>& operator += (const eStringPtrBase<charT>& str);
    };


    ////////////////////////////////////////////////////////////////
    // Definicje u¿ywanych typów tekstu
    ////////////////////////////////////////////////////////////////

    typedef eStringPtrBase<char> eString;
    typedef eStringPtrBase<wchar_t> eUnicodeString;


    ////////////////////////////////////////////////////////////////
    // Dodatkowe funkcje szblonowe
    ////////////////////////////////////////////////////////////////

    namespace StringFunctions
    {
        void convertString(eString& str1, const eUnicodeString& str2);
        void convertString(eUnicodeString& str1, const eString& str2);

        template <typename charT>
        int getCharArrayLength(const charT* str);

        template <typename charT>
        charT toLowerCase(charT x);
    }

}

#endif
