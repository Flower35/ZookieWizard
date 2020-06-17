#ifndef H_KAO2AR_OBJECT
#define H_KAO2AR_OBJECT

#include <kao2ar/TypeInfo.h>

namespace ZookieWizard
{
    class Archive;
    struct eAnimate;
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

            /*[[vptr]+0x08]*/ virtual void serialize(Archive &ar);
            /*[[vptr]+0x00]*/ virtual TypeInfo* getType() const;

            virtual eString getStringRepresentation() const;
            virtual eString generateScriptText() const;
            virtual eString getLogPrintMessage() const;
            virtual void writeStructureToTextFile(FileOperator &file, int32_t indentation) const;
            virtual void writeNodeToXmlFile(ColladaExporter &exporter) const;

            virtual bool renderObject(int32_t draw_flags, eAnimate* anim, eSRP &parent_srp, eMatrix4x4 &parent_matrix, int32_t marked_id);
    };


    ////////////////////////////////////////////////////////////////
    // eObject TypeInfo
    // <kao2.00463210> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_OBJECT_ID = 0x01;

    extern TypeInfo E_OBJECT_TYPEINFO;

}

#endif
