#include <denis/DenisAnimmesh.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Anim Mesh: Extended Bounding Box
    ////////////////////////////////////////////////////////////////

    DenisBoundBox2::DenisBoundBox2()
    {
        radius = 0;
    }

    void DenisBoundBox2::serialize(DenisFileOperator &file)
    {
        min.serialize(file);
        max.serialize(file);
        center.serialize(file);
        file.readOrWrite(&radius, 0x04);
    }


    ////////////////////////////////////////////////////////////////
    // Anim Mesh: Surface
    ////////////////////////////////////////////////////////////////

    DenisAnimmeshFace::DenisAnimmeshFace()
    {
        int32_t i;

        for (i = 0; i < 4; i++)
        {
            index[i] = 0;
            dummy[i] = 0;
        }
    }

    void DenisAnimmeshFace::serialize(DenisFileOperator &file)
    {
        int32_t i;

        for (i = 0; i < 4; i++)
        {
            file.readOrWrite(&(index[i]), 0x02);
            file.readOrWrite(&(dummy[i]), 0x02);
        }
    }


    ////////////////////////////////////////////////////////////////
    // Anim Mesh: Vertex Group
    ////////////////////////////////////////////////////////////////

    DenisAnimmeshObject::DenisAnimmeshObject()
    {
        verticesCount = 0;
        groupsCount = 0;
        std::memset(name, 0x00, 32);
        dummy = (-1);

        firstVertexId = 0;
        vertices = nullptr;
    }

    DenisAnimmeshObject::~DenisAnimmeshObject()
    {
        int32_t i;

        if (nullptr != vertices)
        {
            for (i = 0; i < groupsCount; i++)
            {
                if (nullptr != vertices[i])
                {
                    delete[](vertices[i]);
                    vertices[i] = nullptr;
                }
            }

            vertices = nullptr;
        }
    }

    void DenisAnimmeshObject::serialize(DenisFileOperator &file)
    {
        file.readOrWrite(&verticesCount, 0x04);
        file.readOrWrite(&groupsCount, 0x04);
        file.readOrWrite(name, 32);
        file.readOrWrite(&dummy, 0x04);

        if (file.isInReadMode())
        {
            if (verticesCount < 0)
            {
                throw ErrorMessage
                (
                    "Object \"%s\" has invalid number of vertices!",
                    name
                );
            }
            else if ((verticesCount > 0) && (groupsCount < 1))
            {
                throw ErrorMessage
                (
                    "Object \"%s\" has invalid number of vertex groups!",
                    name
                );
            }
        }
    }

    void DenisAnimmeshObject::serializeVertices(DenisFileOperator &file, int32_t &currentVertexId)
    {
        int32_t i, j, dummy;

        if (file.isInReadMode())
        {
            firstVertexId = currentVertexId;
            currentVertexId += verticesCount;

            vertices = new DenisVertex* [groupsCount];

            for (i = 0; i < groupsCount; i++)
            {
                vertices[i] = nullptr;
            }
        }

        for (i = 0; i < groupsCount; i++)
        {
            if (file.isInReadMode())
            {
                vertices[i] = new DenisVertex [verticesCount];
            }

            for (j = 0; j < verticesCount; j++)
            {
                vertices[i][j].serialize(file);
                file.readOrWrite(&dummy, 0x04);
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // Anim Mesh: Motion info
    ////////////////////////////////////////////////////////////////

    DenisAnimmeshMotion::DenisAnimmeshMotion()
    {
        keyframesCount = 0;
        std::memset(name, 0x00, 32);
        
        firstKeyframeId = 0;
    }

    void DenisAnimmeshMotion::serialize(DenisFileOperator &file, int32_t &currentKeyframeId)
    {
        file.readOrWrite(&keyframesCount, 0x04);
        file.readOrWrite(name, 32);

        if (file.isInReadMode())
        {
            firstKeyframeId = currentKeyframeId;
            currentKeyframeId += keyframesCount;

            if (keyframesCount < 1)
            {
                throw ErrorMessage
                (
                    "Animation \"%s\" has invalid number of keyframes!",
                    name
                );
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // Anim Mesh: Keyframe
    ////////////////////////////////////////////////////////////////

    DenisAnimmeshKeyframe::DenisAnimmeshKeyframe()
    {
        groupId = 0;
        coordMode = 0;
    }

    void DenisAnimmeshKeyframe::serialize(DenisFileOperator &file)
    {
        file.readOrWrite(&groupId, 0x01);
        file.readOrWrite(&coordMode, 0x01);

        rotation.serialize(file);
        translation.serialize(file);
    }


    ////////////////////////////////////////////////////////////////
    // Anim Mesh: constructor
    ////////////////////////////////////////////////////////////////

    DenisAnimmesh::DenisAnimmesh()
    {
        int32_t i;

        type = 0;

        totalVertices = 0;
        vertices = nullptr;
        objectsCount = 0;
        objects = nullptr;

        motionsCount = 0;
        motions = nullptr;
        totalKeyframes = 0;
        keyframes = nullptr;
        keyframesUnknown = nullptr;
        keyframesBoundBoxes = nullptr;

        facesCount = 0;
        faces = nullptr;

        for (i = 0; i < 4; i++)
        {
            commandsCount[i] = 0;
        }

        commands = nullptr;

        material = nullptr;
    }


    ////////////////////////////////////////////////////////////////
    // Anim Mesh: destructor
    ////////////////////////////////////////////////////////////////

    DenisAnimmesh::~DenisAnimmesh()
    {
        int32_t i;

        if (nullptr != vertices)
        {
            delete[](vertices);
            vertices = nullptr;
        }
        totalVertices = 0;

        if (nullptr != objects)
        {
            delete[](objects);
            objects = nullptr;
        }
        objectsCount = 0;

        if (nullptr != motions)
        {
            delete[](motions);
            motions = nullptr;
        }
        motionsCount = 0;

        if (nullptr != keyframes)
        {
            for (i = 0; i < totalKeyframes; i++)
            {
                if (nullptr != keyframes[i])
                {
                    delete[](keyframes[i]);
                    keyframes[i] = nullptr;
                }
            }

            delete[](keyframes);
            keyframes = nullptr;
        }
        totalKeyframes = 0;

        if (nullptr != keyframesUnknown)
        {
            delete[](keyframesUnknown);
            keyframesUnknown = nullptr;
        }

        if (nullptr != keyframesBoundBoxes)
        {
            delete[](keyframesBoundBoxes);
            keyframesBoundBoxes = nullptr;
        }

        if (nullptr != faces)
        {
            delete[](faces);
            faces = nullptr;
        }
        facesCount = 0;

        if (nullptr != commands)
        {
            delete[](commands);
            commands = 0;
        }

        for (i = 0; i < 4; i++)
        {
            commandsCount[i] = 0;
        }

        unloadTexture();
    }


    ////////////////////////////////////////////////////////////////
    // Anim Mesh: serialization
    ////////////////////////////////////////////////////////////////

    void DenisAnimmesh::openAndSerialize(DenisFileOperator &file, int32_t filetype, char* model_name)
    {
        int32_t i, j;
        eString test_str;

        switch (filetype)
        {
            case DENIS_ANIM_MESH_FILE_TYPE_OBJECT:
            {
                test_str = "objects/";

                break;
            }

            case DENIS_ANIM_MESH_FILE_TYPE_ENEMY:
            {
                test_str = "charact/";

                break;
            }

            default:
            {
                return;
            }
        }

        modelName = model_name;

        test_str += modelName;
        test_str += "/output.bin";

        if (!file.open(test_str))
        {
            throw ErrorMessage
            (
                "Could not open file: \n" \
                "\"%s\"",
                file.fileName.getText()
            );
        }

        /********************************/
        /* Anim Mesh magic */

        i = *(int32_t*)"T83d";

        file.readOrWrite(&i, 0x04);

        if (file.isInReadMode())
        {
            if (*(int32_t*)"T83d" != i)
            {
                throw ErrorMessage
                (
                    "\"%s\": invalid animmesh magic.",
                    file.fileName.getText()
                );
            }
        }

        /********************************/
        /* File version */

        i = 12;
        
        file.readOrWrite(&i, 0x04);

        if (file.isInReadMode())
        {
            if (12 != i)
            {
                throw ErrorMessage
                (
                    "\"%s\": wrong file version.\n" \
                    "(got %i, expected %i)",
                    file.fileName.getText(),
                    i, 12
                );
            }
        }

        /********************************/
        /* Anim Mesh Header */
        
        file.readOrWrite(&type, 0x04);

        file.readOrWrite(&objectsCount, 0x04);

        if (file.isInReadMode())
        {
            if ((objectsCount < 0) || (objectsCount > 64))
            {
                throw ErrorMessage
                (
                    "\"%s\": wrong number of objects!" \
                    "(got %i, max %i)",
                    file.fileName.getText(),
                    i, 64
                );
            }
        }

        file.readOrWrite(&facesCount, 0x04);

        file.readOrWrite(&motionsCount, 0x04);

        file.readOrWrite(&(commandsCount[0]), 0x04);
        file.readOrWrite(&(commandsCount[1]), 0x04);
        file.readOrWrite(&(commandsCount[2]), 0x04);

        if (file.isInReadMode())
        {
            commandsCount[3] = commandsCount[0] + commandsCount[1];
        }

        boundBox.serialize(file);

        /********************************/
        /* Objects (Vertex Groups info) */

        if (file.isInReadMode())
        {
            objects = new DenisAnimmeshObject [objectsCount];
        }

        for (i = 0; i < objectsCount; i++)
        {
            objects[i].serialize(file);
        }

        /********************************/
        /* Faces (unknown purpose) */

        if (file.isInReadMode())
        {
            faces = new DenisAnimmeshFace [facesCount];
        }

        for (i = 0; i < facesCount; i++)
        {
            faces[i].serialize(file);
        }

        /********************************/
        /* Vertex Groups and Vertices */

        if (file.isInReadMode())
        {
            totalVertices = 0;
        }

        for (i = 0; i < objectsCount; i++)
        {
            objects[i].serializeVertices(file, totalVertices);
        }

        if (file.isInReadMode())
        {
            vertices = new DenisVertex [totalVertices];
        }

        /********************************/
        /* Animations and Keyframes */

        if (file.isInReadMode())
        {
            motions = new DenisAnimmeshMotion [motionsCount];

            totalKeyframes = 0;
        }

        for (i = 0; i < motionsCount; i++)
        {
            motions[i].serialize(file, totalKeyframes);
        }

        if (file.isInReadMode())
        {
            keyframes = new DenisAnimmeshKeyframe* [totalKeyframes];

            for (i = 0; i < totalKeyframes; i++)
            {
                keyframes[i] = nullptr;
            }
        }

        for (i = 0; i < totalKeyframes; i++)
        {
            if (file.isInReadMode())
            {
                keyframes[i] = new DenisAnimmeshKeyframe [objectsCount];
            }

            for (j = 0; j < objectsCount; j++)
            {
                keyframes[i][j].serialize(file);
            }
        }

        /********************************/
        /* Keyframes unknown entries */

        if (file.isInReadMode())
        {
            keyframesUnknown = new DenisVertex [totalKeyframes];
        }

        for (i = 0; i < totalKeyframes; i++)
        {
            keyframesUnknown[i].serialize(file);
        }

        /********************************/
        /* Keyframes bounding boxes */

        if (file.isInReadMode())
        {
            keyframesBoundBoxes = new DenisBoundBox2 [totalKeyframes];
        }

        for (i = 0; i < totalKeyframes; i++)
        {
            keyframesBoundBoxes[i].serialize(file);
        }

        /********************************/
        /* Render commands */

        if (file.isInReadMode())
        {
            commands = new DenisAnimmeshDisplayCommand [commandsCount[3]];
        }

        for (i = 0; i < commandsCount[3]; i++)
        {
            commands[i].serialize(file);
        }
        
        /********************************/
        /* Finish magic */

        i = *(int32_t*)"T83d";

        file.readOrWrite(&i, 0x04);

        if (file.isInReadMode())
        {
            if (*(int32_t*)"T83d" != i)
            {
                throw ErrorMessage
                (
                    "\"%s\": invalid finish magic.",
                    file.fileName.getText()
                );
            }
        }

        file.close();

        /********************************/
        /* Denis Anim Mesh reading complete! :) */
    }

}
