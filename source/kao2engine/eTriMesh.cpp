#include <kao2engine/eTriMesh.h>
#include <kao2ar/Archive.h>

#include <kao2engine/eGeoSet.h>

#include <kao2engine/eTexture.h>
#include <kao2engine/eMaterial.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eTriMesh interface
    // <kao2.00469830> (constructor)
    // <kao2.00469FD0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_TRIMESH_TYPEINFO
    (
        E_TRIMESH_ID,
        "eTriMesh",
        &E_GEOMETRY_TYPEINFO,
        []() -> eObject*
        {
            return new eTriMesh;
        }
    );

    TypeInfo* eTriMesh::getType()
    {
        return &E_TRIMESH_TYPEINFO;
    }

    eTriMesh::eTriMesh()
    : eGeometry("", nullptr)
    {
        /*[0x58]*/ geo = nullptr;

        /*[0x30]*/ flags02 = 0;
    }

    eTriMesh::~eTriMesh()
    {
        /*[0x58]*/ geo->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // eTriMesh serialization
    // <kao2.0046A880>
    ////////////////////////////////////////////////////////////////
    void eTriMesh::serialize(Archive &ar)
    {
        int32_t a;

        eGeometry::serialize(ar);

        /* unknown or deprecated */
        a = 0x01;
        ar.readOrWrite(&a, 0x04);

        /* [0x58] Geo Set */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&geo, &E_GEOSET_TYPEINFO);

        /* Checking material name for "invisible" */
        if (ar.isInReadMode())
        {
            if (nullptr != material)
            {
                if (material->hasInvisibleInName())
                {
                    flags |= 0x00010000;

                    flags &= (~ 0x00000001);
                }
            }
        }

        /* Prepare for drawing */
        if (ar.isInReadMode())
        {
            /* "eMaterial::eTexture::eBitmap" already prepared during serialization */

            if (nullptr != geo)
            {
                geo->prepareForDrawing();
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eTriMesh: render
    ////////////////////////////////////////////////////////////////
    void eTriMesh::renderObject(eAnimate* anim, int32_t draw_flags, eSRP &parent_srp)
    {
        bool is_invisible = true;

        int32_t i, texID;

        GLuint tex_name = 0;
        eTexture* test_texture;

        if (GUI::drawFlags::DRAW_FLAG_INVISIBLE & draw_flags)
        {
            is_invisible = false;
        }
        else if (0x00000001 & flags)
        {
            is_invisible = false;
        }

        if (false == is_invisible)
        {
            if (nullptr != geo)
            {
                /* (--dsp--) `i < geo->getTextureCoordsCount()` */
                /* (--dsp--) `i < 1` */

                for (i = 0; i < 1; i++)
                {
                    if (nullptr != material)
                    {
                        texID = geo->getTextureId(i);

                        test_texture = material->getIthTexture(texID);

                        if (nullptr != test_texture)
                        {
                            tex_name = test_texture->getTextureName();
                        }
                        else
                        {
                            tex_name = 0;
                        }
                    }

                    geo->draw(anim, draw_flags, tex_name, i);
                }
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eTriMesh: get GeoSet pointer (used with ePhyTriMesh)
    ////////////////////////////////////////////////////////////////
    eGeoSet* eTriMesh::getGeoSetLink()
    {
        return geo;
    }


    ////////////////////////////////////////////////////////////////
    // eTriMesh: set GeoSet pointer
    ////////////////////////////////////////////////////////////////
    void eTriMesh::setGeoSet(eGeoSet* new_geo)
    {
        if (nullptr != geo)
        {
            geo->decRef();
        }

        geo = new_geo;

        if (nullptr != geo)
        {
            geo->incRef();
        }
    }


    ////////////////////////////////////////////////////////////////
    // eTriMesh: set Material pointer
    ////////////////////////////////////////////////////////////////
    void eTriMesh::setMaterial(eMaterial* new_material)
    {
        if (nullptr != material)
        {
            material->decRef();
        }

        material = new_material;

        if (nullptr != material)
        {
            material->incRef();
        }
    }


    ////////////////////////////////////////////////////////////////
    // eTriMesh: get Material pointer
    ////////////////////////////////////////////////////////////////
    eMaterial* eTriMesh::getMaterial()
    {
        return material;
    }


    ////////////////////////////////////////////////////////////////
    // eTriMesh: set boundary box
    ////////////////////////////////////////////////////////////////
    void eTriMesh::setBoundaryBox(ePoint3 new_min, ePoint3 new_max)
    {
        boxBoundMin = new_min;
        boxBoundMax = new_max;
    }

}
