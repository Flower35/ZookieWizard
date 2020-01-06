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
        /*[0x14]*/ bonesCount = 0;
        /*[0x18]*/ bonesMaxLength = 0;
        /*[0x1C]*/ bones = nullptr;
        /*[0x20]*/ defaultVertices = nullptr;
        /*[0x24]*/ defaultNormals = nullptr;
        /*[0x28]*/ morph = nullptr;

        /*[0x08]*/ tri = x;
        /*[0x0C]*/ geo = y;
    }

    ePhyTriMesh::~ePhyTriMesh()
    {
        int32_t i;

        morph->decRef();

        defaultNormals->decRef();

        defaultVertices->decRef();

        for (i = 0; i < bonesCount; i++)
        {
            bones[i].xform->decRef();
        }

        vertices->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // Bone Structure
    ////////////////////////////////////////////////////////////////

    eBoneBase::eBoneBase()
    {
        xform = nullptr;
    }

    void eBoneBase::serializeBone(Archive &ar)
    {
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&xform, &E_TRANSFORM_TYPEINFO);

        /* Seiralize transposed 4x4 matrix */

        matrix.serialize(ar);
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
            ar.readOrWrite(&bonesMaxLength, 0x04);

            if (nullptr != bones)
            {
                delete[](bones);
            }

            bones = new eBoneBase [bonesMaxLength];

            for (i = 0; i < bonesMaxLength; i++)
            {
                bones[i].serializeBone(ar);

                bonesCount = (i+1);
            }
        }
        else
        {
            ar.readOrWrite(&bonesCount, 0x04);

            for (i = 0; i < bonesCount; i++)
            {
                bones[i].serializeBone(ar);
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

        /* [0x24] [0x20] serialize default normals and default vertices */

        ArFunctions::serialize_e3fXArray(ar, &defaultNormals);
        ArFunctions::serialize_e3fXArray(ar, &defaultVertices);

        /* Sanity check */

        if (ar.isInReadMode())
        {
            if (bonesCount > 40)
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

        for (i = 0; i < bonesCount; i++)
        {
            result += "\n bone: ";

            result += bones[i].xform->getStringRepresentation();
        }

        return result;
    }


    ////////////////////////////////////////////////////////////////
    // ePhyTriMesh: prepare matrices
    // <kao2.004B1F70>
    ////////////////////////////////////////////////////////////////
    void ePhyTriMesh::prepareMatrices(int32_t draw_flags)
    {
        int32_t i;
        
        eMatrix4x4 xform_matrix;
        eMatrix4x4 parent_matrix;

        eTransform* test_transform;

        /* (--dsp--) check "eMorpherMod" <kao2.006030C0> */

        /* Load prior transformation with inverse matrix */

        if (nullptr != tri)
        {
            test_transform = tri->getPreviousTransform();

            if (nullptr != test_transform)
            {
                parent_matrix = test_transform->getXForm().getInverseMatrix();
            }
        }

        /* Prepare bone matrices */

        for (i = 0; i < bonesCount; i++)
        {
            if (GUI::drawFlags::DRAW_FLAG_ANIMS & draw_flags)
            {
                xform_matrix = bones[i].xform->getXForm().getMatrix();

                theBonesMatrices[i] = parent_matrix * (xform_matrix * bones[i].matrix);
            }
            else
            {
                theBonesMatrices[i] = xform_matrix;
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // ePhyTriMesh: animate vertices
    // <kao2.004BDE90>
    ////////////////////////////////////////////////////////////////
    void ePhyTriMesh::animateVertices()
    {
        int32_t i, j;
        int32_t length;
        int32_t bone_index;
        float bone_weight;
        bool test;

        ePoint4 newVertex;
        ePoint4 newNormal;
        ePoint4 tempVertex;
        ePoint4 tempNormal;

        ePhyVertex* phyVertices;
        ePoint4* sourceVertices;
        ePoint4* sourceNormals;
        ePoint4* destinationVertices;
        ePoint4* destinationNormals;

        /* Sanity check */

        test = false;
        length = vertices->getLength();

        i = defaultVertices->getLength();
        if ((!test) && (0 != i))
        {
            if (length != i)
            {
                test = true;
            }
        }

        i = defaultNormals->getLength();
        if ((!test) && (0 != i))
        {
            if (length != i)
            {
                test = true;
            }
        }

        i = geo->getVerticesArray()->getLength();
        if ((!test) && (0 != i))
        {
            if (length != i)
            {
                test = true;
            }
        }

        i = geo->getNormalsArray()->getLength();
        if ((!test) && (0 != i))
        {
            if (length != i)
            {
                test = true;
            }
        }

        if (test)
        {
            throw ErrorMessage
            (
                "ePhyTriMesh::animateVertices():\n" \
                "invalid vertices count!"
            );
            
            return;
        }

        /* Set arrays */

        phyVertices = vertices->getData();

        sourceVertices = defaultVertices->getData();
        sourceNormals = defaultNormals->getData();
        destinationVertices = geo->getVerticesArray()->getData();
        destinationNormals = geo->getNormalsArray()->getData();

        if (nullptr == sourceVertices)
        {
            sourceVertices = destinationVertices;
        }

        if (nullptr == sourceNormals)
        {
            sourceNormals = destinationNormals;
        }

        /* (--dsp--) Skip "eMorhperMod" because it will result in reusing same vertices */
        /* This will make sense once we finish "eMorpherMod" call from matrices function */
        if ((false) && (nullptr != morph))
        {
            sourceVertices = destinationVertices;
            sourceNormals = destinationNormals;
        }

        /* Begin the loop */

        for (i = 0; i < length; i++)
        {
            tempVertex = sourceVertices[i];
            tempNormal = sourceNormals[i];

            newVertex = {0};
            newNormal = {0};

            for (j = 0; j < 3; j++)
            {
                bone_index = phyVertices[i].index[j];

                if (0xFF != bone_index)
                {
                    bone_weight = phyVertices[i].weight[j];

                    newVertex = ((theBonesMatrices[bone_index] * tempVertex) * bone_weight) + newVertex;
                    newNormal = ((theBonesMatrices[bone_index] * tempNormal) * bone_weight) + newNormal;
                }
                else
                {
                    if (0 == j)
                    {
                        // Kao2 actually expects all vertices to be rigged
                        newVertex = tempVertex;
                        newNormal = tempNormal;
                    }

                    j = 3; // break loop
                }
            }

            /* Vertices Safety */

            newVertex.w = 1.0f;

            newNormal.w = 0;
            newNormal.normalize();

            /* This replaces "eGeoSet" arrays */

            destinationVertices[i] = newVertex;
            destinationNormals[i] = newNormal;
        }
    }

}
