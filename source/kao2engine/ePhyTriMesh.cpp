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
        morph->decRef();

        defaultNormals->decRef();

        defaultVertices->decRef();

        deleteBones();

        vertices->decRef();
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
    // ePhyTriMesh: destroy bones (required for correct "eTransform" dereferencing)
    ////////////////////////////////////////////////////////////////
    void ePhyTriMesh::deleteBones()
    {
        int32_t i;

        for (i = 0; i < bonesCount; i++)
        {
            bones[i].xform->decRef();
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
    // ePhyTriMesh: COLLADA exporting
    ////////////////////////////////////////////////////////////////
    void ePhyTriMesh::writeNodeToXmlFile(ColladaExporter &exporter) const
    {
        int32_t i, j, k;
        int32_t armature_id;
        int32_t total_weights;
        char bufor[64];

        eMatrix4x4 parent_matrix;
        eTransform* test_transform;

        int32_t v_length = vertices->getLength();
        ePhyVertex* v_data = vertices->getData();

        if (exporter.objectRefAlreadyExists(COLLADA_EXPORTER_OBJ_ARMATURE, this))
        {
            /* Armature was already exported */
            return;
        }
        exporter.openTag("controller");

        armature_id = exporter.getObjectRefId(COLLADA_EXPORTER_OBJ_ARMATURE, this, true);
        sprintf_s(bufor, 64, "Armature%d", armature_id);
        exporter.insertTagAttrib("id", bufor);

        exporter.openTag("skin");

        i = exporter.getObjectRefId(COLLADA_EXPORTER_OBJ_GEOMETRY, geo, false);
        sprintf_s(bufor, 64, "#TriMesh%d", i);
        exporter.insertTagAttrib("source", bufor);

        /********************************/
        /* Info about position and orientation of the base mesh before binding */

        if (nullptr != tri)
        {
            test_transform = tri->getPreviousTransform();

            if (nullptr != test_transform)
            {
                parent_matrix = test_transform->getXForm(true).getMatrix();

                exporter.openTag("bind_shape_matrix");

                for (i = 0; i < 4; i++)
                {
                    sprintf_s
                    (
                        bufor, 64, "%f %f %f %f",
                        parent_matrix.m[i][0], parent_matrix.m[i][1],
                        parent_matrix.m[i][2], parent_matrix.m[i][3]
                    );

                    exporter.writeInsideTag(bufor);
                }

                exporter.closeTag(); // "bind_shape_matrix"
            }
        }

        /********************************/
        /* List of joints */

        exporter.openTag("source");

        sprintf_s(bufor, 64, "Armature%d-joints", armature_id);
        exporter.insertTagAttrib("id", bufor);

        exporter.openTag("Name_array");

        sprintf_s(bufor, 64, "Armature%d-joints-array", armature_id);
        exporter.insertTagAttrib("id", bufor);
        sprintf_s(bufor, 64, "%d", bonesCount);
        exporter.insertTagAttrib("count", bufor);

        for (i = 0; i < bonesCount; i++)
        {
            /* Upon instantiation of a skin controller, the <skeleton> elements define where to start the SID lookup */
            j = exporter.getObjectRefId(COLLADA_EXPORTER_OBJ_NODE, bones[i].xform, true);
            sprintf_s(bufor, 64, "Node%d", j);

            exporter.writeInsideTag(bufor);
        }

        exporter.closeTag(); // "Name_array"

        exporter.openTag("technique_common");
        exporter.openTag("accessor");

        sprintf_s(bufor, 64, "#Armature%d-joints-array", armature_id);
        exporter.insertTagAttrib("source", bufor);
        sprintf_s(bufor, 64, "%d", bonesCount);
        exporter.insertTagAttrib("count", bufor);
        exporter.insertTagAttrib("stride", "1");

        exporter.openTag("param");
        exporter.insertTagAttrib("name", "JOINT");
        exporter.insertTagAttrib("type", "name");

        exporter.closeTag(); // "param"
        exporter.closeTag(); // "accessor"
        exporter.closeTag(); // "technique_common"
        exporter.closeTag(); // "source"

        /********************************/
        /* List of inverse bind matrices */

        exporter.openTag("source");

        sprintf_s(bufor, 64, "Armature%d-bind_poses", armature_id);
        exporter.insertTagAttrib("id", bufor);

        exporter.openTag("float_array");

        sprintf_s(bufor, 64, "Armature%d-bind_poses-array", armature_id);
        exporter.insertTagAttrib("id", bufor);
        sprintf_s(bufor, 64, "%d", (16 * bonesCount));
        exporter.insertTagAttrib("count", bufor);

        for (i = 0; i < bonesCount; i++)
        {
            for (j = 0; j < 4; j++)
            {
                sprintf_s
                (
                    bufor, 64, "%f %f %f %f",
                    bones[i].matrix.m[j][0], bones[i].matrix.m[j][1],
                    bones[i].matrix.m[j][2], bones[i].matrix.m[j][3]
                );

                exporter.writeInsideTag(bufor);
            }
        }

        exporter.closeTag(); // "float_array"

        exporter.openTag("technique_common");
        exporter.openTag("accessor");

        sprintf_s(bufor, 64, "#Armature%d-bind_poses-array", armature_id);
        exporter.insertTagAttrib("source", bufor);
        sprintf_s(bufor, 64, "%d", bonesCount);
        exporter.insertTagAttrib("count", bufor);
        exporter.insertTagAttrib("stride", "16");

        exporter.openTag("param");
        exporter.insertTagAttrib("name", "TRANSFORM");
        exporter.insertTagAttrib("type", "float4x4");

        exporter.closeTag(); // "param"
        exporter.closeTag(); // "accessor"
        exporter.closeTag(); // "technique_common"
        exporter.closeTag(); // "source"

        /********************************/
        /* List of weights */

        total_weights = 0;

        for (i = 0; i < v_length; i++)
        {
            for (j = 0; j < 3; j++)
            {
                if (0xFF != v_data[i].index[j])
                {
                    total_weights++;
                }
                else
                {
                    j = 3; // explicit break
                }
            }
        }

        exporter.openTag("source");

        sprintf_s(bufor, 64, "Armature%d-weights", armature_id);
        exporter.insertTagAttrib("id", bufor);

        exporter.openTag("float_array");

        sprintf_s(bufor, 64, "Armature%d-weights-array", armature_id);
        exporter.insertTagAttrib("id", bufor);
        sprintf_s(bufor, 64, "%d", total_weights);
        exporter.insertTagAttrib("count", bufor);

        for (i = 0; i < v_length; i++)
        {
            for (j = 0; j < 3; j++)
            {
                if (0xFF != v_data[i].index[j])
                {
                    sprintf_s(bufor, 64, "%f", v_data[i].weight[j]);

                    exporter.writeInsideTag(bufor);
                }
                else
                {
                    j = 3; // explicit break
                }
            }
        }

        exporter.closeTag(); // "float_array"

        exporter.openTag("technique_common");
        exporter.openTag("accessor");

        sprintf_s(bufor, 64, "#Armature%d-weights-array", armature_id);
        exporter.insertTagAttrib("source", bufor);
        sprintf_s(bufor, 64, "%d", total_weights);
        exporter.insertTagAttrib("count", bufor);
        exporter.insertTagAttrib("stride", "1");

        exporter.openTag("param");
        exporter.insertTagAttrib("name", "WEIGHT");
        exporter.insertTagAttrib("type", "float");

        exporter.closeTag(); // "param"
        exporter.closeTag(); // "accessor"
        exporter.closeTag(); // "technique_common"
        exporter.closeTag(); // "source"

        /********************************/
        /* Association between joints and attribute data */

        exporter.openTag("joints");

        exporter.openTag("input");
        exporter.insertTagAttrib("semantic", "JOINT");

        sprintf_s(bufor, 64, "#Armature%d-joints", armature_id);
        exporter.insertTagAttrib("source", bufor);

        exporter.closeTag(); // "input"

        exporter.openTag("input");
        exporter.insertTagAttrib("semantic", "INV_BIND_MATRIX");

        sprintf_s(bufor, 64, "#Armature%d-bind_poses", armature_id);
        exporter.insertTagAttrib("source", bufor);

        exporter.closeTag(); // "input"

        exporter.closeTag(); // "joints"

        /********************************/
        /* Association between joints and attribute data */

        exporter.openTag("vertex_weights");

        sprintf_s(bufor, 64, "%d", v_length);
        exporter.insertTagAttrib("count", bufor);

        exporter.openTag("input");
        exporter.insertTagAttrib("semantic", "JOINT");

        sprintf_s(bufor, 64, "#Armature%d-joints", armature_id);
        exporter.insertTagAttrib("source", bufor);
        exporter.insertTagAttrib("offset", "0");

        exporter.closeTag(); // "input"

        exporter.openTag("input");
        exporter.insertTagAttrib("semantic", "WEIGHT");

        sprintf_s(bufor, 64, "#Armature%d-weights", armature_id);
        exporter.insertTagAttrib("source", bufor);
        exporter.insertTagAttrib("offset", "1");

        exporter.closeTag(); // "input"

        exporter.openTag("vcount");

        for (i = 0; i < v_length; i++)
        {
            k = 0;

            for (j = 0; j < 3; j++)
            {
                if (0xFF != v_data[i].index[j])
                {
                    k++;
                }
                else
                {
                    j = 3; // explicit break
                }
            }

            sprintf_s(bufor, 64, "%d", k);

            exporter.writeInsideTag(bufor);
        }

        exporter.closeTag(); // "vcount"

        exporter.openTag("v");

        k = 0;

        for (i = 0; i < v_length; i++)
        {
            for (j = 0; j < 3; j++)
            {
                if (0xFF != v_data[i].index[j])
                {
                    sprintf_s
                    (
                        bufor, 64, "%d %d",
                        v_data[i].index[j], k
                    );

                    k++;

                    exporter.writeInsideTag(bufor);
                }
                else
                {
                    j = 3; // explicit break
                }
            }
        }

        exporter.closeTag(); // "v"

        exporter.closeTag(); // "vertex_weights"

        /********************************/
        /* Close skinning elements */

        exporter.closeTag(); // "skin"
        exporter.closeTag(); // "controller"
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
    // ePhyTriMesh: prepare matrices
    // <kao2.004B1F70>
    ////////////////////////////////////////////////////////////////
    void ePhyTriMesh::prepareMatrices(bool update) const
    {
        int32_t i;

        eMatrix4x4 xform_matrix;
        eMatrix4x4 parent_matrix;

        eTransform* test_transform;

        /* (--dsp--) check "eMorpherMod" <kao2.006030C0> */

        /* Load prior transformation with inverse matrix */

        if (update && (nullptr != tri))
        {
            test_transform = tri->getPreviousTransform();

            if (nullptr != test_transform)
            {
                parent_matrix = test_transform->getXForm(true).getInverseMatrix();
            }
        }

        /* Prepare bone matrices */

        for (i = 0; i < bonesCount; i++)
        {
            if (update)
            {
                xform_matrix = bones[i].xform->getXForm(true).getMatrix();

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
    // ePhyTriMesh: sort bones array in correct order
    ////////////////////////////////////////////////////////////////
    void ePhyTriMesh::sortBoneIndices()
    {
        int32_t i, j, k;
        eTransform* test_xform;
        ePhyVertex* test_phyvertex;

        eTransform* xforms_parents[100];
        eTransform* xforms_queue[100];
        int32_t indices[100];

        eBoneBase bones_queue[40];

        /********************************/
        /* First bone in queue is the Root Bone */

        xforms_parents[0] = xforms_queue[0] = getArmatureParent();
        xforms_parents[0]->setTypeToJoint(true);

        /********************************/
        /* Itterate bones and place then in hierarchical order */

        i = 0; // parent counter [0 -> ? -> (-1)]
        k = 0; // queue counter [0 -> 40]
        indices[0] = 0; // children counter for i-th parent

        while (i >= 0)
        {
            while (indices[i] < xforms_parents[i]->getNodesCount())
            {
                test_xform = (eTransform*)xforms_parents[i]->getIthChild(indices[i]);

                indices[i]++;

                if (test_xform->getType()->checkHierarchy(&E_TRANSFORM_TYPEINFO))
                {
                    if (false == test_xform->isJointNode())
                    {
                        test_xform->setTypeToJoint(true);
                    }

                    i++;
                    k++;

                    if ((i >= 100) || (k >= 100))
                    {
                        throw ErrorMessage
                        (
                            "ePhyTriMesh::sortBoneIndices():\n" \
                            "too many eTransforms found! (max 100)"
                        );
                    }

                    indices[i] = 0;
                    xforms_parents[i] = test_xform;
                    xforms_queue[k] = test_xform;
                }
            }

            i--;
        }

        /********************************/
        /* Set new indices */

        k++; // number of xforms stored in hierarchical queue

        /* Deleting items from queue that don't exist in matrices array */
        i = 0;
        while (i < k)
        {
            for (j = 0; j < bonesCount; j++)
            {
                if (bones[j].xform == xforms_queue[i])
                {
                    j = bonesCount; // explicit break
                }
            }

            if (j <= bonesCount) // "eTransform" from queue not found
            {
                for (j = (i + 1); j < k; j++)
                {
                    xforms_queue[j - 1] = xforms_queue[j];
                }

                k--;
            }
            else
            {
                i++;
            }
        }

        if (k != bonesCount)
        {
            /* (--dsp--) "02_korzenie.ar" -> "dynia_³odyga_itd." */
            return;

            throw ErrorMessage
            (
                "ePhyTriMesh::sortBoneIndices():\n" \
                "bones count mismatch!"
            );
        }

        // i = current bone order
        // j = new index for i-th bone
        for (i = 0; i < bonesCount; i++)
        {
            indices[i] = (-1);

            for (j = 0; j < k; j++)
            {
                if (xforms_queue[j] == bones[i].xform)
                {
                    indices[i] = j;

                    j = k; // break
                }
            }

            if ((-1) == indices[i])
            {
                throw ErrorMessage
                (
                    "ePhyTriMesh::sortBoneIndices():\n" \
                    "bone \"%s\" not found!",
                    bones[i].xform->getStringRepresentation().getText()
                );
            }
        }

        /********************************/
        /* Shuffle actual bones */

        for (i = 0; i < bonesCount; i++)
        {
            bones_queue[indices[i]] = bones[i];
        }

        for (i = 0; i < bonesCount; i++)
        {
            bones[i] = bones_queue[i];
        }

        /********************************/
        /* Update "ePhyVertex" joint indices */

        for (i = 0; i < vertices->getLength(); i++)
        {
            test_phyvertex = &(vertices->getData()[i]);

            for (k = 0; k < 3; k++)
            {
                j = test_phyvertex->index[k];

                if (j >= 0)
                {
                    test_phyvertex->index[k] = indices[j];
                }
            }
        }
    }

}
