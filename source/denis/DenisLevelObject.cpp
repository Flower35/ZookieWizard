#include <denis/DenisLevelObject.h>
#include <denis/DenisLevelTrack.h>

#include <kao2engine/eGroup.h>
#include <kao2engine/eMaterial.h>
#include <kao2engine/eGeoArray.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Level Object: constructor
    ////////////////////////////////////////////////////////////////

    DenisLevelObject::DenisLevelObject()
    {
        std::memset(name, 0x00, 32);
        
        flags = 0x0F;
        dummy_04 = 0;

        vertexCount = 0;
        faces1sidedCount = 0;
        faces2sidedCount = 0;

        dummy_34 = (-1);
        dummy_38 = 0;
        dummy_3C = 0;

        vertices = nullptr;
        faces = nullptr;

        tracksCount = 0;
        tracks = nullptr;

        unknownWordsCount = 0;
        unknownWords = nullptr;
    }


    ////////////////////////////////////////////////////////////////
    // Level Object: destructor
    ////////////////////////////////////////////////////////////////

    DenisLevelObject::~DenisLevelObject()
    {
        if (nullptr != vertices)
        {
            delete[](vertices);
        }

        if (nullptr != faces)
        {
            delete[](faces);
        }

        if (nullptr != tracks)
        {
            delete[](tracks);
        }

        if (nullptr != unknownWords)
        {
            delete[](unknownWords);
        }
    }


    ////////////////////////////////////////////////////////////////
    // Level Object: serialization
    ////////////////////////////////////////////////////////////////

    void DenisLevelObject::serialize(DenisFileOperator &file, int32_t current_type)
    {
        int32_t i;
        
        /* Flags */

        file.readOrWrite(&flags, 0x04);

        /* Dummy (4 bytes) */

        file.readOrWrite(&dummy_04, 0x04);

        /* Number of vertices */

        file.readOrWrite(&vertexCount, 0x04);

        /* 1-sided faces and 2-sided faces */

        file.readOrWrite(&faces1sidedCount, 0x04);
        file.readOrWrite(&faces2sidedCount, 0x04);

        /* Object name */

        file.readOrWrite(name, 32);

        /* unknown values */

        file.readOrWrite(&dummy_34, 0x04);
        file.readOrWrite(&dummy_38, 0x04);
        file.readOrWrite(&dummy_3C, 0x04);

        /* Boundary box */

        boundBox.serialize(file);

        /* Vertices (position and color) */

        if (file.isInReadMode())
        {
            vertices = new DenisGeoVertex [vertexCount];
        }

        for (i = 0; i < vertexCount; i++)
        {
            vertices[i].serialize(file);
        }

        /* Collision faces */

        if (file.isInReadMode())
        {
            faces = new DenisGeoFace [faces1sidedCount + faces2sidedCount];
        }

        for (i = 0; i < (faces1sidedCount + faces2sidedCount); i++)
        {
            faces[i].serialize(file);
        }

        /* Tracks for moving objects */

        if (DENIS_LEVEL_OBJECT_TYPE_MOVING == current_type)
        {
            i = *(int32_t*)"KEYS";

            file.readOrWrite(&i, 0x04);

            if (file.isInReadMode())
            {
                if (*(int32_t*)"KEYS" != i)
                {
                    throw ErrorMessage
                    (
                        "\"%s\": invalid keys magic.",
                        file.fileName.getText()
                    );
                }
            }

            if (file.isInReadMode())
            {
                if (nullptr != tracks)
                {
                    delete[](tracks);
                    tracksCount = 0;
                }
            }

            file.readOrWrite(&tracksCount, 0x04);

            if (file.isInReadMode())
            {
                if (tracksCount <= 0)
                {
                    throw ErrorMessage
                    (
                        "\"%s\": no tracks...",
                        file.fileName.getText()
                    );
                }

                tracks = new DenisLevelTrack [tracksCount];
            }

            for (i = 0; i < tracksCount; i++)
            {
                tracks[i].serialize(file);
            }
        }

        /* Unknown WORDS (must be at least one) */

        file.readOrWrite(&unknownWordsCount, 0x04);

        if (file.isInReadMode())
        {
            unknownWords = new int16_t [unknownWordsCount];
        }

        file.readOrWrite(unknownWords, (0x02 * unknownWordsCount));

        /* Display commands */

        displayCommands.serialize(file);
    }


    ////////////////////////////////////////////////////////////////
    // Level Object: convert from Kao1 to Kao2
    ////////////////////////////////////////////////////////////////

    void DenisLevelObject::convertToKao2
    (
        int32_t object_type,
        int32_t object_id,
        eGroup* parent_group,
        int32_t materials_count,
        eMaterial** materials_list
    )
    {
        char bufor[32];
        eString group_name;
        eGroup* test_group = nullptr;

        /********************************/
        /* Make a group of meshes */

        sprintf_s(bufor, 32, "#group of %d:%d:", object_type, object_id);

        group_name = bufor;
        group_name += name;

        test_group = new eGroup();
        test_group->incRef();

        test_group->setName(group_name);

        /********************************/
        /* Trying to figure out "eNode" flags... */

        test_group->setFlags(0x70000009); // 0x20000009

        /********************************/
        /* Convert display commands */

        displayCommands.convertToKao2
        (
            test_group,
            materials_count,
            materials_list,
            vertexCount,
            vertices,
            name
        );

        /********************************/
        /* Append this object */

        if (nullptr != parent_group)
        {
            parent_group->appendChild(test_group);
        }

        test_group->decRef();
    }

}
