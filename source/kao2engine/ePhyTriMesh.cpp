#include <kao2engine/ePhyTriMesh.h>
#include <kao2ar/Archive.h>

#include <kao2engine/eTransform.h>
#include <kao2engine/eTriMesh.h>
#include <kao2engine/eGeoSet.h>
#include <kao2engine/eMorpherMod.h>

#include <kao2engine/e3fXArray.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePhyTriMesh interface
    // <kao2.004B17A0> (constructor)
    // <kao2.004B1BC0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_PHYTRIMESH_TYPEINFO
    (
        E_PHYTRIMESH_ID,
        "ePhyTriMesh",
        &E_MODIFIER_TYPEINFO,
        []() -> eObject*
        {
            return new ePhyTriMesh(nullptr, nullptr);
        }
    );

    TypeInfo* ePhyTriMesh::getType()
    {
        return &E_PHYTRIMESH_TYPEINFO;
    }

    ePhyTriMesh::ePhyTriMesh(eTriMesh* x, eGeoSet* y)
    : eModifier()
    {
        /*[0x10]*/ vertices = nullptr;
        /*[0x14]*/ matrixCount = 0;
        /*[0x18]*/ matrixMaxLength = 0;
        /*[0x1C]*/ matrix = nullptr;
        /*[0x20]*/ unknown_20 = nullptr;
        /*[0x24]*/ unknown_24 = nullptr;
        /*[0x28]*/ morph = nullptr;

        /*[0x08]*/ tri = x;
        /*[0x0C]*/ geo = y;
    }

    ePhyTriMesh::~ePhyTriMesh()
    {
        int32_t i;

        morph->decRef();

        unknown_24->decRef();

        unknown_20->decRef();

        for (i = 0; i < matrixCount; i++)
        {
            matrix[i].bone->decRef();
        }

        vertices->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // Bone Structure
    ////////////////////////////////////////////////////////////////

    eBoneBase::eBoneBase()
    {
        int32_t i, j;

        bone = nullptr;

        for (i = 0; i < 4; i++)
        {
            for (j = 0; j < 4; j++)
            {
                if (i == j)
                {
                    matrix[i][j] = 1.0f;
                }
                else
                {
                    matrix[i][j] = 0;
                }
            }
        }
    }

    void eBoneBase::serializeBone(Archive &ar)
    {
        int32_t i, j;

        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&bone, &E_TRANSFORM_TYPEINFO);

        for (i = 0; i < 4; i++)
        {
            for (j = 0; j < 4; j++)
            {
                ar.readOrWrite(&(matrix[i][j]), 0x04);
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // ePhyTriMesh serialization
    // <kao2.004B1CE0>
    ////////////////////////////////////////////////////////////////
    void ePhyTriMesh::serialize(Archive &ar)
    {
        int32_t i;

        /* Vertices with bone weights */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&vertices, &E_GEOARRAY_EPHYVERTEX_TYPEINFO);

        /* Bones with matrices */

        if (ar.isInReadMode())
        {
            ar.readOrWrite(&matrixMaxLength, 0x04);

            if (nullptr != matrix)
            {
                delete[](matrix);
            }

            matrix = new eBoneBase [matrixMaxLength];

            for (i = 0; i < matrixMaxLength; i++)
            {
                matrix[i].serializeBone(ar);

                matrixCount = (i+1);
            }
        }
        else
        {
            ar.readOrWrite(&matrixCount, 0x04);

            for (i = 0; i < matrixCount; i++)
            {
                matrix[i].serializeBone(ar);
            }
        }

        /* eGeoSet link (empty in KAO_TW, required in KAO2) */

        ar.serialize((eObject**)&geo, &E_GEOSET_TYPEINFO);

        /* eTriMesh link */

        ar.serialize((eObject**)&tri, &E_TRIMESH_TYPEINFO);

        if (ar.isInReadMode())
        {
            if (nullptr == tri)
            {
                throw ErrorMessage
                (
                    "ePhyTriMesh::serialize():\n" \
                    "eTriMesh link cannot be empty!"
                );
            }
            else
            {
                geo = tri->getGeoSetLink();
            }
        }

        /* [0x24] [0x20] unknown */

        ArFunctions::serialize_e3fXArray(ar, &unknown_24);
        ArFunctions::serialize_e3fXArray(ar, &unknown_20);

        /* Sanity check */

        if (ar.isInReadMode())
        {
            if (matrixCount > 40)
            {
                throw ErrorMessage
                (
                    "ePhyTriMesh::serialize():\n" \
                    "Too many matrices [max 40]."
                );
            }
        }

        /* MorpherMod */

        if (ar.getVersion() >= 0x7B)
        {
            ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&morph, &E_MORPHERMOD_TYPEINFO);
        }
        else
        {
            if (nullptr != morph)
            {
                morph->decRef();
                morph = nullptr;
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // ePhyTriMesh: print
    ////////////////////////////////////////////////////////////////
    eString ePhyTriMesh::getLogPrintMessage()
    {
        int32_t i;

        eString result = eObject::getLogPrintMessage();

        result += "\n";

        for (i = 0; i < matrixCount; i++)
        {
            result += "\n bone: ";

            result += matrix[i].bone->getStringRepresentation();
        }

        return result;
    }

}
