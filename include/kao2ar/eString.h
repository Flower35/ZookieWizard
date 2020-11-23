#ifndef H_KAO2AR_STRING
#define H_KAO2AR_STRING

#include <cstring> // `std::memcpy`

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Multireference Serializable String class from KAO2
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

            eStringBase(int count);
            ~eStringBase();

            /* Reference manipulation */
            eStringBase<charT>* decRef();
            void incRef();

            /* Retrieving member data */
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

            eStringPtrBase(int count = 0);
            eStringPtrBase(const charT* str);
            eStringPtrBase(const eStringPtrBase<charT>& str);
            ~eStringPtrBase();

        private:

            /* String creation from some data */
            void createFromText(const charT* str);
            void createFromOtherString(const eStringPtrBase<charT>& source);

        public:

            /* Assignment operators and addition operators */
            eStringPtrBase<charT>& operator = (const charT* str);
            eStringPtrBase<charT>& operator = (const eStringPtrBase<charT>& str);
            eStringPtrBase<charT> operator + (const charT* str) const;
            eStringPtrBase<charT> operator + (const eStringPtrBase<charT>& str) const;
            eStringPtrBase<charT>& operator += (const charT* str);
            eStringPtrBase<charT>& operator += (const eStringPtrBase<charT>& str);

            /* Reference manipulation */
            void decRef();
            void incRef();

            /* Retrieving data from the base object */
            charT* getText() const;
            int getLength() const;
            int getReferenceCount() const;

            /* Retrieve or set the base pointer */
            eStringBase<charT>* getPointer() const;
            void setPointer(eStringBase<charT>* newPtr);

            /* Different text operations */
            bool isEmpty() const;
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
            void assertPath();
            bool isRooted() const;
    };


    ////////////////////////////////////////////////////////////////
    // Alternate String type definitions (better class names)
    ////////////////////////////////////////////////////////////////

    typedef eStringPtrBase<char> eString;
    typedef eStringPtrBase<wchar_t> eUnicodeString;


    ////////////////////////////////////////////////////////////////
    // Helper functions for the Strings
    ////////////////////////////////////////////////////////////////

    namespace StringFunctions
    {
        void convertString(eString& deestination, const eUnicodeString& source);
        void convertString(eUnicodeString& destination, const eString& source);

        template <typename charT>
        int getCharArrayLength(const charT* str);

        template <typename charT>
        charT toLowerCase(charT x);
    }

}

#endif
