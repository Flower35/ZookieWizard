#include <ElephantEngine/ePhyTriMesh.h>
#include <ElephantBase/Archive.h>

#include <ElephantEngine/eTransform.h>
#include <ElephantEngine/eTriMesh.h>
#include <ElephantEngine/eGeoSet.h>
#include <ElephantEngine/eMorpherMod.h>

#include <ElephantEngine/e3fXArray.h>

#include <ElephantEngine/Log.h>
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

    const TypeInfo* ePhyTriMesh::getType() const
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

        if (ar.getVersion() < 0x9E)
        {
            /* Bone weights for each vertex */
            ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&phyVertices, &E_GEOARRAY_EPHYVERTEX_TYPEINFO);

            if (nullptr == phyVertices)
            {
                throw ErrorMessage
                (
                    "ePhyTriMesh::serialize():\n" \
                    "Missing the PhyVertices Array!"
                );
            }
        }

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

        /* "eGeoSet" link (empty from "KaoTW" onwards, required in "Kao2") */

        ar.serialize((eObject**)&geosetLink, &E_GEOSET_TYPEINFO);

        /* "eTriMesh" link */

        ar.serialize((eObject**)&trimeshLink, &E_TRIMESH_TYPEINFO);

        /* ASSERTION */

        if (!ar.assertLastSerializedNode(trimeshLink))
        {
            throw ErrorMessage
            (
                "ePhyTriMesh::serialize():\n" \
                "incorrect TriMesh linked to this PhyTriMesh!"
            );
        }

        if (ar.isInReadMode())
        {
            if (nullptr == trimeshLink)
            {
                throw ErrorMessage
                (
                    "ePhyTriMesh::serialize():\n" \
                    "eTriMesh link cannot be empty!"
                );
            }
            else
            {
                geosetLink = trimeshLink->getGeoset();

                if (nullptr == geosetLink)
                {
                    throw ErrorMessage
                    (
                        "ePhyTriMesh::serialize():\n" \
                        "eGeoSet link cannot be empty!"
                    );
                }
            }
        }

        /* Serializing default vertices and solving the compatibility issue */

        if (ar.getVersion() < 0x9E)
        {
            ArFunctions::serialize_e3fXArray(ar, &defaultNormals);

            if (nullptr == defaultNormals)
            {
                throw ErrorMessage
                (
                    "ePhyTriMesh::serialize():\n"
                    "Missing the Default Normals Array!"
                );
            }

            ArFunctions::serialize_e3fXArray(ar, &defaultVertices);

            if (nullptr == defaultVertices)
            {
                throw ErrorMessage
                (
                    "ePhyTriMesh::serialize():\n"
                    "Missing the Default Vertices Array!"
                );
            }

            if (ar.isInReadMode())
            {
                geosetLink->setNormalsArray(1, defaultNormals);
                geosetLink->setVerticesArray(1, defaultVertices);
                geosetLink->setPhyVertices(phyVertices);
            }
        }
        else
        {
            if (ar.isInReadMode())
            {
                if (nullptr != (defaultNormals = geosetLink->getNormalsArray(1)))
                {
                    defaultNormals->incRef();
                }
                else
                {
                    throw ErrorMessage
                    (
                        "ePhyTriMesh::serialize():\n"
                        "Default Normals Array missing from \"eGeoSet\"! (ar version >= 158)"
                    );
                }

                if (nullptr != (defaultVertices = geosetLink->getVerticesArray(1)))
                {
                    defaultVertices->incRef();
                }
                else
                {
                    throw ErrorMessage
                    (
                        "ePhyTriMesh::serialize():\n"
                        "Default Vertices Array missing from \"eGeoSet\"! (ar version >= 158)"
                    );
                }

                if (nullptr != (phyVertices = geosetLink->getPhyVertices()))
                {
                    phyVertices->incRef();
                }
                else
                {
                    throw ErrorMessage
                    (
                        "ePhyTriMesh::serialize():\n"
                        "PhyVertices Array missing from \"eGeoSet\"! (ar version >= 158)"
                    );
                }
            }
        }

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
            int length = phyVertices->getLength();

            if (false == (test = (defaultVertices->getLength() != length)))
            {
                if (false == (test = (defaultNormals->getLength() != length)))
                {
                    if (false == (test = (geosetLink->getVerticesArray(0)->getLength() != length)))
                    {
                        test = (geosetLink->getNormalsArray(0)->getLength() != length);
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
    // ePhyTriMesh: dump object tree as a JSON value
    ////////////////////////////////////////////////////////////////
    void ePhyTriMesh::dumpTreeAsJsonValue(JsonValue& output, bool dumpChildNodes) const
    {
        int32_t a, b;
        eNode* trimesh_parent = trimeshLink->getParentNode();

        output.setType(JSON_VALUETYPE_OBJECT);
        JsonObject* jsonObjectRef = (JsonObject *) output.getValue();

        /* "ePhyTriMesh": bones */

        if (bonesCount > 0)
        {
            JsonArray jsonBones;
            JsonObject jsonBone;

            JsonArray jsonMatrixCols;
            JsonArray jsonMatrixRow;

            for (a = 0; a < bonesCount; a++)
            {
                jsonBone.clear();

                /* Bone path relative to "eTriMesh" parent */

                jsonBone.appendKeyValue("path", bones[a].xform->getArchivePath(trimesh_parent));

                /* Inverse Bind Matrix */

                jsonMatrixCols.clear();

                for (b = 0; b < 4; b++)
                {
                    jsonMatrixRow.clear();

                    jsonMatrixRow.appendValue(bones[a].matrix.m[b][0]);
                    jsonMatrixRow.appendValue(bones[a].matrix.m[b][1]);
                    jsonMatrixRow.appendValue(bones[a].matrix.m[b][2]);
                    jsonMatrixRow.appendValue(bones[a].matrix.m[b][3]);

                    jsonMatrixCols.appendValue(jsonMatrixRow);
                }

                jsonBone.appendKeyValue("invBindMatrix", jsonMatrixCols);

                jsonBones.appendValue(jsonBone);
            }
            
            jsonObjectRef->appendKeyValue("bones", jsonBones);
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

        /* (--TODO--) update "eMorhperMod"! */
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

        /* (--TODO--) check "eMorpherMod" <kao2.006030C0> */

        /* Load prior transformation with inverse matrix */

        if (nullptr != (test_xform = trimeshLink->getPreviousTransform()))
        {
            test_srp = test_xform->getXForm(true);
            parent_matrix = test_srp.getInverseMatrix();
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

        ePoint4 new_vertex;
        ePoint4 new_normal;
        ePoint4 temp_vertex;
        ePoint4 temp_normal;

        /* Set arrays */

        int32_t length = phyVertices->getLength();
        ePhyVertex* vertex_weights = phyVertices->getData();

        ePoint4* source_vertices = defaultVertices->getData();
        ePoint4* source_normals = defaultNormals->getData();
        ePoint4* destination_vertices = geosetLink->getVerticesArray(0)->getData();
        ePoint4* destination_normals = geosetLink->getNormalsArray(0)->getData();

        if (nullptr == source_vertices)
        {
            source_vertices = destination_vertices;
        }

        if (nullptr == source_normals)
        {
            source_normals = destination_normals;
        }

        /* (--TODO--) Skip "eMorhperMod" because it will result in reusing same vertices */
        /* This will make sense once we finish "eMorpherMod" call from matrices function */
        if ((false) && (nullptr != morph))
        {
            source_vertices = destination_vertices;
            source_normals = destination_normals;
        }

        if ((nullptr == destination_vertices) || (nullptr == destination_normals))
        {
            return;
        }

        /* Begin the loop */

        for (i = 0; i < length; i++)
        {
            temp_vertex = source_vertices[i];
            temp_normal = source_normals[i];

            new_vertex = {0};
            new_normal = {0};

            for (j = 0; j < 3; j++)
            {
                bone_index = vertex_weights[i].index[j];

                if (!(0x80 & bone_index))
                {
                    bone_weight = vertex_weights[i].weight[j];

                    new_vertex = ((theBonesMatrices[bone_index] * temp_vertex) * bone_weight) + new_vertex;
                    new_normal = ((theBonesMatrices[bone_index] * temp_normal) * bone_weight) + new_normal;
                }
                else
                {
                    if (0 == j)
                    {
                        // Kao2 actually expects all vertices to be rigged
                        new_vertex = temp_vertex;
                        new_normal = temp_normal;
                    }

                    j = 3; // break loop
                }
            }

            /* Vertices Safety */

            new_vertex.w = 1.0f;

            new_normal.w = 0;
            new_normal.normalize();

            /* This replaces data in "eGeoSet" arrays */

            destination_vertices[i] = new_vertex;
            destination_normals[i] = new_normal;
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

        if (nullptr != trimeshLink)
        {
            test_xform = trimeshLink->getPreviousTransform();

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
    // ePhyTriMesh: get or ser the Morpher Modifier
    ////////////////////////////////////////////////////////////////

    eMorpherMod* ePhyTriMesh::getMorpherModifier() const
    {
        return morph;
    }

    void ePhyTriMesh::setMorpherModifier(eMorpherMod* new_morpher_mod)
    {
        if (new_morpher_mod != morph)
        {
            morph->decRef();

            morph = new_morpher_mod;

            if (nullptr != morph)
            {
                morph->incRef();
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // ePhyTriMesh: clear this object
    ////////////////////////////////////////////////////////////////
    void ePhyTriMesh::clearNewPhyTriMesh(eTriMesh* x, eGeoSet* y)
    {
        /*[0x10]*/ phyVertices = nullptr;
        /*[0x14]*/ bonesCount = 0;
        /*[0x18]*/ bonesMaxLength = 0;
        /*[0x1C]*/ bones = nullptr;
        /*[0x20]*/ defaultVertices = nullptr;
        /*[0x24]*/ defaultNormals = nullptr;
        /*[0x28]*/ morph = nullptr;

        /*[0x08]*/ trimeshLink = x;
        /*[0x0C]*/ geosetLink = y;
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

        phyVertices->decRef();
        phyVertices = nullptr;
    }

}
