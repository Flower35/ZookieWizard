#include <kao2engine/ePhyTriMesh.h>
#include <kao2ar/Archive.h>

#include <kao2engine/eTransform.h>
#include <kao2engine/eTriMesh.h>
#include <kao2engine/eGeoSet.h>
#include <kao2engine/eMorpherMod.h>

#include <kao2engine/e3fXArray.h>

#include <kao2engine/Log.h>
#include <utilities/ColladaExporter.h>

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

    TypeInfo* ePhyTriMesh::getType() const
    {
        return &E_PHYTRIMESH_TYPEINFO;
    }

    ePhyTriMesh::ePhyTriMesh(eTriMesh* x, eGeoSet* y)
    : eModifier()
    {
        clearNewPhyTriMesh(x, y);
    }

    ePhyTriMesh::~ePhyTriMesh()
    {
        clearExistingPhyTriMesh();
    }


    ////////////////////////////////////////////////////////////////
    // ePhyTriMesh: cloning the object
    ////////////////////////////////////////////////////////////////

    void ePhyTriMesh::createFromOtherObject(const ePhyTriMesh &other)
    {
        throw ErrorMessage
        (
            "CRITICAL ERROR while cloning the \"ePhyTriMesh\" object:\n" \
            "cloning << physical triangular meshes >> without context is not supported!!!"
        );
    }

    ePhyTriMesh::ePhyTriMesh(const ePhyTriMesh &other)
    : eModifier(other)
    {
        clearNewPhyTriMesh(nullptr, nullptr);

        /****************/

        createFromOtherObject(other);
    }

    ePhyTriMesh& ePhyTriMesh::operator = (const ePhyTriMesh &other)
    {
        if ((&other) != this)
        {
            eModifier::operator = (other);

            /****************/

            clearExistingPhyTriMesh();

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* ePhyTriMesh::cloneFromMe() const
    {
        return new ePhyTriMesh(*this);
    }


    ////////////////////////////////////////////////////////////////
    // Bone Structure
    // <kao2.004B1D70> (serialization)
    ////////////////////////////////////////////////////////////////

    eBoneBase::eBoneBase()
    {
        xform = nullptr;
    }

    void eBoneBase::serializeBone(Archive &ar)
    {
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&xform, &E_TRANSFORM_TYPEINFO);

        xform->setTypeToJoint(true);

        /* Serialize transposed 4x4 matrix */

        matrix.serialize(ar);
    }


    ////////////////////////////////////////////////////////////////
    // ePhyTriMesh: serialization
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
                geo = tri->getGeoset();
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

            bool test = false;
            int length = vertices->getLength();

            if (false == (test = (defaultVertices->getLength() != length)))
            {
                if (false == (test = (defaultNormals->getLength() != length)))
                {
                    if (false == (test = (geo->getVerticesArray()->getLength() != length)))
                    {
                        test = (geo->getNormalsArray()->getLength() != length);
                    }
                }
            }

            if (true == test)
            {
                throw ErrorMessage
                (
                    "ePhyTriMesh::serialize():\n" \
                    "invalid vertices count!"
                );

                return;
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
    eString ePhyTriMesh::getLogPrintMessage() const
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
    // ePhyTriMesh: export readable structure
    ////////////////////////////////////////////////////////////////
    void ePhyTriMesh::writeStructureToTextFile(FileOperator &file, int32_t indentation, bool group_written) const
    {
        int32_t a, b;
        char bufor[2 * LARGE_BUFFER_SIZE];
        eNode* trimesh_parent = nullptr;
        eString bone_path;

        if (nullptr != tri)
        {
            trimesh_parent = tri->getParentNode();
        }

        for (a = 0; a < bonesCount; a++)
        {
            /* 1. Print bone path relative to "eTriMesh" parent */

            bone_path = bones[a].xform->getArchivePath(trimesh_parent);

            sprintf_s
            (
                bufor, (2 * LARGE_BUFFER_SIZE),
                " - bone [%d]: \"%s\"",
                a,
                bone_path.getText()
            );

            ArFunctions::writeIndentation(file, indentation);
            file << bufor;
            ArFunctions::writeNewLine(file, 0);

            /* 2. Print the Inverse Bind Matrix */

            ArFunctions::writeIndentation(file, indentation);
            file << " - inv bind matrix: [";

            for (b = 0; b < 4; b++)
            {
                sprintf_s
                (
                    bufor, (2 * LARGE_BUFFER_SIZE),
                    "[%f, %f, %f, %f]",
                    bones[a].matrix.m[b][0],
                    bones[a].matrix.m[b][1],
                    bones[a].matrix.m[b][2],
                    bones[a].matrix.m[b][3]
                );

                file << bufor;

                if (b < 3)
                {
                    file << ", ";
                }
            }

            file << "]";
            ArFunctions::writeNewLine(file, 0);
        }
    }


    ////////////////////////////////////////////////////////////////
    // ePhyTriMesh: destroy bones (required for correct "eTransform" dereferencing)
    ////////////////////////////////////////////////////////////////
    void ePhyTriMesh::deleteBones()
    {
        for (int32_t a = 0; a < bonesCount; a++)
        {
            bones[a].xform->decRef();
            bones[a].xform = nullptr;
        }

        if (nullptr != bones)
        {
            delete[](bones);
            bones = nullptr;
        }

        bonesCount = 0;
        bonesMaxLength = 0;
    }


    ////////////////////////////////////////////////////////////////
    // ePhyTriMesh: transform default vertices and default normals
    ////////////////////////////////////////////////////////////////
    void ePhyTriMesh::transformVertices(eSRP &new_transform)
    {
        int32_t a, b, vertices_length;
        ePoint4* vertices_data;
        eMatrix4x4 matrix = new_transform.getMatrix();

        const eGeoArray<ePoint4>* arrays[2] = {defaultVertices, defaultNormals};

        for (a = 0; a < 2; a++)
        {
            vertices_length = arrays[a]->getLength();
            vertices_data = arrays[a]->getData();

            if (nullptr != vertices_data)
            {
                for (b = 0; b < vertices_length; b++)
                {
                    vertices_data[b] = matrix * vertices_data[b];
                }
            }
        }

        /* (--dsp--) update "eMorhperMod"! */
    }


    ////////////////////////////////////////////////////////////////
    // ePhyTriMesh: prepare matrices
    // <kao2.004B1F70>
    ////////////////////////////////////////////////////////////////
    void ePhyTriMesh::prepareMatrices(bool update) const
    {
        int32_t i;

        eMatrix4x4 bone_xform_matrix;
        eMatrix4x4 parent_matrix;

        eTransform* test_xform;
        eSRP test_srp;

        /* (--dsp--) check "eMorpherMod" <kao2.006030C0> */

        /* Load prior transformation with inverse matrix */

        if (nullptr != tri)
        {
            if (nullptr != (test_xform = tri->getPreviousTransform()))
            {
                test_srp = test_xform->getXForm(true);
                parent_matrix = test_srp.getInverseMatrix();
            }
        }

        /* Prepare bone matrices */

        if (update)
        {
            for (i = 0; i < bonesCount; i++)
            {
                bone_xform_matrix = bones[i].xform->getXForm(true).getMatrix();

                theBonesMatrices[i] = parent_matrix * (bone_xform_matrix * bones[i].matrix);
            }
        }
        else
        {
            parent_matrix.m[0][3] = 0;
            parent_matrix.m[1][3] = 0;
            parent_matrix.m[2][3] = 0;

            for (i = 0; i < bonesCount; i++)
            {
                theBonesMatrices[i] = parent_matrix;
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
        int32_t bone_index;
        float bone_weight;

        ePoint4 newVertex;
        ePoint4 newNormal;
        ePoint4 tempVertex;
        ePoint4 tempNormal;

        /* Set arrays */

        int32_t length = vertices->getLength();
        ePhyVertex* phyVertices = vertices->getData();

        ePoint4* sourceVertices = defaultVertices->getData();
        ePoint4* sourceNormals = defaultNormals->getData();
        ePoint4* destinationVertices = geo->getVerticesArray()->getData();
        ePoint4* destinationNormals = geo->getNormalsArray()->getData();

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

        if ((nullptr == destinationVertices) || (nullptr == destinationNormals))
        {
            return;
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

                if (!(0x80 & bone_index))
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


    ////////////////////////////////////////////////////////////////
    // ePhyTriMesh: get first bone reference
    ////////////////////////////////////////////////////////////////
    eTransform* ePhyTriMesh::getArmatureParent() const
    {
        eTransform* last_bone = nullptr;
        eTransform* test_xform = nullptr;

        /* Bones in array are not sorted by default! */

        if (nullptr != tri)
        {
            test_xform = tri->getPreviousTransform();

            if (nullptr != test_xform)
            {
                return test_xform;
            }
        }

        if (bonesCount > 0)
        {
            test_xform = bones[0].xform;
        }

        while (nullptr != test_xform)
        {
            if (test_xform->isJointNode())
            {
                last_bone = test_xform;
                test_xform = (eTransform*)test_xform->getParentNode();

                if (nullptr != test_xform)
                {
                    if (false == test_xform->getType()->checkHierarchy(&E_TRANSFORM_TYPEINFO))
                    {
                        test_xform = nullptr;
                    }
                }
            }
            else
            {
                test_xform = nullptr;
            }
        }

        return last_bone;
    }


    ////////////////////////////////////////////////////////////////
    // ePhyTriMesh: clear this object
    ////////////////////////////////////////////////////////////////
    void ePhyTriMesh::clearNewPhyTriMesh(eTriMesh* x, eGeoSet* y)
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


    ////////////////////////////////////////////////////////////////
    // ePhyTriMesh: clear already existing object
    ////////////////////////////////////////////////////////////////
    void ePhyTriMesh::clearExistingPhyTriMesh()
    {
        morph->decRef();
        morph = nullptr;

        defaultNormals->decRef();
        defaultNormals = nullptr;

        defaultVertices->decRef();
        defaultVertices = nullptr;

        deleteBones();

        vertices->decRef();
        vertices = nullptr;
    }

}
