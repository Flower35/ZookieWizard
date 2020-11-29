#include <kao2engine/eTriMesh.h>
#include <kao2ar/Archive.h>
#include <kao2ar/eDrawContext.h>

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

        /*[0x30]*/ flagsCollisionResponse = 0;
    }

    eTriMesh::~eTriMesh()
    {
        /*[0x58]*/ geo->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // eTriMesh: cloning the object
    ////////////////////////////////////////////////////////////////

    void eTriMesh::createFromOtherObject(const eTriMesh &other)
    {
        if (nullptr != other.geo)
        {
            geo = new eGeoSet(*(other.geo));
            geo->incRef();
        }
        else
        {
            geo = nullptr;
        }
    }

    eTriMesh::eTriMesh(const eTriMesh &other)
    : eGeometry(other)
    {
        createFromOtherObject(other);
    }

    eTriMesh& eTriMesh::operator = (const eTriMesh &other)
    {
        if ((&other) != this)
        {
            eGeometry::operator = (other);

            /****************/

            geo->decRef();

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eTriMesh::cloneFromMe() const
    {
        return new eTriMesh(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eTriMesh: serialization
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
    // eTriMesh: export readable structure
    ////////////////////////////////////////////////////////////////
    void eTriMesh::writeStructureToTextFile(FileOperator &file, int32_t indentation, bool group_written) const
    {
        ePhyTriMesh* phy;

        /* "eGeometry": parent class */

        eGeometry::writeStructureToTextFile(file, indentation, true);

        /* "eTriMesh": additional info */

        if (nullptr != geo)
        {
            phy = geo->getPhyTriMesh();

            if (nullptr != phy)
            {
                phy->writeStructureToTextFile(file, indentation, true);
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
    // eTriMesh: render this node
    ////////////////////////////////////////////////////////////////
    void eTriMesh::renderNode(eDrawContext &draw_context) const
    {
        int32_t i, draw_flags;
        bool is_selected_or_marked;
        bool use_outline;
        float color[3];

        eMatrix4x4* previous_matrix;
        eMatrix4x4 parent_matrix;
        ePoint4 test_vertices[2];

        if (nullptr == geo)
        {
            return;
        }

        /* Testing 3D mesh boundaries */

        draw_flags = draw_context.getDrawFlags();

        if (GUI::drawFlags::DRAW_FLAG_FRUSTUM & draw_flags)
        {
            test_vertices[0] = ePoint4(boxBoundMin);
            test_vertices[1] = ePoint4(boxBoundMax);

            if (nullptr != (previous_matrix = draw_context.getParentMatrix()))
            {
                parent_matrix = (*previous_matrix);
            }

            for (i = 0; i < 2; i++)
            {
                test_vertices[i].w = 1.0f;
                test_vertices[i] = parent_matrix * test_vertices[i];
            }

            if (false == GUI::testWithCameraPlanes
              (test_vertices[0].x, test_vertices[0].y, test_vertices[0].z,
              test_vertices[1].x, test_vertices[1].y, test_vertices[1].z))
            {
                return;
            }
        }

        /* Render 3D mesh */

        is_selected_or_marked = draw_context.isNodeSelectedOrMarked();
        use_outline = draw_context.isNodeOutlined();

        if (is_selected_or_marked)
        {
            glPushMatrix();
            GUI::multiplyBySelectedObjectTransform(false);
        }

        if (use_outline)
        {
            GUI::colorOfMarkedObject(color[0], color[1], color[2]);
            glColor3f(color[0], color[1], color[2]);
        }

        /* `i < geo->getTextureCoordsCount()` */

        for (i = 0; i < 1; i++)
        {
            draw_context.useMaterial
            (
                use_outline ? nullptr : material,
                geo->getTextureId(i)
            );

            geo->draw
            (
                use_outline ? ((~ GUI::drawFlags::DRAW_FLAG_COLORS) & draw_flags) : draw_flags,
                i
            );
        }

        if (use_outline)
        {
            glColor3f(1.0f, 1.0f, 1.0f);
        }

        if (is_selected_or_marked)
        {
            glPopMatrix();
        }
    }


    ////////////////////////////////////////////////////////////////
    // eTriMesh: (editor option) rebuild collision
    ////////////////////////////////////////////////////////////////
    void eTriMesh::editingRebuildCollision()
    {
        eGeometry::editingRebuildCollision();

        flagsCollisionResponse = 0x00FF;

        if (nullptr != geo)
        {
            try
            {
                geo->buildAabbTree(name);

                flagsCollisionResponse = 0;
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
    void eTriMesh::editingClearCollision(bool create_empty_pointer)
    {
        if (nullptr != geo)
        {
            geo->clearAabbTree();
        }

        eGeometry::editingClearCollision(create_empty_pointer);
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
    // eTriMesh: get or set the GeoSet
    ////////////////////////////////////////////////////////////////

    eGeoSet* eTriMesh::getGeoset() const
    {
        return geo;
    }

    void eTriMesh::setGeoset(eGeoSet* new_geo)
    {
        if (geo != new_geo)
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

}
