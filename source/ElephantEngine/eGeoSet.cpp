#include <ElephantEngine/eGeoSet.h>
#include <ElephantBase/Archive.h>

#include <ElephantEngine/e3fXArray.h>
#include <ElephantEngine/ePhyTriMesh.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eGeoSet interface
    // <kao2.00469990> (constructor)
    // <kao2.0046A050> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_GEOSET_TYPEINFO
    (
        E_GEOSET_ID,
        "eGeoSet",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return new eGeoSet;
        }
    );

    TypeInfo* eGeoSet::getType() const
    {
        return &E_GEOSET_TYPEINFO;
    }

    eGeoSet::eGeoSet()
    : eRefCounter()
    {
        int32_t i;

        /* [0x14] */ indicesOffsets = nullptr;
        /* [0x18] */ indicesArray = nullptr;

        /*[0x1C-0x20]*/
        for (i = 0; i < 2; i++)
        {
            verticesArray[i] = nullptr;
        }

        /*[0x24-0x28]*/
        for (i = 0; i < 2; i++)
        {
            normalsArray[i] = nullptr;
        }

        /*[0x2C-0x38]*/
        for (i = 0; i < 4; i++)
        {
            texCoordsArray[i] = nullptr;
        }

        /*[0x3C]*/ colorsArray = nullptr;
        /*[0x58]*/ phy = nullptr;
        /*[0x5C]*/ aabbTree = nullptr;

        /*[0x08]*/ unknown_08 = 0;
        /*[0x50]*/ displayList = 0;
        /*[0x54]*/ currentSet = 0;
        /*[0x10]*/ texCoordsCount = 1;

        /*[0x40-0x4C]*/
        for (i = 0; i < 4; i++)
        {
            texCoordsId[i] = 0;
        }
    }

    eGeoSet::~eGeoSet()
    {
        clearExistingGeoSet();
    }


    ////////////////////////////////////////////////////////////////
    // eGeoSet: cloning the object
    ////////////////////////////////////////////////////////////////

    void eGeoSet::createFromOtherObject(const eGeoSet &other)
    {
        int32_t a;

        /****************/

        unknown_08 = other.unknown_08;

        defaultVertexCount = other.defaultVertexCount;

        texCoordsCount = other.texCoordsCount;

        /****************/

        if (nullptr != other.indicesOffsets)
        {
            indicesOffsets = new eGeoArray<ushort>(*(other.indicesOffsets));
            indicesOffsets->incRef();
        }
        else
        {
            indicesOffsets = nullptr;
        }

        /****************/

        if (nullptr != other.indicesArray)
        {
            indicesArray = new eGeoArray<ushort>(*(other.indicesArray));
            indicesArray->incRef();
        }
        else
        {
            indicesArray = nullptr;
        }

        /****************/

        for (a = 0; a < 2; a++)
        {
            if (nullptr != other.verticesArray[a])
            {
                verticesArray[a] = new eGeoArray<ePoint4>(*(other.verticesArray[a]));
                verticesArray[a]->incRef();
            }
            else
            {
                verticesArray[a] = nullptr;
            }
        }

        /****************/

        for (a = 0; a < 2; a++)
        {
            if (nullptr != other.normalsArray[a])
            {
                normalsArray[a] = new eGeoArray<ePoint4>(*(other.normalsArray[a]));
                normalsArray[a]->incRef();
            }
            else
            {
                normalsArray[a] = nullptr;
            }
        }

        /****************/

        for (a = 0; a < texCoordsCount; a++)
        {
            texCoordsId[a] = other.texCoordsId[a];

            if (nullptr != other.texCoordsArray[a])
            {
                texCoordsArray[a] = new eGeoArray<ePoint2>(*(other.texCoordsArray[a]));
                texCoordsArray[a]->incRef();
            }
            else
            {
                texCoordsArray[a] = nullptr;
            }
        }

        for (a = texCoordsCount; a < 4; a++)
        {
            texCoordsArray[a] = nullptr;
            texCoordsId[a] = 0;
        }

        /****************/

        if (nullptr != other.colorsArray)
        {
            colorsArray = new eGeoArray<ePoint4>(*(other.colorsArray));
            colorsArray->incRef();
        }
        else
        {
            colorsArray = nullptr;
        }

        /****************/

        displayList = 0;

        currentSet = 0;

        /****************/

        /* << MUST BE RESOLVED! >> */
        phy = nullptr;

        /****************/

        if (nullptr != other.aabbTree)
        {
            aabbTree = new eGeoArray<eABB>(*(other.aabbTree));
            aabbTree->incRef();
        }
        else
        {
            aabbTree = nullptr;
        }
    }

    eGeoSet::eGeoSet(const eGeoSet &other)
    : eRefCounter(other)
    {
        createFromOtherObject(other);
    }

    eGeoSet& eGeoSet::operator = (const eGeoSet &other)
    {
        if ((&other) != this)
        {
            eRefCounter::operator = (other);

            /****************/

            clearExistingGeoSet();

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eGeoSet::cloneFromMe() const
    {
        return new eGeoSet(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eGeoSet: serialization
    // <kao2.0046A930>
    ////////////////////////////////////////////////////////////////
    void eGeoSet::serialize(Archive &ar)
    {
        int32_t i;

        /* [0x08] unknown */
        ar.readOrWrite(&unknown_08, 0x04);

        /* Default number of vertices */
        ar.readOrWrite(&defaultVertexCount, 0x04);

        /* Array: Indices */

        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&indicesArray, &E_GEOARRAY_USHORT_TYPEINFO);

        /* Array: Vertices */

        ArFunctions::serialize_e3fXArray(ar, &(verticesArray[0]));

        /* Array: Normals */

        ArFunctions::serialize_e3fXArray(ar, &(normalsArray[0]));

        /* Number of texture coordinates */

        ar.readOrWrite(&texCoordsCount, 0x04);

        if ((texCoordsCount < 0) || (texCoordsCount > 4))
        {
            throw ErrorMessage
            (
                "eGeoSet::serialize():\n" \
                "invalid number of tex coord arrays!"
            );
        }

        /* Arrays: UV coordinates */

        for (i = 0; i < texCoordsCount; i++)
        {
            ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&(texCoordsArray[i]), &E_GEOARRAY_EPOINT2_TYPEINFO);

            ar.readOrWrite(&(texCoordsId[i]), 0x04);
        }

        if (ar.isInReadMode())
        {
            for (i = texCoordsCount; i < 4; i++)
            {
                texCoordsArray[i] = nullptr;
                texCoordsId[i] = 0;
            }
        }

        /* Array: Colors */

        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&colorsArray, &E_GEOARRAY_EPOINT4_TYPEINFO);

        /* Array: Indices Offsets */

        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&indicesOffsets, &E_GEOARRAY_USHORT_TYPEINFO);

        /* Array: "AABB" tree */

        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&aabbTree, &E_GEOARRAY_EABB_TYPEINFO);

        /* PhyTriMesh */

        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&phy, &E_PHYTRIMESH_TYPEINFO);
    }


    ////////////////////////////////////////////////////////////////
    // eGeoSet: draw
    ////////////////////////////////////////////////////////////////
    void eGeoSet::draw(int32_t draw_flags, int32_t texID) const
    {
        if ((texID >= 0) && (texID < 4))
        {
            GUI::changeView(true);

            /* DEBUG (moving objects) */
            if (0 != displayList)
            {
                glCallList(displayList + texID);
            }
            else
            {
                if (nullptr != phy)
                {
                    phy->prepareMatrices(GUI::drawFlags::DRAW_FLAG_ANIMS & draw_flags);
                    phy->animateVertices();
                }

                displayVertexBufferObject(texID, GUI::drawFlags::DRAW_FLAG_COLORS & draw_flags);
            }
        }

        if (GUI::drawFlags::DRAW_FLAG_COLLISION & draw_flags)
        {
            if ((nullptr != aabbTree) && (aabbTree->getLength() > 0))
            {
                eABB* boxes = aabbTree->getData();

                GUI::renderBoundingBox
                (
                    0.5f,
                    0, 1.0f, 0,
                    boxes[0].min.x, boxes[0].min.y, boxes[0].min.z,
                    boxes[0].max.x, boxes[0].max.y, boxes[0].max.z
                );
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eGeoSet: prepare for drawing
    // <kao2.0046A5A0>
    ////////////////////////////////////////////////////////////////
    void eGeoSet::prepareForDrawing()
    {
        if (0 != displayList)
        {
            glDeleteLists(displayList, getTextureCoordsCount());
        }
    }


    ////////////////////////////////////////////////////////////////
    // eGeoSet: texture coordinates functions (used with eTriMesh)
    ////////////////////////////////////////////////////////////////

    int32_t eGeoSet::getTextureCoordsCount() const
    {
        if (0 == texCoordsCount)
        {
            return 1;
        }

        return texCoordsCount;
    }

    int32_t eGeoSet::getTextureId(int32_t i) const
    {
        if ((i >= 0) && (i < 4))
        {
            return texCoordsId[i];
        }

        return 0;
    }


    ////////////////////////////////////////////////////////////////
    // eGeoSet: set arrays
    ////////////////////////////////////////////////////////////////

    void eGeoSet::setVerticesArray(eGeoArray<ePoint4>* new_vertices_array)
    {
        if (verticesArray[0] != new_vertices_array)
        {
            if (nullptr != verticesArray[0])
            {
                verticesArray[0]->decRef();
            }

            verticesArray[0] = new_vertices_array;

            if (nullptr != verticesArray[0])
            {
                verticesArray[0]->incRef();
            }
        }
    }

    void eGeoSet::setNormalsArray(eGeoArray<ePoint4>* new_normals_array)
    {
        if (normalsArray[0] != new_normals_array)
        {
            if (nullptr != normalsArray[0])
            {
                normalsArray[0]->decRef();
            }

            normalsArray[0] = new_normals_array;

            if (nullptr != normalsArray[0])
            {
                normalsArray[0]->incRef();
            }
        }
    }

    void eGeoSet::setIndicesOffsets(eGeoArray<ushort>* new_indices_offets)
    {
        if (indicesOffsets != new_indices_offets)
        {
            if (nullptr != indicesOffsets)
            {
                indicesOffsets->decRef();
            }

            indicesOffsets = new_indices_offets;

            if (nullptr != indicesOffsets)
            {
                indicesOffsets->incRef();
            }
        }
    }

    void eGeoSet::setIndicesArray(eGeoArray<ushort>* new_indices_array)
    {
        if (indicesArray != new_indices_array)
        {
            if (nullptr != indicesArray)
            {
                indicesArray->decRef();
            }

            indicesArray = new_indices_array;

            if (nullptr != indicesArray)
            {
                indicesArray->incRef();
            }
        }
    }

    void eGeoSet::setTextureCoordsArray(eGeoArray<ePoint2>* new_uv_array)
    {
        int32_t i;

        if (texCoordsArray[0] != new_uv_array)
        {
            for (i = 0; i < 4; i++)
            {
                if (nullptr != texCoordsArray[i])
                {
                    texCoordsArray[i]->decRef();

                    texCoordsArray[i] = nullptr;
                }

                texCoordsId[i] = 0;
            }

            texCoordsArray[0] = new_uv_array;
            texCoordsId[0] = 0;

            if (nullptr != texCoordsArray[0])
            {
                texCoordsArray[0]->incRef();

                texCoordsCount = 1;
            }
            else
            {
                texCoordsCount = 0;
            }
        }
    }

    void eGeoSet::setColorsArray(eGeoArray<ePoint4>* new_colors_array)
    {
        if (colorsArray != new_colors_array)
        {
            if (nullptr != colorsArray)
            {
                colorsArray->decRef();
            }

            colorsArray = new_colors_array;

            if (nullptr != colorsArray)
            {
                colorsArray->incRef();
            }
        }
    }

    void eGeoSet::setTwoIntegers(int32_t a, int32_t b)
    {
        /* Object is not drawn when [0x0C] is ZERO */
        /* [0x08] is usually 0x0F, [0x0C] is usualy vertices/colors/normals length */

        unknown_08 = a;
        defaultVertexCount = b;
    }


    ////////////////////////////////////////////////////////////////
    // eGeoSet: get arrays
    ////////////////////////////////////////////////////////////////

    eGeoArray<ePoint4>* eGeoSet::getVerticesArray() const
    {
        return verticesArray[currentSet];
    }

    eGeoArray<ePoint4>* eGeoSet::getNormalsArray() const
    {
        return normalsArray[currentSet];
    }

    eGeoArray<ePoint2>* eGeoSet::getTextureCoordsArray() const
    {
        return texCoordsArray[0];
    }

    eGeoArray<ePoint4>* eGeoSet::getColorsArray() const
    {
        return colorsArray;
    }

    eGeoArray<ushort>* eGeoSet::getIndicesOffsets()const
    {
        return indicesOffsets;
    }

    eGeoArray<ushort>* eGeoSet::getIndicesArray() const
    {
        return indicesArray;
    }

    ePhyTriMesh* eGeoSet::getPhyTriMesh() const
    {
        return phy;
    }


    ////////////////////////////////////////////////////////////////
    // eGeoSet: transform vertices and normals, recartulate bounding box
    ////////////////////////////////////////////////////////////////
    void eGeoSet::transformVertices(eSRP &new_transform, eString &mesh_name, ePoint3 &box_min, ePoint3 &box_max)
    {
        int32_t a, b, vertices_length;
        ePoint4* vertices_data;
        eMatrix4x4 matrix = new_transform.getMatrix();

        const eGeoArray<ePoint4>* arrays[4] =
        {
            verticesArray[0], verticesArray[1],
            normalsArray[0], normalsArray[1]
        };

        for (a = 0; a < 4; a++)
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

        vertices_length = verticesArray[0]->getLength();
        vertices_data = verticesArray[0]->getData();

        if (nullptr != vertices_data)
        {
            calculateBoundaryBox(box_min, box_max, vertices_length, vertices_data, 0, nullptr);
        }

        if (nullptr != aabbTree)
        {
            try
            {
                buildAabbTree(mesh_name);
            }
            catch (ErrorMessage &err)
            {
                err.display();
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eGeoSet: build "axis-aligned bounding boxes" tree
    ////////////////////////////////////////////////////////////////
    void eGeoSet::buildAabbTree(eString &mesh_name)
    {
        int32_t i, j, k, l, m, total_entries, total_leaves;

        int32_t test_vertices_length = verticesArray[0]->getLength();
        ePoint4* test_vertices_data = verticesArray[0]->getData();
        int32_t test_indices_length = indicesArray->getLength();
        ushort* test_indices_data = indicesArray->getData();
        int32_t test_indices_offsets_length = indicesOffsets->getLength();
        ushort* test_indices_offsets = indicesOffsets->getData();

        ushort temp_vertex_id[3];
        eABB temp_aabb_entry;
        eABB* temp_aabb_data = nullptr;

        eABB* aabb_data = nullptr;

        clearAabbTree();

        if (nullptr == test_vertices_data)
        {
            return;
        }

        /********************************/
        /* Look for all the triangles in the mesh */
        /* (--dsp--) optimize for quads */

        for (i = 0; i < 2; i++)
        {
            total_leaves = 0;

            if (nullptr != test_indices_offsets)
            {
                /* TRIANGLE_STRIP list (with spacing offsets) */

                k = 0;

                for (j = 0; j < test_indices_offsets_length; j++)
                {
                    l = (test_indices_offsets[j] - 2);

                    if (nullptr != test_indices_data)
                    {
                        if (1 == i)
                        {
                            for (m = 0; m < l; m++)
                            {
                                temp_vertex_id[0] = test_indices_data[k + m];
                                temp_vertex_id[1] = test_indices_data[k + m + 1];
                                temp_vertex_id[2] = test_indices_data[k + m + 2];

                                calculateBoundaryBox
                                (
                                    temp_aabb_data[total_leaves + m].min,
                                    temp_aabb_data[total_leaves + m].max,
                                    test_vertices_length,
                                    test_vertices_data,
                                    3,
                                    temp_vertex_id
                                );

                                /* Set indices IDs */
                                temp_aabb_data[total_leaves + m].leftNode = (0 == (m % 2)) ? 0x80000000 : 0xC0000000;
                                temp_aabb_data[total_leaves + m].leftNode |= (k + m);
                                temp_aabb_data[total_leaves + m].rightNode = (0 == (m % 2)) ? 0xC0000000 : 0x80000000;
                                temp_aabb_data[total_leaves + m].rightNode |= 0x01;
                            }
                        }
                    }
                    else
                    {
                        if (1 == i)
                        {
                            for (m = 0; m < l; m++)
                            {
                                temp_vertex_id[0] = k + m;
                                temp_vertex_id[1] = k + m + 1;
                                temp_vertex_id[2] = k + m + 2;

                                calculateBoundaryBox
                                (
                                    temp_aabb_data[total_leaves + m].min,
                                    temp_aabb_data[total_leaves + m].max,
                                    test_vertices_length,
                                    test_vertices_data,
                                    3,
                                    temp_vertex_id
                                );

                                /* Set vertices IDs */
                                temp_aabb_data[total_leaves + m].leftNode = (0 == (m % 2)) ? 0x80000000 : 0xC0000000;
                                temp_aabb_data[total_leaves + m].leftNode |= temp_vertex_id[0];
                                temp_aabb_data[total_leaves + m].rightNode = (0 == (m % 2)) ? 0xC0000000 : 0x80000000;
                                temp_aabb_data[total_leaves + m].rightNode |= 0x01;
                            }
                        }
                    }

                    k += test_indices_offsets[j];

                    if (l > 0) total_leaves += l;
                }

            }
            else if (nullptr != test_indices_data)
            {
                /* TRIANGLES list (with specified indices) */

                l = (test_indices_length / 3);

                if (1 == i)
                {
                    for (m = 0; m < l; m++)
                    {
                        temp_vertex_id[0] = test_indices_data[3 * m];
                        temp_vertex_id[1] = test_indices_data[3 * m + 1];
                        temp_vertex_id[2] = test_indices_data[3 * m + 2];

                        calculateBoundaryBox
                        (
                            temp_aabb_data[total_leaves + m].min,
                            temp_aabb_data[total_leaves + m].max,
                            test_vertices_length,
                            test_vertices_data,
                            3,
                            temp_vertex_id
                        );

                        /* Set indices IDs */
                        temp_aabb_data[total_leaves + m].leftNode = (0x80000000 | (3 * m));
                        temp_aabb_data[total_leaves + m].rightNode = (0x80000000 | (3 * m));
                    }
                }

                if (l > 0) total_leaves += l;
            }
            else
            {
                /* TRIANGLES list (without indices) */

                l = (defaultVertexCount / 3);

                if (1 == i)
                {
                    for (m = 0; m < l; m++)
                    {
                        calculateBoundaryBox
                        (
                            temp_aabb_data[total_leaves + m].min,
                            temp_aabb_data[total_leaves + m].max,
                            3,
                            (test_vertices_data + (3 * m)),
                            0,
                            nullptr
                        );

                        /* Set vertices IDs */
                        temp_aabb_data[total_leaves + m].leftNode = (0x80000000 | (3 * m));
                        temp_aabb_data[total_leaves + m].rightNode = (0x80000000 | (3 * m));
                    }
                }

                if (l > 0) total_leaves += l;
            }

            if ((0 == i) && (total_leaves > 0))
            {
                if (total_leaves > 1000)
                {
                    throw ErrorMessage
                    (
                        "eGeoSet::buildAabbTree():\n" \
                        "too many collision triangles! (found %d, max 1000)\n\n" \
                        "Please subdivide this eTriMesh: \"%s\"",
                        total_leaves,
                        mesh_name.getText()
                    );
                }
                else
                {
                    temp_aabb_data = new eABB [total_leaves];
                }
            }
        }

        if (total_leaves <= 0)
        {
            return;
        }

        /********************************/
        /* Sort boundary boxes */

        for (i = 0; i < (total_leaves - 1); i++)
        {
            for (j = (i + 1); j < total_leaves; j++)
            {
                if ( (temp_aabb_data[j].min.x < temp_aabb_data[i].min.x)
                  || (temp_aabb_data[j].min.y < temp_aabb_data[i].min.y)
                  || (temp_aabb_data[j].min.z < temp_aabb_data[i].min.z)
                  || (temp_aabb_data[j].max.x < temp_aabb_data[i].max.x)
                  || (temp_aabb_data[j].max.y < temp_aabb_data[i].max.y)
                  || (temp_aabb_data[j].max.z < temp_aabb_data[i].max.z) )
                {
                    temp_aabb_entry = temp_aabb_data[i];
                    temp_aabb_data[i] = temp_aabb_data[j];
                    temp_aabb_data[j] = temp_aabb_entry;
                }
            }
        }

        /********************************/
        /* Setup tree, copy first entry */
        /* (branches = leaves - 1) */

        total_entries = (total_leaves - 1) + total_leaves;

        aabb_data = new eABB [total_entries];
        aabb_data[0] = temp_aabb_data[0];

        aabbTree = new eGeoArray<eABB>;
        aabbTree->incRef();
        aabbTree->setup(total_entries, aabb_data);

        /********************************/
        /* Fill the list, assign IDs */

        k = 1; // next empty ID

        for (i = 1; i < total_leaves; i++)
        {
            if (false == aabb_data[0].insertLeaf(0, k, aabb_data, temp_aabb_data[i]))
            {
                if (nullptr != temp_aabb_data)
                {
                    delete[](temp_aabb_data);
                    temp_aabb_data = nullptr;
                }

                throw ErrorMessage
                (
                    "eGeoSet::buildAabbTree()\n" \
                    "failure while adding leaf to the list!\n" \
                    "(eTriMesh name: \"%s\")",
                    mesh_name.getText()
                );
            }
        }

        if (nullptr != temp_aabb_data)
        {
            delete[](temp_aabb_data);
            temp_aabb_data = nullptr;
        }

        if (k != total_entries)
        {
            throw ErrorMessage
            (
                "eGeoSet::buildAabbTree()\n" \
                "some entries went missing!\n" \
                "(eTriMesh name: \"%s\")",
                mesh_name.getText()
            );
        }
    }


    ////////////////////////////////////////////////////////////////
    // eGeoSet: clear "axis-aligned bounding boxes" tree
    ////////////////////////////////////////////////////////////////
    void eGeoSet::clearAabbTree()
    {
        if (nullptr != aabbTree)
        {
            aabbTree->decRef();
            aabbTree = nullptr;
        }
    }


    ////////////////////////////////////////////////////////////////
    // eGeoSet: clear already existing object
    ////////////////////////////////////////////////////////////////
    void eGeoSet::clearExistingGeoSet()
    {
        int32_t a;

        /****************/

        if (0 != displayList)
        {
            glDeleteLists(displayList, getTextureCoordsCount());
            displayList = 0;
        }

        /****************/

        aabbTree->decRef();
        aabbTree = nullptr;

        /****************/

        phy->decRef();
        phy = nullptr;

        /****************/

        colorsArray->decRef();
        colorsArray = nullptr;

        /****************/

        for (a = 0; a < 4; a++)
        {
            texCoordsArray[a]->decRef();
            texCoordsArray[a] = nullptr;
        }

        /****************/

        for (a = 0; a < 2; a++)
        {
            normalsArray[a]->decRef();
            normalsArray[a] = nullptr;
        }

        /****************/

        for (a = 0; a < 2; a++)
        {
            verticesArray[a]->decRef();
            verticesArray[a] = nullptr;
        }

        /****************/

        indicesArray->decRef();
        indicesArray = nullptr;

        /****************/

        indicesOffsets->decRef();
        indicesOffsets = nullptr;
    }


    ////////////////////////////////////////////////////////////////
    // eGeoSet: display Vertex Buffer Object (OpenGL calls)
    // <kao2.0046A190>
    ////////////////////////////////////////////////////////////////
    void eGeoSet::displayVertexBufferObject(int32_t texID, bool use_color) const
    {
        int32_t i, j;

        /* VERTICES */

        glEnableClientState(GL_VERTEX_ARRAY);

        glVertexPointer
        (
            0x04,
            GL_FLOAT,
            0,
            verticesArray[currentSet]->getData()
        );

        /* TEXTURE */

        if ((texID >= 0) && (texID < texCoordsCount))
        {
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);

            glTexCoordPointer
            (
                0x02,
                GL_FLOAT,
                0,
                texCoordsArray[texID]->getData()
            );
        }

        /* NORMALS */

        if (nullptr != normalsArray[currentSet])
        {
            glEnableClientState(GL_NORMAL_ARRAY);

            glNormalPointer
            (
                GL_FLOAT,
                0x10,
                normalsArray[currentSet]->getData()
            );
        };

        /* COLORS */

        if (use_color && (nullptr != colorsArray))
        {
            glEnableClientState(GL_COLOR_ARRAY);

            glColorPointer
            (
                0x04,
                GL_FLOAT,
                0,
                colorsArray->getData()
            );
        }

        /* INDICES (strips or triangles) */

        if (nullptr != indicesOffsets)
        {
            j = 0;

            for (i = 0; i < indicesOffsets->getLength(); i++)
            {
                if (nullptr != indicesArray)
                {
                    glDrawElements
                    (
                        GL_TRIANGLE_STRIP,
                        indicesOffsets->getData()[i],
                        GL_UNSIGNED_SHORT,
                        (indicesArray->getData() + j)
                    );
                }
                else
                {
                    glDrawArrays
                    (
                        GL_TRIANGLE_STRIP,
                        j,
                        indicesOffsets->getData()[i]
                    );
                }

                j += indicesOffsets->getData()[i];
            }
        }
        else
        {
            if (nullptr != indicesArray)
            {
                glDrawElements
                (
                    GL_TRIANGLES,
                    indicesArray->getLength(),
                    GL_UNSIGNED_SHORT,
                    indicesArray->getData()
                );
            }
            else
            {
                glDrawArrays
                (
                    GL_TRIANGLES,
                    0x00,
                    defaultVertexCount
                );
            }
        }

        /* DISABLE CLIENT STATES */

        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
    }

}
