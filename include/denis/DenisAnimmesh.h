#ifndef H_DENIS_ANIM_MESH
#define H_DENIS_ANIM_MESH

#include <denis/Denis.h>

namespace ZookieWizard
{
    class eGroup;
    class eMaterial;

    ////////////////////////////////////////////////////////////////
    // Kao the Kangaroo: Anim Mesh sub-structures
    ////////////////////////////////////////////////////////////////

    struct DenisBoundBox2
    {
        /*** Properties ***/

            DenisVertex min;
            DenisVertex max;
            DenisVertex center;
            float radius;

        /*** Methods ***/

            DenisBoundBox2();
            void serialize(DenisFileOperator &file);
    };
    
    struct DenisAnimmeshFace
    {
        /*** Properties ***/

            uint16_t index[4];
            uint16_t dummy[4];

        /*** Methods ***/

            DenisAnimmeshFace();
            void serialize(DenisFileOperator &file);
    };

    struct DenisAnimmeshObject
    {
        /*** Properties ***/

            int32_t verticesCount;
            int32_t groupsCount;
            char name[32];
            int32_t dummy;

            int32_t firstVertexId;
            DenisVertex** vertices;

        /*** Methods ***/

            DenisAnimmeshObject();
            ~DenisAnimmeshObject();

            void serialize(DenisFileOperator &file);
            void serializeVertices(DenisFileOperator &file, int32_t &currentVertexId);
    };

    struct DenisAnimmeshMotion
    {
        /*** Properties ***/

            int32_t keyframesCount;
            char name[32];

            int32_t firstKeyframeId;

        /*** Methods ***/

            DenisAnimmeshMotion();

            void serialize(DenisFileOperator &file, int32_t &currentKeyframeId);
    };

    struct DenisAnimmeshKeyframe
    {
        /*** Properties ***/

            uint8_t groupId;
            uint8_t coordMode;
            DenisEulerRotation rotation;
            DenisVertex translation;

        /*** Methods ***/

            DenisAnimmeshKeyframe();

            void serialize(DenisFileOperator &file);
    };
    
    struct DenisAnimmeshDisplayVertex
    {
        /*** Properties ***/

            uint16_t index;
            
            uint8_t u;
            uint8_t v;

        /*** Methods ***/

            DenisAnimmeshDisplayVertex();

            void serialize(DenisFileOperator &file);
    };
    
    struct DenisAnimmeshDisplayCommand
    {
        /*** Properties ***/

            uint8_t indicesCount;
            uint8_t transparency;
            bool triangleStrips;
            DenisAnimmeshDisplayVertex* indices;

        /*** Methods ***/

            DenisAnimmeshDisplayCommand();
            ~DenisAnimmeshDisplayCommand();

            void serialize(DenisFileOperator &file);
    };


    ////////////////////////////////////////////////////////////////
    // Kao the Kangaroo: Anim Mesh
    ////////////////////////////////////////////////////////////////

    #define DENIS_ANIM_MESH_FILE_TYPE_OBJECT 0x01
    #define DENIS_ANIM_MESH_FILE_TYPE_ENEMY 0x02

    struct DenisAnimmesh
    {
        /*** Properties ***/

            /* Other */
            eString modelName;
            int32_t type;
            DenisBoundBox2 boundBox;

            /* Vertices and vertex groups */
            int32_t totalVertices;
            DenisVertex* vertices;
            int32_t objectsCount;
            DenisAnimmeshObject* objects;

            /* Animations */
            int32_t motionsCount;
            DenisAnimmeshMotion* motions;
            int32_t totalKeyframes;
            DenisAnimmeshKeyframe** keyframes;
            DenisVertex* keyframesUnknown;
            DenisBoundBox2* keyframesBoundBoxes;

            /* Rendering */
            int32_t facesCount;
            DenisAnimmeshFace* faces;
            int32_t commandsCount[4];
            DenisAnimmeshDisplayCommand* commands;
            eMaterial* material;

        /*** Methods ***/

            DenisAnimmesh();
            ~DenisAnimmesh();

            void openAndSerialize(DenisFileOperator &file, int32_t filetype, char* model_name);

            void generateVertices(int32_t anim_id, int32_t frame);

            void loadTexture(DenisFileOperator &file, int32_t filetype);
            void unloadTexture();

            void convertToKao2(eGroup* parent_group, DenisColor* maxobj_colors);
    };

}

#endif
