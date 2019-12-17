#include <kao2engine/eGeoSet.h>
#include <kao2ar/Archive.h>

#include <kao2engine/ePhyTriMesh.h>

#include <kao2engine/e3fXArray.h>

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

    TypeInfo* eGeoSet::getType()
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
        /*[0x5C]*/ unknown_5C = nullptr;

        /*[0x08]*/ unknown_08 = 0;
        /*[0x50]*/ displayList = 0;
        /*[0x54]*/ verticesCurrent = 0;
        /*[0x10]*/ texCoordsCount = 1;

        /*[0x40-0x4C]*/
        for (i = 0; i < 4; i++)
        {
            texCoordsId[i] = 0;
        }
    }

    eGeoSet::~eGeoSet()
    {
        int32_t i;

        if (0 != displayList)
        {
            glDeleteLists(displayList, ((0 == texCoordsCount) ? 0x01 : texCoordsCount));
        }

        unknown_5C->decRef();

        phy->decRef();

        colorsArray->decRef();

        for (i = 0; i < 4; i++)
        {
            texCoordsArray[i]->decRef();
        }

        for (i = 0; i < 2; i++)
        {
            normalsArray[i]->decRef();
        }

        for (i = 0; i < 2; i++)
        {
            verticesArray[i]->decRef();
        }

        indicesArray->decRef();

        indicesOffsets->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // eGeoSet serialization
    // <kao2.0046A930>
    ////////////////////////////////////////////////////////////////
    void eGeoSet::serialize(Archive &ar)
    {
        int32_t i;

        /* [0x08] unknown */
        ar.readOrWrite(&unknown_08, 0x04);

        /* Indicies number */
        ar.readOrWrite(&indicesCount, 0x04);

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

        /* Array: "ABB" */

        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&unknown_5C, &E_GEOARRAY_EABB_TYPEINFO);

        /* PhyTriMesh */

        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&phy, &E_PHYTRIMESH_TYPEINFO);
    }


    ////////////////////////////////////////////////////////////////
    // eGeoSet: draw
    ////////////////////////////////////////////////////////////////
    void eGeoSet::draw(GLuint tex_name)
    {
        if (0 != displayList)
        {
            if (0 != tex_name)
            {
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, tex_name);
            }
            else
            {
                glDisable(GL_TEXTURE_2D);
            }

            GUI::changeView(true);

            glCallList(displayList);

            if (0 != tex_name)
            {
                glDisable(GL_TEXTURE_2D);
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eGeoSet: generate OpenGL Display List
    ////////////////////////////////////////////////////////////////
    void eGeoSet::generateDisplayList(int32_t texID, bool c)
    {
        int32_t i;
        int32_t j;

        /* VERTICES */

        glEnableClientState(GL_VERTEX_ARRAY);

        glVertexPointer
        (
            0x04,
            GL_FLOAT,
            0,
            verticesArray[verticesCurrent]->getData()
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

        if (nullptr != normalsArray[verticesCurrent])
        {
            glEnableClientState(GL_NORMAL_ARRAY);

            glNormalPointer
            (
                GL_FLOAT,
                0x10,
                normalsArray[verticesCurrent]->getData()
            );
        };

        /* (--dsp--) COLORS (disabled: no dynamic lights in renderer) */

        if (false && (false == c))
        {
            if (nullptr != colorsArray)
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
        }

        /* INDICES (strips or triangles) */

        if (nullptr != indicesOffsets)
        {
            j = 0;

            for (i = 0; i < indicesOffsets->getLength(); i++)
            {
                if (true == c)
                {
                    /* (--dsp--) <kao2.0046A268> */
                }

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
                    indicesCount
                );
            }
        }

        /* DISABLE CLIENT STATES */

        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
    }


    ////////////////////////////////////////////////////////////////
    // eGeoSet: prepare for drawing
    // <kao2.0046A5A0>
    ////////////////////////////////////////////////////////////////
    void eGeoSet::prepareForDrawing()
    {
        int32_t a;
        int32_t b;
        GLuint lists;

        if (0 == displayList)
        {
            if ((referenceCount > 2) && (nullptr != phy))
            {
                unknown_08 |= 0x00001000;
            }

            /* (--dsp--) lists are NOT generated for animated meshes */
            if ((true) || (0 == (0x00000100 & unknown_08)))
            {
                b = texCoordsCount;

                if (0 == b)
                {
                    b = 1;
                }

                lists = glGenLists(b);

                for (a = 0; a < b; a++)
                {
                    /* (--dsp--) (colorArray) <kao2.0046A679> */

                    glNewList((lists + a), GL_COMPILE);

                    generateDisplayList(a, false);

                    glEndList();
                }

                displayList = lists;
            }
        }
    }

}
