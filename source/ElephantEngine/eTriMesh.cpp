#include <ElephantEngine/eTriMesh.h>
#include <ElephantBase/Archive.h>
#include <ElephantBase/eDrawContext.h>

#include <ElephantEngine/ePhyTriMesh.h>
#include <ElephantEngine/eGeoSet.h>

#include <ElephantEngine/eTexture.h>
#include <ElephantEngine/eMaterial.h>

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

    const TypeInfo* eTriMesh::getType() const
    {
        return &E_TRIMESH_TYPEINFO;
    }

    eTriMesh::eTriMesh()
    : eGeometry("", nullptr)
    {
        /*[0x58]*/ geo = nullptr;
        /*[0x64]*/ modifier = nullptr;

        /* Collision enabled by default for all TriMeshes! */
        /*[0x30]*/ flagsCollisionResponse = 0;
    }

    eTriMesh::~eTriMesh()
    {
        /*[0x58]*/ geo->decRef();
        /*[0x64]*/ modifier->decRef();
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

        /****************/

        /* << MUST BE RESOLVED! >> */
        modifier = nullptr;
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

            modifier->decRef();
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

        if (nullptr == geo)
        {
            throw ErrorMessage
            (
                "eTriMesh::serialize():\n" \
                "Missing the \"eGeoSet\" object!"
            );
        }

        if (ar.getVersion() >= 0x9E)
        {
            /* [0x64] Modifier with bones table (moved from "eGeoSet") */
            ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&modifier, &E_PHYTRIMESH_TYPEINFO);

            if (ar.isInReadMode())
            {
                geo->setPhyTriMesh(modifier);
            }
        }
        else
        {
            if (ar.isInReadMode())
            {
                if (nullptr != (modifier = geo->getPhyTriMesh()))
                {
                    modifier->incRef();
                }
            }
        }

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
        int32_t i, uv_maps, draw_flags;
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

        uv_maps = geo->getTextureCoordsCount();

        if ((0 == uv_maps) || (0 == (GUI::drawFlags::DRAW_FLAG_BLENDING & draw_flags)))
        {
            uv_maps = 1;
        }

        for (i = 0; i < uv_maps; i++)
        {
            draw_context.useMaterial
            (
                use_outline ? nullptr : material,
                i
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
    // eTriMesh: custom TXT parser
    ////////////////////////////////////////////////////////////////

    int32_t eTriMesh::parsingCustomMessage(char* result_msg, const eString &message, int32_t params_count, const TxtParsingNodeProp* params)
    {
        int32_t test[2];
        eGeoArray<ePoint4>* vertices = nullptr;
        eGeoArray<ePoint2>* uv_mapping = nullptr;
        ePhyTriMesh* phy;

        if (1 != (test[0] = eGeometry::parsingCustomMessage(result_msg, message, params_count, params)))
        {
            return test[0];
        }

        if (message.compareExact("assertTextureMappingTypes", true))
        {
            if ((params_count < 0) || (params_count > 4))
            {
                TxtParsingNode_ErrorArgCount(result_msg, "assertTextureMappingTypes", 4);
                return 2;
            }

            /********************************/

            if (nullptr == geo)
            {
                sprintf_s(result_msg, LARGE_BUFFER_SIZE, "\"assertTextureMappingTypes\" message: `GeoSet` is empty!");
                return 2;
            }

            if (nullptr != (uv_mapping = geo->getTextureCoordsArray(0)))
            {
                test[1] = uv_mapping->getLength();
            }
            else
            {
                test[1] = 0;
            }

            if (0 == test[1])
            {
                if (nullptr != (vertices = geo->getVerticesArray(0)))
                {
                    test[1] = vertices->getLength();
                }
                else
                {
                    test[1] = 0;
                }
            }

            if (nullptr == uv_mapping)
            {
                uv_mapping = new eGeoArray<ePoint2>();
                uv_mapping->setup(test[1], new ePoint2 [test[1]]);
            }

            uv_mapping->incRef();

            for (test[0] = 0; test[0] < params_count; test[0]++)
            {
                if (!params[test[0]].checkType(TXT_PARSING_NODE_PROPTYPE_INTEGER))
                {
                    TxtParsingNode_ErrorArgType(result_msg, "assertTextureMappingTypes", test[0], TXT_PARSING_NODE_PROPTYPE_INTEGER);
                    return 2;
                }

                params[test[0]].getValue(&(test[1]));

                if (nullptr == geo->getTextureCoordsArray(test[0]))
                {
                    geo->setTextureCoordsArray(test[0], uv_mapping);
                }

                geo->setTexMappingType(test[0], test[1]);
            }

            uv_mapping->decRef();

            for (test[0] = params_count; test[0] < 4; test[0]++)
            {
                geo->setTextureCoordsArray(test[0], nullptr);
                geo->setTexMappingType(test[0], 0);
            }

            return 0;
        }
        else if (message.compareExact("clearMorpherModifier", true))
        {
            if (0 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "clearMorpherModifier", 0);
                return 2;
            }

            /********************************/

            if (nullptr == geo)
            {
                sprintf_s(result_msg, LARGE_BUFFER_SIZE, "\"clearMorpherModifier\" message: `GeoSet` is empty!");
                return 2;
            }

            phy = geo->getPhyTriMesh();

            if (nullptr == phy)
            {
                sprintf_s(result_msg, LARGE_BUFFER_SIZE, "\"clearMorpherModifier\" message: `PhyTriMesh` is empty!");
                return 2;
            }

            phy->setMorpherModifier(nullptr);

            return 0;
        }

        return 1;
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
            geo->decRef();

            geo = new_geo;

            if (nullptr != geo)
            {
                geo->incRef();
            }
        }
    }

}
