#ifndef H_KAO2AR_OBJECT
#define H_KAO2AR_OBJECT

#include <kao2ar/TypeInfo.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // KAO2 ARCHIVE REFERENCE
    ////////////////////////////////////////////////////////////////

    class Archive;


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
            /*[[vptr]+0x00]*/ virtual TypeInfo* getType();

            virtual eString getStringRepresentation();
            virtual eString generateScriptText();
            virtual eString getLogPrintMessage();
            virtual void writeStructureToTextFile(FileOperator &file, int32_t indentation);

            virtual void renderObject(float time, int32_t draw_flags);
    };


    ////////////////////////////////////////////////////////////////
    // eObject TypeInfo
    // <kao2.00463210> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_OBJECT_ID = 0x01;

    extern TypeInfo E_OBJECT_TYPEINFO;

}

#endif
