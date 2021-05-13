#ifndef H_KAO2AR_STRINGSECTION
#define H_KAO2AR_STRINGSECTION

#include <ElephantEngine/eRefCounter.h>

#include <ElephantBase/Collection.h>
#include <ElephantEngine/StringProperty.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // StringSection interface
    ////////////////////////////////////////////////////////////////

    class StringSection : public eRefCounter
    {

        /*** Properties ***/

        protected:

            /*[0x08]*/ eString name;
            /*[0x0C-0x14]*/ Collection<ArFunctions::serialize_StringProperty> props;

        /*** Methods ***/

        public:

            StringSection();
            ~StringSection();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            eString getStringRepresentation() const override;

            void saveSectionToTextFile(FileOperator &file, int32_t indentation) const;
    };


    ////////////////////////////////////////////////////////////////
    // StringSection TypeInfo
    // <kao2.00593A00> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_STRINGSECTION_ID = 0xFFFFFFFF;

    extern TypeInfo E_STRINGSECTION_TYPEINFO;

}

#endif
