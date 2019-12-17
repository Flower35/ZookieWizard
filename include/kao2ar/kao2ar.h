#ifndef H_KAO2AR
#define H_KAO2AR

#include <ZookieWizard/ZookieWizard.h>

#include <kao2ar/eString.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ENGINE VERSIONS
    ////////////////////////////////////////////////////////////////
    
    #define GAME_VERSION_KAO2_PL_PC 1
    #define GAME_VERSION_KAO2_EUR_PC 2
    #define GAME_VERSION_KAO_TW_PC 3


    ////////////////////////////////////////////////////////////////
    // Collection of functions declared outside classes
    ////////////////////////////////////////////////////////////////

    class Archive;
    class eRefCounter;
    struct TypeInfo;

    namespace ArFunctions
    {
        eString readString(Archive &ar);
        void writeString(Archive &ar, eString &s);

        void serialize_eRefCounter(Archive &ar, eRefCounter** o, TypeInfo* t);

        void serialize_eMultiBlockIndexCtrl(Archive &ar, eRefCounter** o, TypeInfo* t);
        void serialize_Property(Archive &ar, eRefCounter** o, TypeInfo* t);
        void serialize_StringProperty(Archive &ar, eRefCounter** o, TypeInfo* t);
        void serialize_StringSection(Archive &ar, eRefCounter** o, TypeInfo* t);

        void writeIndentation(FileOperator &fo, int32_t indentation);
        void writeNewLine(FileOperator &fo, int32_t indentation);
    }

    FileOperator& operator << (FileOperator &fo, const char* str);
    FileOperator& operator << (FileOperator &fo, const eString &str);


    ////////////////////////////////////////////////////////////////
    // KAO2 DATA STRUCTURES
    ////////////////////////////////////////////////////////////////

    typedef uint16_t ushort;

    /* `sizeof(ePoint2) == 0x08` (8 bytes) */
    struct ePoint2
    {
        float u;
        float v;
    };

    /* `sizeof(ePoint3) == 0x0C` (12 bytes) */
    struct ePoint3
    {
        float x;
        float y;
        float z;

        ePoint3();
        ePoint3(float initializer);
        ePoint3(float, float, float);

        ePoint3& operator + (const ePoint3&);
        ePoint3& operator - (const ePoint3&);
        ePoint3& operator * (float);

        void serialize(Archive &ar);
    };

    /* `sizeof(ePoint4) == 0x10` (16 bytes) */
    struct ePoint4
    {
        float x;
        float y;
        float z;
        float w;

        ePoint4();

        void serialize(Archive &ar);
    };

    /* `sizeof(ePhyVertex) == 0x10` (16 bytes) */
    struct ePhyVertex
    {
        int8_t index[4];
        float weight[3];
    };

    /* `sizeof(eABB) == 0x20` (32 bytes) */
    struct eABB
    {
        float min[3];
        int32_t unknown_0C;
        float max[3];
        int32_t unknown_1C;
    };

    /* `sizeof(eQuat) == 0x10` (16 bytes) */
    struct eQuat
    {
        float x;
        float y;
        float z;
        float w;

        eQuat();
        eQuat(float initializer);
        eQuat(float, float, float, float);

        eQuat& operator+(const eQuat&);
        eQuat& operator-(const eQuat&);
        eQuat& operator * (float);

        void normalize();
    };

    struct eMatrix
    {
        float m[4][4];

        eMatrix();

        void transpose(float result[16]);
    };

    eMatrix operator * (eMatrix a, eMatrix b);

    /* `sizeof(eSRP) == 0x20` (32 bytes) */
    struct eSRP
    {
        eQuat rot;
        ePoint3 pos;
        float scale;

        eSRP();
        eSRP(float initializer);
        
        eMatrix getMatrix();

        void serialize(Archive &ar);
    };

    /* "eAnimState", "eTrack": */
    enum loopTypeEnum
    {
        DEFAULT = -1,
        SINGLE = 0,
        REPEAT = 1,
        QUARTZ = 2
    };

}

#endif
