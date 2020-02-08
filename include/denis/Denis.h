#ifndef H_DENIS_MAIN
#define H_DENIS_MAIN

#include <ZookieWizard/ZookieWizard.h>
#include <kao2ar/eString.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Kao the Kangaroo: Serialization/Deserialization opeartor
    ////////////////////////////////////////////////////////////////

    struct DenisFileOperator
    {
        /*** Properties ***/

            FileOperator myFile;
            uint8_t mode;

            eString fileName;
            eString workingDirectory;

        /*** Methods ***/

            DenisFileOperator(eString new_dir);
            ~DenisFileOperator();
            DenisFileOperator& operator = (const DenisFileOperator &new_file);

            bool isInReadMode() const;
            void readOrWrite(void* ptr, int32_t size);

            bool open(eString path);
            void close();
    };


    ////////////////////////////////////////////////////////////////
    // Kao the Kangaroo: object types in level
    ////////////////////////////////////////////////////////////////

    #define DENIS_LEVEL_OBJECT_TYPE_STATIC 0
    #define DENIS_LEVEL_OBJECT_TYPE_PUSHABLE 2
    #define DENIS_LEVEL_OBJECT_TYPE_MOVING 1
    #define DENIS_LEVEL_OBJECT_TYPES 3

    extern const int DENIS_LEVEL_OBJECT_ID[DENIS_LEVEL_OBJECT_TYPES];


    ////////////////////////////////////////////////////////////////
    // Kao the Kangaroo: vertex structure
    ////////////////////////////////////////////////////////////////

    struct DenisVertex
    {
        /*** Properties ***/

            float x;
            float y;
            float z;

        /*** Methods ***/

            DenisVertex();

            void serialize(DenisFileOperator &file);
    };


    ////////////////////////////////////////////////////////////////
    // Kao the Kangaroo: color structure
    ////////////////////////////////////////////////////////////////

    struct DenisColor
    {
        /*** Properties ***/

        uint8_t color_blue;
        uint8_t color_green;
        uint8_t color_red;
        uint8_t alpha;

        /*** Methods ***/

        DenisColor();

        void serialize(DenisFileOperator &file);
    };


    ////////////////////////////////////////////////////////////////
    // Kao the Kangaroo: geo vertex
    ////////////////////////////////////////////////////////////////

    struct DenisGeoVertex
    {
        /*** Properties ***/

            DenisVertex v;
            DenisColor c;

        /*** Methods ***/

            void serialize(DenisFileOperator &file);
    };


    ////////////////////////////////////////////////////////////////
    // Kao the Kangaroo: boundary box structure
    ////////////////////////////////////////////////////////////////

    struct DenisBoundBox
    {
        /*** Properties ***/

            DenisVertex min;
            DenisVertex max;

        /*** Methods ***/

            void serialize(DenisFileOperator &file);
    };


    ////////////////////////////////////////////////////////////////
    // Kao the Kangaroo: geo face
    ////////////////////////////////////////////////////////////////

    struct DenisGeoFace
    {
        /*** Properties ***/

            DenisVertex normalVector;
            float dotProduct;

            uint16_t index[4];
            int32_t collisionType;
            int32_t dummy;

        /*** Methods ***/

            DenisGeoFace();

            void serialize(DenisFileOperator &file);
    };


    ////////////////////////////////////////////////////////////////
    // Kao the Kangaroo: euler rotation
    ////////////////////////////////////////////////////////////////

    struct DenisEulerRotation
    {
        /*** Properties ***/

            uint16_t alpha;
            uint16_t beta;
            uint16_t gamma;

        /*** Methods ***/

            DenisEulerRotation();

            void serialize(DenisFileOperator &file);

            void toEulerAngles(bool isAnimmesh, float &x, float &y, float &z) const;
            void toQuaternion(float result[4]) const;
    };

}

#endif
