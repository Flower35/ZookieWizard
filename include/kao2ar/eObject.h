#ifndef H_KAO2AR_OBJECT
#define H_KAO2AR_OBJECT

#include <kao2ar/TypeInfo.h>

namespace ZookieWizard
{
    class Archive;
    class eDrawContext;
    class ColladaExporter;

    ////////////////////////////////////////////////////////////////
    // KAO2 OBJECT INTERFACE
    ////////////////////////////////////////////////////////////////

    class eObject
    {
        /*** Methods ***/

        public:

            eObject();
            /*[[vptr]+0x0C]*/ virtual ~eObject();

        private:

            void createFromOtherObject(const eObject &other);

        public:

            eObject(const eObject &other);
            eObject& operator = (const eObject &other);
            virtual eObject* cloneFromMe() const;

            /* << eObject >> */

            /*[[vptr]+0x00]*/ virtual TypeInfo* getType() const;
            /*[[vptr]+0x08]*/ virtual void serialize(Archive &ar);

            virtual eString getStringRepresentation() const;
            virtual eString generateScriptText() const;
            virtual eString getLogPrintMessage() const;
            virtual void writeStructureToTextFile(FileOperator &file, int32_t indentation, bool group_written) const;
            virtual void writeNodeToXmlFile(ColladaExporter &exporter) const;
    };


    ////////////////////////////////////////////////////////////////
    // eObject TypeInfo
    // <kao2.004631F0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_OBJECT_ID = 0x01;

    extern TypeInfo E_OBJECT_TYPEINFO;

}

#endif
