#include <kao2engine/eGeometry.h>
#include <kao2ar/Archive.h>

#include <kao2engine/eMaterial.h>

#include <kao2engine/eALBox.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eGeometry interface
    // <kao2.0046F040> (overloaded constructor)
    // <kao2.0046EF90> (constructor)
    // <kao2.0046F160> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_GEOMETRY_TYPEINFO
    (
        E_GEOMETRY_ID,
        "eGeometry",
        &E_NODE_TYPEINFO,
        []() -> eObject*
        {
            return nullptr;
        }
    );

    TypeInfo* eGeometry::getType() const
    {
        return &E_GEOMETRY_TYPEINFO;
    }

    eGeometry::eGeometry(eString s, eNode* x)
    : eNode(s, x)
    {
        /*[0x3C]*/ material = nullptr;
        /*[0x40]*/ boxBoundMax.x = 1.0f;
        /*[0x4C]*/ boxBoundMin.x = 0;
    }

    eGeometry::eGeometry()
    : eNode()
    {
        /*[0x3C]*/ material = nullptr;
        /*[0x4C]*/ boxBoundMax.x = 0;
        /*[0x40]*/ boxBoundMin.x = 1.0f;
    }

    eGeometry::~eGeometry()
    {
        /*[0x3C]*/ material->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // eGeometry serialization
    // <kao2.0046F1D0>
    ////////////////////////////////////////////////////////////////
    void eGeometry::serialize(Archive &ar)
    {
        eNode::serialize(ar);

        /* Material */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&material, &E_MATERIAL_TYPEINFO);

        /* Bounding box */
        if (ar.getVersion() < 0x82)
        {
            eObject* o = nullptr;
            ar.serialize(&o, nullptr);
        }
        else
        {
            boxBoundMin.serialize(ar);
            boxBoundMax.serialize(ar);
        }
    }


    ////////////////////////////////////////////////////////////////
    // eGeometry old serialization
    // <kao2.0046F980>
    ////////////////////////////////////////////////////////////////
    void eGeometry::oldNodeSerialization(ePoint3* arg1)
    {
        boxBoundMin = arg1[0];
        boxBoundMax = arg1[1];

        /*[0x1C]*/ flags &= 0xFFFFFFEF;
    }


    ////////////////////////////////////////////////////////////////
    // eGeometry: (editor option) find object in 3D space
    ////////////////////////////////////////////////////////////////
    ePoint3 eGeometry::editingGetCenterPoint() const
    {
        return (boxBoundMax + boxBoundMin) * 0.5f;
    }


    ////////////////////////////////////////////////////////////////
    // eGeometry: (editor option) rebuild collision
    ////////////////////////////////////////////////////////////////
    void eGeometry::editingRebuildCollision()
    {
        createCollisionEntry();
    }


    ////////////////////////////////////////////////////////////////
    // eGeometry: find material by path
    ////////////////////////////////////////////////////////////////
    eMaterial* eGeometry::findMaterial(eString &searched_path) const
    {
        if (nullptr != material)
        {
            if (material->matchesPath(searched_path))
            {
                return material;
            }
        }

        return nullptr;
    }


    ////////////////////////////////////////////////////////////////
    // eGeometry: get Material pointer
    ////////////////////////////////////////////////////////////////
    eMaterial* eGeometry::getMaterial() const
    {
        return material;
    }


    ////////////////////////////////////////////////////////////////
    // eGeometry: set Material pointer
    ////////////////////////////////////////////////////////////////
    void eGeometry::setMaterial(eMaterial* new_material)
    {
        if (material != new_material)
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
    }


    ////////////////////////////////////////////////////////////////
    // eGeometry: set boundary box
    ////////////////////////////////////////////////////////////////
    void eGeometry::setBoundaryBox(ePoint3 &new_min, ePoint3 &new_max)
    {
        boxBoundMin = new_min;
        boxBoundMax = new_max;
    }


    ////////////////////////////////////////////////////////////////
    // eGeometry: create collision entry
    ////////////////////////////////////////////////////////////////
    void eGeometry::createCollisionEntry()
    {
        eALBox* new_albox = nullptr;

        float boundaries[6] =
        {
            boxBoundMin.x, boxBoundMin.y, boxBoundMin.z,
            boxBoundMax.x, boxBoundMax.y, boxBoundMax.z
        };

        new_albox = new eALBox();
        new_albox->incRef();

        new_albox->createAxisListEntry(this, boundaries);

        new_albox->decRef();
    }

}
