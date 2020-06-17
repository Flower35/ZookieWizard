#include <kao2engine/eTriMesh.h>
#include <kao2ar/Archive.h>

#include <kao2engine/ePhyTriMesh.h>
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

    TypeInfo* eTriMesh::getType() const
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
    // eTriMesh: dereference "eTransform" bones (if any exist)
    ////////////////////////////////////////////////////////////////
    void eTriMesh::destroyNode()
    {
        ePhyTriMesh* test_phy;

        if (nullptr != geo)
        {
            test_phy = geo->getPhyTriMesh();

            if (nullptr != test_phy)
            {
                test_phy->deleteBones();
            }
        }

        eNode::destroyNode();
    }


    ////////////////////////////////////////////////////////////////
    // eTriMesh: (editor option) rebuild collision
    ////////////////////////////////////////////////////////////////
    void eTriMesh::editingRebuildCollision()
    {
        eGeometry::editingRebuildCollision();

        if (nullptr != geo)
        {
            try
            {
                geo->buildAabbTree(name);
            }
            catch (ErrorMessage &err)
            {
                err.display();
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eTriMesh: (editor function) clear collision
    ////////////////////////////////////////////////////////////////
    void eTriMesh::editingClearCollision()
    {
        if (nullptr != geo)
        {
            geo->clearAabbTree();
        }

        eNode::editingClearCollision();
    }


    ////////////////////////////////////////////////////////////////
    // eTriMesh: (editor option) apply new transformation
    ////////////////////////////////////////////////////////////////
    void eTriMesh::editingApplyNewTransform(eSRP &new_transform, int32_t marked_id)
    {
        ePhyTriMesh* test_phy;

        if (nullptr != geo)
        {
            geo->transformVertices(new_transform, name, boxBoundMin, boxBoundMax);

            if (nullptr != axisListBox)
            {
                eGeometry::editingRebuildCollision();
            }

            test_phy = geo->getPhyTriMesh();

            if (nullptr != test_phy)
            {
                test_phy->transformVertices(new_transform);
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eTriMesh: render
    ////////////////////////////////////////////////////////////////
    bool eTriMesh::renderObject(int32_t draw_flags, eAnimate* anim, eSRP &parent_srp, eMatrix4x4 &parent_matrix, int32_t marked_id)
    {
        int32_t i, texID;
        bool is_selected_or_marked;
        bool use_outline;
        float color[3];

        ePoint4 test_vertices[2];

        GLuint tex_name = 0;
        eTexture* test_texture;

        if (nullptr == geo)
        {
            return false;
        }

        if (false == eNode::renderObject(draw_flags, anim, parent_srp, parent_matrix, marked_id))
        {
            return false;
        }

        /* Testing 3D mesh boundaries */

        test_vertices[0] = ePoint4(boxBoundMin);
        test_vertices[1] = ePoint4(boxBoundMax);

        for (i = 0; i < 2; i++)
        {
            test_vertices[i].w = 1.0f;
            test_vertices[i] = parent_matrix * test_vertices[i];
        }

        if (false == GUI::testWithCameraPlanes
          (test_vertices[0].x, test_vertices[0].y, test_vertices[0].z,
          test_vertices[1].x, test_vertices[1].y, test_vertices[1].z))
        {
            return false;
        }

        /* Render 3D mesh */

        is_selected_or_marked = (((-2) == marked_id) || ((-1) == marked_id));
        use_outline = ((GUI::drawFlags::DRAW_FLAG_OUTLINE & draw_flags) && (((-2) == marked_id) || ((-3) == marked_id)));

        if (is_selected_or_marked)
        {
            /* This object is selected (-1) or marked (-2) and can be moved around */
            glPushMatrix();
            GUI::multiplyBySelectedObjectTransform();
        }

        if (use_outline)
        {
            GUI::colorOfMarkedObject(color[0], color[1], color[2]);
            glColor3f(color[0], color[1], color[2]);

            //// glDisable(GL_DEPTH_TEST);
            //// glPushMatrix();
            //// glScalef(1.05f, 1.05f, 1.05f);

            //// geo->draw(anim, draw_flags, 0, 0);

            //// glPopMatrix();
            //// glEnable(GL_DEPTH_TEST);
        }

        /* (--dsp--) `i < geo->getTextureCoordsCount()` */

        for (i = 0; i < 1; i++)
        {
            if (nullptr != material)
            {
                texID = geo->getTextureId(i);

                test_texture = material->getIthTexture(texID);

                if ((false == use_outline) && (nullptr != test_texture))
                {
                    tex_name = test_texture->getTextureName();
                }
                else
                {
                    tex_name = 0;
                }
            }

            geo->draw(draw_flags, tex_name, i);
        }

        if (use_outline)
        {
            glColor3f(1.0f, 1.0f, 1.0f);
        }

        if (is_selected_or_marked)
        {
            glPopMatrix();
        }

        return true;
    }


    ////////////////////////////////////////////////////////////////
    // eTriMesh: get GeoSet pointer (used with ePhyTriMesh)
    ////////////////////////////////////////////////////////////////
    eGeoSet* eTriMesh::getGeoset() const
    {
        return geo;
    }


    ////////////////////////////////////////////////////////////////
    // eTriMesh: set GeoSet pointer
    ////////////////////////////////////////////////////////////////
    void eTriMesh::setGeoset(eGeoSet* new_geo)
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

}
