#ifndef H_KAO2AR
#define H_KAO2AR

#include <ZookieWizard/ZookieWizard.h>

#include <ElephantBase/eString.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ENGINE VERSIONS
    ////////////////////////////////////////////////////////////////

    #define GAME_VERSION_KAO2_PL_PC 1
    #define GAME_VERSION_KAO2_EUR_PC 2
    #define GAME_VERSION_KAO_TW_PC 3
    #define GAME_VERSION_ASTERIX_XXL2_PSP 4


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

        void serialize_eRefCounter(Archive &ar, eRefCounter** o, const TypeInfo* t);

        void serialize_eMultiBlockIndexCtrl(Archive &ar, eRefCounter** o, const TypeInfo* t);
        void serialize_Property(Archive &ar, eRefCounter** o, const TypeInfo* t);
        void serialize_StringProperty(Archive &ar, eRefCounter** o, const TypeInfo* t);
        void serialize_StringSection(Archive &ar, eRefCounter** o, const TypeInfo* t);

        void writeIndentation(FileOperator &fo, int32_t indentation);
        void writeNewLine(FileOperator &fo, int32_t indentation);

        int32_t splitString(eString &source, eString* destination, int32_t max_entries);
        int32_t propertyString(eString &source, eString* destination, int32_t max_entries, int32_t line_number);
        eString removeComment(eString source, bool hashtag_or_slashes);

        bool compareNameWithWildcards(const char* source, const char* format);
    }

    FileOperator& operator << (FileOperator &fo, const char* str);
    FileOperator& operator << (FileOperator &fo, const eString &str);
    void operator << (eString &str, FileOperator &fo);


    ////////////////////////////////////////////////////////////////
    // KAO2 DATA STRUCTURES
    ////////////////////////////////////////////////////////////////

    typedef uint16_t ushort;

    /* user-defined assignment */
    struct ePoint3;
    struct ePoint4;

    /* `sizeof(ePoint2) == 0x08` (8 bytes) */
    struct ePoint2
    {
        float u;
        float v;

        ePoint2();
        ePoint2(float initializer);
        ePoint2(float, float);

        bool operator == (const ePoint2&) const;
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

        bool operator == (const ePoint3&) const;

        ePoint3 operator + (const ePoint3&) const;
        ePoint3& operator += (const ePoint3&);
        ePoint3 operator - (const ePoint3&) const;
        ePoint3& operator -= (const ePoint3&);
        ePoint3 operator * (float) const;

        ePoint3(const ePoint4&);
        ePoint3& operator += (const ePoint4&);
        ePoint3& operator -= (const ePoint4&);

        float getLength() const;
        void normalize();

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
        ePoint4(float initializer);
        ePoint4(float, float, float, float);

        ePoint4 operator + (const ePoint4&) const;
        ePoint4& operator += (const ePoint4&);
        ePoint4 operator - (const ePoint4&) const;
        ePoint4& operator -= (const ePoint4&);
        ePoint4 operator * (float) const;

        ePoint4(const ePoint3&);
        ePoint4& operator += (const ePoint3&);
        ePoint4& operator -= (const ePoint3&);

        float getLength() const;
        void normalize();

        void serialize(Archive &ar);
    };

    ePoint3 crossProduct(const ePoint3&, const ePoint3&);
    float dotProduct(const ePoint3&, const ePoint3&);
    float angleBetweenVectors(const ePoint3&, const ePoint3&);
    void calculateBoundaryBox(ePoint3&, ePoint3&, int32_t, const ePoint4*, int32_t, const ushort*);

    /* `sizeof(ePhyVertex) == 0x10` (16 bytes) */
    struct ePhyVertex
    {
        int8_t index[4];
        float weight[3];
    };

    /* `sizeof(eABB) == 0x20` (32 bytes) */
    struct eABB
    {
        ePoint3 min;
        int32_t leftNode;
        ePoint3 max;
        int32_t rightNode;

        eABB();

        bool operator == (const eABB&) const;

        bool fitsMeFromLeft(const eABB&) const;
        bool fitsMeFromRight(const eABB&) const;
        bool isIntersecting(const eABB&) const;
        void expandBoundaries(const eABB&, bool, bool);
        bool insertLeaf(int32_t, int32_t&, eABB*, const eABB&);
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

        eQuat operator + (const eQuat&) const;
        eQuat operator - (const eQuat&) const;
        eQuat operator * (const eQuat&) const;
        eQuat operator * (float) const;

        float getLength() const;
        void normalize();

        void fromEulerAngles(bool transposed, float alpha_rad, float beta_rad, float gamma_rad);
        void fromAxisAngle(ePoint3&, float);
        void toEulerAngles(bool inverse, float &alpha_rad, float &beta_rad, float &gamma_rad) const;
    };

    ePoint3 operator * (const ePoint3 &pos, const eQuat &rot);

    struct eMatrix4x4
    {
        float m[4][4];

        eMatrix4x4();

        void identity();
        void transpose(float result[16]) const;

        void serialize(Archive &ar);

        void setRotationZ(float angle);
        void setRotationY(float angle);
        void setRotationX(float angle);
    };

    eMatrix4x4 operator * (const eMatrix4x4 &a, const eMatrix4x4 &b);
    ePoint4 operator * (const eMatrix4x4 &a, const ePoint4 &p);

    /* Global Bones Matrices */
    extern eMatrix4x4 theBonesMatrices[40];

    /* `sizeof(eSRP) == 0x20` (32 bytes) */
    struct eSRP
    {
        eQuat rot;
        ePoint3 pos;
        float scale;

        eSRP();
        eSRP(float initializer);

        eMatrix4x4 getMatrix() const;
        eMatrix4x4 getInverseMatrix() const;

        void serialize(Archive &ar);

        eSRP applyAnotherSRP(const eSRP &parent) const;
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
